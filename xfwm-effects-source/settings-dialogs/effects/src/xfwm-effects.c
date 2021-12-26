/*

Copyright 2021 James Hoover

Permission is hereby granted, free of charge, to any person obtaining a copy 
of this software and associated documentation files (the "Software"), to deal 
in the Software without restriction, including without limitation the rights 
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
copies of the Software, and to permit persons to whom the Software is furnished 
to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
SOFTWARE.

*/

#include <gtk/gtk.h>
#include <xfconf/xfconf.h>
#include <gdk/gdkx.h>
#include <string.h>

static void
effects_configure_widgets (GtkBuilder *builder)
{
    XfconfChannel *window_effects = xfconf_channel_new ("xfwm-effects");
    
    GtkWidget *use_effects_check = GTK_WIDGET (gtk_builder_get_object 
            (builder, "use_effects_check"));
    GtkWidget *blur_amount_scale = GTK_WIDGET (gtk_builder_get_object 
            (builder, "blur_amount_scale"));
    GtkWidget *white_amount_scale = GTK_WIDGET (gtk_builder_get_object 
            (builder, "white_amount_scale"));
    GtkWidget *effect_color_button = GTK_WIDGET (gtk_builder_get_object 
            (builder, "effect_color_button"));
    
    gint blur_value = 99;
    //if(!xfconf_channel_has_property(window_effects, "/blur-amount"))
    //{
        blur_value = xfconf_channel_get_int(window_effects, "/blur-amount", 100);
        gtk_range_set_value(GTK_RANGE(blur_amount_scale), blur_value);
    //}
        
    gint white_value = 0;
    //if(!xfconf_channel_has_property(window_effects, "/white-amount"))
    //{
        white_value = xfconf_channel_get_int(window_effects, "/white-amount", 0);
        gtk_range_set_value(GTK_RANGE(white_amount_scale), white_value);
    //}
	
	gboolean effect_active = TRUE;
    //if(!xfconf_channel_has_property(window_effects, "/effect-active"))
    //{
        effect_active = xfconf_channel_get_bool(window_effects, "/effect-active", TRUE);
        gtk_switch_set_state( (GtkSwitch *) use_effects_check, effect_active);
    //}

    //NOTE: bindings bind settings both ways!

    // when settings are changed in Tweaks dialog or xfce-settings-editor, etc., 
    // bindings will cause settings to update in our dialog
    xfconf_g_property_bind (window_effects,
                            "/effect-active",
                            G_TYPE_BOOLEAN,
                            G_OBJECT(use_effects_check), "active");
                            
    GtkAdjustment *adj_blur = 
            gtk_range_get_adjustment(GTK_RANGE(blur_amount_scale));
    xfconf_g_property_bind (window_effects,
                            "/blur-amount",
                            G_TYPE_INT,
                            (GObject *) adj_blur, "value");
    
    GtkAdjustment *adj_white = 
            gtk_range_get_adjustment(GTK_RANGE(white_amount_scale));
    xfconf_g_property_bind (window_effects,
                            "/white-amount",
                            G_TYPE_INT,
                            (GObject *) adj_white, "value");
    
    //should be bound to invert boolean, but couldn't figure an easy way to do it without writing a 'converter' class
    /* // this shows/hides the label that should become visible when compositor is turned off, since effects won't work then
    XfconfChannel *xfwm4 = xfconf_channel_new ("xfwm4");
    GtkWidget *compositor_is_off_label = GTK_WIDGET (gtk_builder_get_object (builder, "compositor_is_off_label"));
    xfconf_g_property_bind (xfwm4,
                            "/general/use_compositing",
                            G_TYPE_BOOLEAN,
                            (GObject *)compositor_is_off_label, "visible"); */
	
	xfconf_g_property_bind_gdkrgba(window_effects, 
								"/effect-color", 
								G_OBJECT(effect_color_button), 
								"rgba");   
}

int main(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;
    const gchar     *wm_name;

    gtk_init(&argc, &argv);

    // report version number
    if(argc > 1 && (!strcmp(argv[1],"-version") || !strcmp(argv[1],"--V")))
    {
        g_print("%s\n", "Xfwm Effects version 1.5.0");
        g_print("%s\n", "Copyright (c) 2021 James Hoover");
        g_print("\n");
        return 0;
    }
        
    wm_name = gdk_x11_screen_get_window_manager_name (gdk_screen_get_default ());
    if (G_UNLIKELY (g_ascii_strcasecmp (wm_name, "Xfwm4")))
    {
        g_print ("These settings cannot work with your current window manager (%s)\n", wm_name);
        return 1;
    }
    
    xfconf_init (NULL);
 
    builder = gtk_builder_new();
    
    //this feels dirty having to put a whole file path here, but not sure how else to do it
    //commentary: sure would be nice if linux was like macOS, where all this stuff is inside the app bundle
    gtk_builder_add_from_file (builder, "/usr/local/share/xfwm-effects/xfwm-effects.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "xfwm_effects"));
    
    gtk_window_set_title (GTK_WINDOW (window), "Xfwm Effects");
 
    gtk_widget_show(window);  
     
    gtk_builder_connect_signals(builder, NULL);
    
    if (builder)
    {
        effects_configure_widgets (builder);
    }
     
    g_object_unref(builder);
                       
    gtk_main();
    
    xfconf_shutdown ();

    return 0;
}

// called when window is closed
void on_xfwm_effects_destroy()
{
    gtk_main_quit();
}

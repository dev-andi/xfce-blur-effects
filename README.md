# xfce-blur-effects

## Note: 

This is a shameless copy of James Hoover's XFCE Effects. 

All credits goes to Kalideva. This package is just a port of xfce-effects to Archlinux

Visit : https://www.kalideva.com/ for more details. 

I have included the below steps which is similar to the original package.

## WARNING :
If you run it without sudo privileges, the next time you reboot
the entire WM would be gone and you'll only get black screen. 
So be careful.

 
 # Xfwm Effects 1.5

__Xfwm Effects__ adds depth and color harmony to the Xfce4 Desktop Environment 
by modifying the Xfwm4 compositing window manager's code.

## How it works

Xfwm Effects adds depth and color harmony to the appearance of the desktop, 
without adding distraction. It does so by creating an image of the desktop
when necessary, then uses the Imlib2 library to blur the desktop image, then 
uses Xlib compositing commands to composite the blurred background image onto 
desktop windows, panels, menus, and popovers. The effect is reminiscent of 
Apple's 'vibrancy' effect. Using this method sidesteps the computationally 
expensive need to continually generate gaussian blur, which can slow the 
responsiveness of the desktop environment.

## A settings adjustment app is included

Also included is an app (xfwm-effects) that allows the user to turn the effect 
on and off, to adjust the amount of blur, and to adjust the amount of white 
composited (for light themes). Note that to see the effects, 'Compositor > 
Enable Display Compositing' must be selected (i.e., active) in the Window 
Manager Tweaks app (the compositor is used to draw the effect). Adjusting the 
sliders on the Compositor tab of the Window Manager Tweaks app toward 
'Transparent' will make the effect more pronounced. On the other hand, if the 
sliders on that tab are all slid to the 'Opaque' position, you will not see the 
effect at all.

## Additional effects

Additional effects are possible via a file path setting that is accessible in 
the xfce4-settings-editor app (channel: xfwm-effects, property: image-path). 
This allows the user to specify an image to be composited over windows. For 
example, the desktop background image might be a picture of a person, while 
the composited background image might be a picture of a similarly positioned 
skeleton, giving the windows an X-Ray effect. This effect cannot be combined 
with the other 'blurred background' effect. Note that the X-Ray effect's file 
path is ignored if the "Use xlib instead of imlib2..." option is selected 
in the settings app.

## Works with:

Xfwm4 version 4.16. Xfwm4 is the Xfce4 desktop environment's window 
manager. 'xfce4-about' in a terminal to see what version you have.

## Included is:

-xfwm4 (hacked version)
-xfwm-effects (settings app)

## Dependencies are:

Imlib2 (the libimlib2 package) for image processing
 
## Installation and Usage

Before you begin, run Software Updater and install any needed 
updates.

1) extract the archived folder (xfwm-blur-effects-main.zip) containing the 
needed files, which include:

-README.txt
-xfwm4
-xfwm-effects
-xfwm-effects.desktop
-xfwm-effects.glade
-xfwm-effects.svg
-xfwm-effects.xml
-xfwm-effects-install.sh

2) open a terminal window, "cd" to the file path of the install folder you 
just unarchived and type:

sudo bash xfwm-effects-install.sh 
or
sudo ./xfwm-effects-install.sh 

If it doesn't work, then type the below command before bash execution: 

chmod +x xfwm-effects-install.sh 

then enter your password if prompted.

-this script will install the files; user password will be required if 
not root
-it will also install the imlib2 library, needed for image processing, 
using apt-get (it may prompt you to type "y" for "yes" to approve this).


if OS is running on real hardware, log out and log back in at 
this point. This action does not appear to be necessary when OS 
is running on a virtual machine.

3) now to start the effect, in a terminal window, type: 

/usr/local/bin/xfwm4 --replace & disown

Note: the 'replace' part exits the stock window manager (at /usr/bin) 
and starts up the hacked version (at /usr/local/bin/); the 'disown' part 
disconnects the new process from the terminal.

4) start Window Manager Tweaks, select the Compositor tab, select Enable 
Display Compositing, and move the sliders on that tab somewhat closer to 
'Transparent' (since you will not see the effect when they are set at 
'Opaque', which is the default position)

5) Xfwm Effects _works best with dark themes_ (selected in Appearance) 
and dark window frames (selected in Window Manager), so try these first.
A good one is appearance: Adwaita-dark; window manager theme: Default.

Note: keep the 'White amount' slider of the Xfwm Effects panel at zero for 
all dark themes; keep the 'White amount' slider above zero for all light 
themes. This is because the 'White amount' setting not only adjusts the 
amount of white added, but also changes type type of compositing that is 
done (one type favors light themes and one favors dark themes).

Also note: some apps have their own transparency settings, such as Whisker 
menu and the Xfce4 panel. Changing the 'opacity' level for these apps in 
their properties settings will adjust the effect.

## Known issues

Shadows under windows are almost invisible when the slider for frame 
opaqueness in Window Manager Tweaks is set closer to the 'Transparent' 
setting, so you probably won't see shadows under the windows when the 
effect is active.

X-Ray effect file path is ignored if "Use xlib instead of imlib2..." 
setting is selected in the settings app. Also, "Use xlib instead of 
imlib2..." will not work if imlib2 is not installed because imlib2
is not loaded conditionally.

## Troubleshooting / Reverting

If you run into problems, first try logging out and logging back in, 
and if that does not work then try reinstalling xfwm effects.

Note Well: You can restart the original (unmodified) xfwm4 window 
manager at the terminal with:

/usr/bin/xfwm4 --replace & disown

You may need to log out and log back in for it to take effect!

If you wish, you can then delete the "xfwm effects" version of xfwm4 
with:

'sudo rm /usr/local/bin/xfwm4'


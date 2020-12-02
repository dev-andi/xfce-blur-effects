# change application name here (executable output name)
TARGET=xfwm-effects

# binary: usr/local/bin/xfwm-effects
# desktop: usr/local/share/applications/
# gtk docs say 'common location to install UI descriptions and similar data is /usr/(local)/share/appname.' 
# glade: user/local/share/xfwm-effects/xfwm-effects.glade
# icon: usr/local/share/xfwm-effects/xfwm-effects.icon

# install 
PREFIX = $(DESTDIR)/usr/local
BINDIR = $(PREFIX)/bin

DESKTOP_FILE = $(TARGET).desktop
DESKTOP_DIR = $(PREFIX)/share/applications

UI_FILE = $(TARGET).glade
ICON_FILE = $(TARGET).svg
RESOURCE_DIR = $(PREFIX)/share/$(TARGET)


# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall
 
RELEASEFLAGS = -O2 -D NDEBUG -combine -fwhole-program 
 
CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe
 
GTK_CFLAGS = -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include -I/usr/include/gio-unix-2.0/ -I/usr/include/cairo -I/usr/include/libdrm -I/usr/include/pango-1.0 -I/usr/include/harfbuzz -I/usr/include/pango-1.0 -I/usr/include/fribidi -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/uuid -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include

XFCONF_CFLAGS = -I/usr/include/xfce4/xfconf-0

GTK_LIBS = -L/usr/local/lib -L/usr/local/ -L/usr/include/ -lgtk-3 -lgdk-3 -lpango-1.0 -latk-1.0 -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0

XFCONF_LIBS = -L/usr/local/lib -L/usr/local/ -L/usr/include/ -lxfconf-0

POFILES =  am.po ar.po ast.po be.po bg.po bn.po ca.po cs.po da.po de.po el.po en_AU.po en_CA.po en_GB.po eo.po es.po et.po eu.po fi.po fr.po gl.po he.po hr.po hu.po id.po is.po it.po ja.po kk.po ko.po lt.po lv.po ms.po nb.po nl.po nn.po oc.po pa.po pl.po pt_BR.po pt.po ro.po ru.po si.po sk.po sl.po sq.po sr.po sv.po te.po th.po tr.po ug.po uk.po ur_PK.po ur.po vi.po zh_CN.po zh_HK.po zh_TW.po
POSUB = po

# linker
LD=gcc
LDFLAGS= $(GTKLIB) $(GTK_LIBS) $(XFCONF_LIBS) -export-dynamic
 
OBJS=xfwm-effects.o

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)
  
xfwm-effects.o: src/xfwm-effects.c
	$(CC) -c $(CCFLAGS) $(GTK_CFLAGS) $(XFCONF_CFLAGS) src/xfwm-effects.c $(GTKLIB) $(GTK_LIBS) $(XFCONF_LIBS) -o xfwm-effects.o

install: all
	install -D $(TARGET) $(BINDIR)/$(TARGET)
	install -D $(DESKTOP_FILE) $(DESKTOP_DIR)/$(DESKTOP_FILE)
	install -D $(UI_FILE) $(RESOURCE_DIR)/$(UI_FILE)
	install -D $(ICON_FILE) $(RESOURCE_DIR)/$(ICON_FILE)

install-strip: all
	install -D -s $(TARGET) $(BINDIR)/$(TARGET)
	install -D $(DESKTOP_FILE) $(DESKTOP_DIR)/$(DESKTOP_FILE)
	install -D $(UI_FILE) $(RESOURCE_DIR)/$(UI_FILE)
	install -D $(ICON_FILE) $(RESOURCE_DIR)/$(ICON_FILE)

uninstall:
	-rm $(BINDIR)/$(TARGET)
	-rm $(DESKTOP_DIR)/$(DESKTOP_FILE)
	-rm $(RESOURCE_DIR)/$(UI_FILE)
	-rm $(RESOURCE_DIR)/$(ICON_FILE)

clean:
	rm -f *.o $(TARGET)

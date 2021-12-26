#!/bin/bash
# INSTALLER SCRIPT FOR XUBUNTU; OTHER DISTROS WILL NEED CHANGES TO SCRIPT ETC.
# this script installs a hacked xfwm window manager to usr/local/bin 
# (the hack allows for translucency effects); it also installs an app 
# called xfwm-effects to adjust the effect settings

echo "----------------------------------------------------------"
echo "Xfce Effects (v.1.5.0) Install Script for Xubuntu 21.04"
echo "Installing xfwm translucency hack and xfwm-effects panel..."
echo "----------------------------------------------------------"

# install xfwm hack:

# install hacked 'xfwm' to '/usr/local/bin/'
# this will override the original 'xfwm' in '/usr/bin/'
sudo install -D xfwm4 /usr/local/bin/xfwm4
# install 'xfwm-effects.xml' to '/home/user/.config/xfce4/xfconf/xfce-perchannel-xml/'
install -D xfwm-effects.xml ~/.config/xfce4/xfconf/xfce-perchannel-xml/xfwm-effects.xml
# copy /usr/share/xfwm4/defaults to /usr/local/share/xfwm4/defaults
# since /usr/local/bin/xfwm4 will look there instead
install -d /usr/local/share/xfwm4
cp /usr/share/xfwm4/defaults /usr/local/share/xfwm4/defaults

# install xfwm-effects panel app:

# install 'xfwm-effects' binary to 'usr/local/bin/'
install -D xfwm-effects /usr/local/bin/xfwm-effects
# install 'xfwm-effects.desktop' to 'usr/local/share/applications/'
install -D xfwm-effects.desktop /usr/local/share/applications/xfwm-effects.desktop
# install 'xfwm-effects.glade' to 'usr/local/share/xfwm-effects/'
install -D xfwm-effects.glade /usr/local/share/xfwm-effects/xfwm-effects.glade
# install 'xfwm-effects.svg' to 'usr/local/share/xfwm-effects/'
install -D xfwm-effects.svg /usr/local/share/xfwm-effects/xfwm-effects.svg

echo " "
echo "----------------------------------------------------------"
echo "Installing Imlib2 library (for blur effects)..."
echo "----------------------------------------------------------"

# the blur effects are created by Imlib2 library

sudo pacman -Syu imlib2

echo " "
echo "----------------------------------------------------------"
echo "To start modified xfwm4 window manager, run this command: "
echo ""\"""\/"usr"\/"local"\/"bin"\/"xfwm4 --replace & disown"\"" from a terminal."
echo "Note: To switch back to original xfwm4, you can run: " 
echo ""\"""\/"usr"\/"bin"\/"xfwm4 --replace & disown"\"" from a terminal."
echo "----------------------------------------------------------"


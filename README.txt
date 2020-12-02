# Xfwm Effects 1.3

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

Xfwm4 version 4.15.1. Xfwm4 is the Xfce4 desktop environment's window 
manager. 'xfce4-about' in a terminal to see what version you have.

The installer script is written for Xubuntu 20.04; other distros will need 
some massaging to get xfwm-effects to work.

## Included is:

-xfwm4 (hacked version)
-xfwm-effects (settings app)

## Dependencies are:

Imlib2 (the libimlib2 package) for image processing
 
## Installation and Usage

Before you begin, run Software Updater and install any needed 
updates.

1) extract the archived folder (xfwm-effects.tar.gz) containing the 
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
just unarchived:

cd /home/user/Downloads/xfwm-effects-install-1.3

the above is just an example; your "user" is different!

and type:

sudo bash xfwm-effects-install.sh

then enter your password if prompted.

-this script will install the files; user password will be required if 
not root
-it will also install the imlib2 library, needed for image processing, 
using apt-get (it may prompt you to type "y" for "yes" to approve this).

if Xubuntu is running on real hardware, log out and log back in at 
this point. This action does not appear to be necessary when Xubuntu 
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

## How to build from source code (for xfwm4 4.15.1 on Xubuntu 20.04)

I apologize in advance for the following crappy build instructions.

First, download the compressed source code for xfwm4: 
xfwm4-4.15.1.tar.gz 
from https://git.xfce.org/xfce/xfwm4/ and expand it.

Use the following two lines in the terminal:
'sudo apt-get update'
'sudo apt-get install make xfce4-dev-tools libglib2.0-dev xorg-dev libpango1.0-dev libatk1.0-dev libepoxy-dev libatk-bridge2.0-dev libgtk-3-dev libxfce4util-dev libxfce4ui-2-dev libwnck-3-dev gawk libimlib2-dev'

At this point, copy the provided source files (compositor.c, 
screen.c, and screen.h) which are found at 
/xfwm-effects-source/src to the xfwm4-4.xx.x/src folder. 
  
Copy the 'effects' source code folder and paste inside the  
xfwm4-x.xx.x/settings-dialogs/ folder

At the terminal, 'cd' into the expanded xfwm4 source code 
folder (probably named 'xfwm4-4.15.1'), and 'sudo ./configure'

Open the Makefile under src/ with an editor; add the 
Imlib2 library to the end of this line:

COMPOSITOR_LIBS = -lXcomposite -lXdamage -lXfixes

so it looks like:

COMPOSITOR_LIBS = -lXcomposite -lXdamage -lXfixes -lImlib2

and save the change.

Then, to build the hacked xfwm4, 'cd' into the main source 
code folder (probably named 'xfwm4-4.15.1') and

'sudo make && sudo make install'

Next, to build the settings panel (optional) 'cd' into the 
'settings-dialogs/effects' folder of the source code and  
'sudo make && sudo make install' to compile the xfwm-effects 
control panel.

To start and use xfwm-effects, just go to '##Installation and 
Usage' step 3 in this document.

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

## Changelog

1.3 -updated for xfwm4 4.15.1 and Xubuntu 20.04
    -removed clumsy polling of xfconf_settings
    -fixed freeze caused by calling XQueryTree when tree is 
     changing
    -rewrote window painting code with fewer calls
     to xlib
    -note that settings behavior for 'transparency'
     works a little truer to this paradigm now:
     full effect <---------|---------> no effect

1.2 updated for xfwm4 version 4.14.0 and Xubuntu 19.10

1.1 added (experimental) option to use xlib instead of imlib2 for blur
	in the settings app (however, it's slower and requires more cpu)

1.0 initial release

## Contact

jnrh2001(at)yahoo(dot)com

## License

__Xfwm Effects__ License Info (= MIT License)

Copyright 2020 James Hoover

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

__Xfwm4__ License Info

Copied and pasted from the 'compositor.c' source code file...

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., Inc., 51 Franklin Street, Fifth Floor, Boston,
MA 02110-1301, USA.
xcompmgr - (c) 2003 Keith Packard
metacity - (c) 2003, 2004 Red Hat, Inc.
xfwm4    - (c) 2005-2015 Olivier Fourdan

__Imlib2 License__

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies of the Software and its Copyright notices. In addition publicly documented acknowledgment must be given that this software has been used if no source code of this software is made available publicly. Making the source available publicly means including the source for this software with the distribution, or a method to get this software via some reasonable mechanism (electronic transfer via a network or media) as well as making an offer to supply the source on request. This Copyright notice serves as an offer to supply the source on on request as well. Instead of this, supplying acknowledgments of use of this software in either Copyright notices, Manuals, Publicity and Marketing documents or any documentation provided with any product containing this software. This License does not apply to any software that links to the libraries provided by this software (statically or dynamically), but only to the software provided.

Please see the COPYING-PLAIN for a plain-english explanation of this notice and its intent.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

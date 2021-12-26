# Xfwm Effects 1.5

Xfwm Effects adds depth and color harmony to the Xfce4 Desktop Environment 
by modifying the Xfwm4 compositing window manager's code.

## How it works

Xfwm Effects creates an image of the desktop when needed, blurs the 
image, then composites the blurred image onto windows, panels, 
menus, and popovers. The effect is reminiscent of Apple's 'vibrancy' 
effect. Using this method sidesteps the computationally expensive need 
to continually generate gaussian blur.

## A settings adjustment app is included

Also included is the Xfwm Effects app (the binary is called "xfwm-effects") 
that allows the user to turn the effect on and off, to adjust the amount 
of blur, and to adjust the amount of color composited. 

Note: to see the effects, 'Compositor > Enable Display Compositing' must 
be enabled in the Window Manager Tweaks app (because the compositor is 
used to draw the effect). 

Adjusting the sliders on the Compositor tab of the Window Manager Tweaks 
app toward 'Transparent' will make the effect more pronounced. Adjusting 
the sliders toward 'Opaque' will lesson the effect.

## Additional effects

Additional effects are possible via a file path setting that is accessible in 
the xfce4-settings-editor app (channel: xfwm-effects, property: /image-path). 
This allows the user to specify an image to be composited over windows. For 
example, the desktop background image might be a picture of a person, while 
the composited background image might be a picture of a similarly positioned 
skeleton, giving the windows an X-Ray effect. This effect cannot be combined 
with the 'blurred background' effect.

## Works with:

Xfwm4 version 4.16.x. Xfwm4 is the Xfce4 desktop environment's window 
manager. Use 'xfce4-about' in a terminal to see what version you have.

The installer script is written for Xubuntu 21.04; other distros will need 
some massaging to get xfwm-effects to work.

## Included is:

-xfwm4 (hacked version)
-xfwm-effects (settings app)

## Dependencies are:

Imlib2 (the libimlib2 package) for image processing
 
## Installation and Usage

Before you begin, run Software Updater and install any needed 
updates.

1) extract the archived folder (xfwm-effects-install-x.x.tar.gz) 
containing the needed files, which include:

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

cd /home/user/Downloads/xfwm-effects-install-1.5

the above is just an example; your "user" is different!

and type:

sudo bash xfwm-effects-install.sh

then enter your password if prompted.

-this script will install the files; user password will be required if 
not root

-it will also install the imlib2 library, needed for image processing, 
using "apt-get install" (it may prompt you to type "y" for "yes" to 
approve this).

if Xubuntu is running on real hardware, log out and log back in at 
this point. This action does not appear to be necessary when Xubuntu 
is running on a virtual machine.

3) now, to start the effect, in a terminal window, type: 

/usr/local/bin/xfwm4 --replace & disown

Note: the 'replace' part exits the stock window manager (at /usr/bin) 
and starts up the hacked version (at /usr/local/bin/); the 'disown' part 
disconnects the new process from the terminal so you can close it.

Note the additional command line options for vertical sync:

--vblank=off | xpresent | glx

Apparently, the --vblank=xpresent option works best with Intel and 
some AMD graphics chips.
[Source: https://linuxreviews.org/Xfwm4_4.14.3_Is_Released_With_X-Resource_Extension_Support]

4) start the Window Manager Tweaks app, select the Compositor tab, select 
Enable Display Compositing, and move the sliders on that tab somewhat 
closer to 'Transparent' (since you will *not* see the effect when they are 
set at 'Opaque', which is the default position).

Note: Xfwm Effects works best with dark themes (selected in Appearance) 
and dark window frames (selected in Window Manager), so try these first.
A good one is appearance: Adwaita-dark; window manager theme: Default.

5) Use the Xfwm Effects panel (found under Settings in the Whisker menu)
to adjust blur strengh, and color blend. 

Note: It is recommended to keep the 'Color amount' slider of the 
Xfwm Effects panel at zero for dark themes; keep the 'Color amount' 
slider above zero for light themes. This is because the 'Color amount' 
setting not only adjusts the amount of color added (select the color 
using the 'Blend Color' button), but also changes type type of 
compositing that is done (one type favors light themes and one favors 
dark themes).

IMPORTANT: some apps have their own transparency settings, such as 
the Whisker menu, the Xfce4 panel, and the Terminal. Changing the 
'opacity' level for these apps in their properties settings will 
adjust the effect.

## How to build from source code (for xfwm4 4.16.1 on Xubuntu 21.04)

I apologize in advance for the following crappy build instructions.

First, download the compressed source code for xfwm4: 
xfwm4-4.16.1.tar.gz from
https://archive.xfce.org/src/xfce/xfwm4/ by selecting the appropriate 
version, downloading the tarball, and expanding it.

Use the following two lines in the terminal:
'sudo apt-get update'
'sudo apt-get install make xfce4-dev-tools libglib2.0-dev xorg-dev libpango1.0-dev libatk1.0-dev libepoxy-dev libatk-bridge2.0-dev libgtk-3-dev libxfce4util-dev libxfce4ui-2-dev libwnck-3-dev gawk libimlib2-dev libxpresent-dev'

[Note: if support for xpresent is not needed, remove 'libxpresent-dev' 
from the above list.]

At this point, copy the provided source files (compositor.c, screen.c, 
and screen.h) which are found at /xfwm-effects-source/src to the 
xfwm4-4.xx.x/src folder. 
  
Copy the entire 'effects' source code folder found inside the 
'settings-dialogs' folder and paste it inside the 
xfwm4-4.xx.x/settings-dialogs/ folder

At the terminal, 'cd' into the expanded xfwm4 source code 
folder (probably named 'xfwm4-4.16.1'), and 
'sudo ./autogen.sh --enable-xpresent'

[Note Well: ./autogen.sh above might need to be ./configure instead 
depending on the branch and version!]

[Note: if support for xpresent is not needed, use 'sudo ./autogen.sh']

Open the Makefile under src/ with an editor; add the 
Imlib2 library to the end of this line:

COMPOSITOR_LIBS = -lXcomposite -lXdamage -lXfixes

so it looks like:

COMPOSITOR_LIBS = -lXcomposite -lXdamage -lXfixes -lImlib2

and save the change. If the file is write-protected, save to
'Makefile2'; then 'rm Makefile' and 'mv Makefile2 Makefile'.

Then, to build the hacked xfwm4, 'cd' into the main source 
code folder (probably named 'xfwm4-4.16.x') and

'sudo make && sudo make install'

Next, to build the settings panel, 'cd' into the 
'settings-dialogs/effects' folder of the source code and  
'sudo make && sudo make install' to compile the xfwm-effects 
control panel.

To start and use xfwm-effects, go to '##Installation and 
Usage' step 3 in this document. You'll have to change some 
settings to really see the effect.

## Known issues

A couple of people reported that Xfwm Effects ran very slow on their 
graphics cards, even when the effect is off (which should just run 
the unmodified, original code). I don't have an explanation. See the 
'Reverting' section just below for instructions on how to restart 
the original Xfce window manager. Also see the note about the 
--vblank command line option under step 3 above.

Shadows under windows are almost invisible when the slider for frame 
opaqueness in Window Manager Tweaks is set closer to the 'Transparent' 
setting, so you probably won't see shadows under the windows when the 
effect is active.

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

If the revised window manager is truly borked for some reason, as a 
last resort, go to tty2 (control+alt+F2), then log in, then do 
'sudo rm /usr/local/bin/xfwm4' and 
'sudo systemctl restart display-manager' to restart the display 
server so that the original window manager will take over.

## Changelog

1.5.0
	-updated to xfwm4 4.16.1 and Xubuntu 21.04
	-removed "Use Xlib Only" option from Xfwm Effects panel
	-removed some dead code

1.4.1
	-fixed a problem where the xfwm-effects panel controls
	 would be inaccurate on first run
1.4 -updated to xfwm4 4.15.3 and Xubuntu 20.10
	-the Xfwm Effects panel now lets you select a color to blend 
     with light window themes (formerly the blend color was 
     limited to white)
	-build instructions now include xpresent support (for, 
     for example, vertical sync on Intel graphics)
 
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

Copyright 2021 James Hoover

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
xfwm4    - (c) 2005-2020 Olivier Fourdan

__Imlib2 License__

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies of the Software and its Copyright notices. In addition publicly documented acknowledgment must be given that this software has been used if no source code of this software is made available publicly. Making the source available publicly means including the source for this software with the distribution, or a method to get this software via some reasonable mechanism (electronic transfer via a network or media) as well as making an offer to supply the source on request. This Copyright notice serves as an offer to supply the source on on request as well. Instead of this, supplying acknowledgments of use of this software in either Copyright notices, Manuals, Publicity and Marketing documents or any documentation provided with any product containing this software. This License does not apply to any software that links to the libraries provided by this software (statically or dynamically), but only to the software provided.

Please see the COPYING-PLAIN for a plain-english explanation of this notice and its intent.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

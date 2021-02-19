dwm - dynamic window manager
============================
dwm is an extremely fast, small, and dynamic window manager for X.


Requirements
------------
In order to build dwm you need the Xlib header files.


| Program               | Function                                                                     |
________________________________________________________________________________________________________
| nitrogen              | Sets wallpaper.                                                              |
| picom-jonaburg        | X compositor that draws blurring and rounded corners.                        |
| dunst                 | Notification daemon.                                                         |
| KDE polkit            | Policy kit that I use because I install KDE by default                       |
| emacs                 | Optional. My editor of choice, which I run as a daemon for faster launching. |
| volumeicon            | Systray volume control.                                                      |
| networkmanager applet | Systray network management.                                                  |
| zathura               | Fave PDF viewer.                                                             |
| surfraw               | Provides websearch with dmenu                                                |
| xdotool               | Window hide script.                                                          |
| dmenu                 | Awesome dynamic menu program.                                                |
| rofi                  | Application launcher.                                                        |
| xclip                 | Dep for plumbing script.                                                     |
| ranger                | Awesome terminal file manager                                                |
| st                    | My terminal, preferably.                                                     |
| ueberzug              | Image previews in ranger.                                                    |
| R                     | I use Rscript as a calculator.                                               |



Installation
------------
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


Running dwm
-----------
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm


Configuration
-------------
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.


Debian
====================
This directory contains files used to package new808coind/new808coin-qt
for Debian-based Linux systems. If you compile new808coind/new808coin-qt yourself, there are some useful files here.

## new808coin: URI support ##


new808coin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install new808coin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your new808coinqt binary to `/usr/bin`
and the `../../share/pixmaps/new808coin128.png` to `/usr/share/pixmaps`

new808coin-qt.protocol (KDE)


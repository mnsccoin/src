
Debian
====================
This directory contains files used to package mnscd/mnsc-qt
for Debian-based Linux systems. If you compile mnscd/mnsc-qt yourself, there are some useful files here.

## pivx: URI support ##


mnsc-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install mnsc-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your mnsc-qt binary to `/usr/bin`
and the `../../share/pixmaps/pivx128.png` to `/usr/share/pixmaps`

mnsc-qt.protocol (KDE)


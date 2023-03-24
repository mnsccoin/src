
Debian
====================
This directory contains files used to package mnsavingsd/mnsavings-qt
for Debian-based Linux systems. If you compile mnsavingsd/mnsavings-qt yourself, there are some useful files here.

## mnsavings: URI support ##


mnsavings-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install mnsavings-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your mnsavings-qt binary to `/usr/bin`
and the `../../share/pixmaps/mnsavings128.png` to `/usr/share/pixmaps`

mnsavings-qt.protocol (KDE)


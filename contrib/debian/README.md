
Debian
====================
This directory contains files used to package vrontonoded/vrontonode-qt
for Debian-based Linux systems. If you compile vrontonoded/vrontonode-qt yourself, there are some useful files here.

## vrontonode: URI support ##


vrontonode-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install vrontonode-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your vrontonodeqt binary to `/usr/bin`
and the `../../share/pixmaps/vrontonode128.png` to `/usr/share/pixmaps`

vrontonode-qt.protocol (KDE)

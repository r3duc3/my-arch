#!/usr/bin/sh
# https://itsfoss.com/install-pamac-arch-linux/

pkgs="archlinux-appstream-data-pamac libpamac-aur pamac-aur"

sudo pacman -S --needed base-devel git
for pkg in $pkgs; do
	git clone https://aur.archlinux.org/$pkg.git
	cd $pkg
	makepkg -sic
	cd ..
done

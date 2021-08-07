#!/bin/sh
if [ ! -d $HOME/mnt ]; then
	mkdir -p $HOME/mnt
fi
usbdrives="$(lsblk -rpo "name,type,size,mountpoint" | grep 'part\|rom' | awk '$4==""{printf "%s (%s)\n",$1,$3}')"
chosen="$(echo "$usbdrives" | dmenu -i -p "Mount which drive?")" || exit 1
chosen="$(echo "$chosen" | awk '{print $1}')"
md=$(udiskie-mount "$chosen" | awk '{print $4}')
echo $md | xclip -selection clipboard
ln -s $md $HOME/mnt/
notify-send "💻 USB mounting" "$chosen mounted at $md." && exit 0

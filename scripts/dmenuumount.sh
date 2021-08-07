#!/bin/sh

drives=$(lsblk -nrpo "name,type,size,mountpoint" | awk '$4!~/\/boot|\/home$|SWAP/&&length($4)>1{printf "%s (%s)\n",$4,$3}')

[ -z "$drives" ] && echo "No drives to unmount." &&  exit
echo "Unmountable USB drive detected."

[ -z "$drives" ] && exit
chosen="$(echo "$drives" | dmenu -i -p "Unmount which drive?")" || exit 1
chosen="$(echo "$chosen" | awk '{print $1}')"
[ -z "$chosen" ] && exit
udiskie-umount "$chosen" && notify-send "💻 USB unmounting" "$chosen unmounted."
rm $HOME/mnt/${chosen##*/}

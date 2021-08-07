#!/bin/bash
wincache="$HOME/.cache/wincache"
activewin=$(xdotool getactivewindow)

test -f $wincache || touch $wincache

if [ -s $wincache ]; then
	xdotool windowmap $(cat "$wincache")
	rm -f $wincache
	touch $wincache
else
	rm -f $wincache
	touch $wincache
	echo "$activewin" > $wincache
	xdotool windowunmap $activewin
fi

#!/bin/bash
#  ____ _____
# |  _ \_   _|  Derek Taylor (DistroTube)
# | | | || |    http://www.youtube.com/c/DistroTube
# | |_| || |    http://www.gitlab.com/dwt1/
# |____/ |_|
#
# Dmenu script for launching surfaw, a command line search utility.

cmd="dmenu -l 10 -i"
histfile="$HOME/.cache/hist_cache"
query=$@

test -f $histfile || touch $histfile

while [ -z "$engine" ]; do
engine=$(sr -elvi | gawk '{if (NR!=1) { print $1 }}' | $cmd -p "Search engine?") || exit
done

while [ -z "$query" ]; do
query=$(uniq $histfile | $cmd -p "Searching $engine") || exit
done

sr -g "$engine" $query
echo $query >> $histfile

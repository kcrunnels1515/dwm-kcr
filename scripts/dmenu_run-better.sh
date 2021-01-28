#!/bin/sh
# dmenu_run improved

termcmd="alacritty -e"
browsercmd="brave -newtab"
test -s $HOME/.dmenurc && . $HOME/.dmenurc

cmd="$(dmenu_path | dmenu -p "Run " -l 10 $@)"
case $cmd in
    \>* ) ${browsercmd} "$(echo $cmd | sed "s/>//")";; # start your command with > to directly go to the url
    \?* ) ${browsercmd} "https://duckduckgo.com/?q=$(echo $cmd | sed "s/?//")";; # start your command with ? to search on duck duck go
    \/* ) ${browsercmd} "https://www.youtube.com/results?search_query=$(echo $cmd | sed "s/\///")";; # start your command with / to search on youtube
    *\! ) ${termcmd} "$(printf "%s" "${cmd}" | cut -d'!' -f1)";; # end your command with ! to open it in a new terminal window
    * ) ${cmd} ;; #Plane command without any of the above modifications will run as a normal shell command.
esac
unset termcmd
unset browsercmd
exit

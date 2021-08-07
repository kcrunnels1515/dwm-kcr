#!/usr/bin/env bash
init_rx="$(cat /sys/class/net/wlp3s0/statistics/rx_bytes)"
sleep 1
fin_rx="$(cat /sys/class/net/wlp3s0/statistics/rx_bytes)"
printf "%s/s" $(numfmt --to=iec $( expr $fin_rx - $init_rx ))

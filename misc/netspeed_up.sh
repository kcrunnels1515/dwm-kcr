#!/usr/bin/env bash
init_tx="$(cat /sys/class/net/wlp3s0/statistics/tx_bytes)"
sleep 1
fin_tx="$(cat /sys/class/net/wlp3s0/statistics/tx_bytes)"
printf "%s/s" $(numfmt --to=iec $( expr $fin_tx - $init_tx ))

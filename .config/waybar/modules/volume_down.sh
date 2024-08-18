#!/bin/bash

VOLUME=$(pactl get-sink-volume @DEFAULT_SINK@ | awk '{print $5}' | sed 's/%//')
NUMERIC=$((VOLUME-13))

if [ $NUMERIC -gt 0 ]; then
    pactl set-sink-volume @DEFAULT_SINK@ -1% &
fi

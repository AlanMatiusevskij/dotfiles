#!/usr/bin/env sh

killall -q hyprpaper

white pgrep -x hyprpaper >/dev/null; do sleep 1; done

hyprpaper

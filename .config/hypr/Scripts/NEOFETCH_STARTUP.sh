#!/bin/bash

PRINT_NEOFETCH() {
    sleep 1800
    while true; do
        clear
        neofetch --colors 0 --off
        sleep 1800
    done
}

PRINT_NEOFETCH &

while true; do
    clear
    neofetch --colors 0 --off
    echo -e -n "\e[?25l"
    read INPUT
done

#!/bin/bash

#NOTE: this is tailored precisely -and only- for my laptop's speakers.

VOLUME=$(pactl get-sink-volume @DEFAULT_SINK@ | awk '{print $5}' | sed 's/%//')

ICON="err"
NUMERIC=$((VOLUME-13))

MUTE_STATE=$(pactl list sinks | grep -A 15 "Sink #" | grep -A 15 "Analog Stereo" | grep -i "Mute:")
if [ "$NUMERIC" -le 0 ] || echo "$MUTE_STATE" | grep -iq "yes"; then
    ICON=" "
    NUMERIC="0"
else 
    if [ $NUMERIC -gt 0 ] && [ $NUMERIC -le 33 ]; then
        ICON="‣"
    fi

    if [ $NUMERIC -gt 33 ] && [ $NUMERIC -le 66 ]; then 
        ICON="𐰣" #Old Turkic Letter ORKHON AN (the second wave)  
    fi
    
    if [ $NUMERIC -gt 66 ]; then
        ICON="᛫"
    fi
fi

HeadphoneCheck=$(pactl list sinks | grep -i "output-headphones" | grep -i ", available")

if echo "$HeadphoneCheck" | grep -iq "available"; then
    #Audio Device Is Connected
    ICON="᛫$ICON"    
fi
echo -e "{\"text\":\"" $NUMERIC% $ICON"\", \"alt\":\"" $ICON"\",\"tooltip\":\""Volume: $NUMERIC%"\", \"class\":\"""\"}"

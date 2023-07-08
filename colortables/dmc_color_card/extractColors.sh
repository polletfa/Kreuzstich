#!/usr/bin/env bash

#
# Extract the colors from the files in color_card and save
# them in extracted_colors.
# You must specify one of the color_card/*.def files as input
# (each def file defines a column on the color card)
#

if [ "$1" = "" ]; then
    echo "You must specify a *.def file"
    exit 1
fi

. "$1"

x=$STARTX
y=$STARTY
i=0
while [ $i -lt ${#NAMES[@]} ]; do
    if [ $i -lt 10 ]; then
        s="00$i"
    elif [ $i -lt 100 ]; then
        s="0$i"
    else
        s="$i"
    fi
    out="extracted_colors/${COLUMN}_${s}_${NAMES[$i]}.png"
    echo "$out"
    convert "color_card/$FILE" -crop $SIZE+$x+$y "$out"

    y=$(($y+$STEP))
    i=$(($i+1))
done

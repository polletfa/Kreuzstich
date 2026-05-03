#!/usr/bin/env bash

# Kreuzstich
# Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
# MIT License, see LICENSE file.

NAME="$1"
SOURCE="$2"
INTERMEDIATE="$3"
OUTPUT="$4"

INTERMEDIATE_OUTPUT="$INTERMEDIATE/$(basename "$OUTPUT")"

function init {
    mkdir -p "$INTERMEDIATE"
    mkdir -p "$(dirname "$OUTPUT")"
}

function extractColors {
    def=$1

    # Reset variables
    FILE=
    COLUMN=
    SIZE=
    STARTX=
    STARTY=
    STEP=
    NAMES=

    # Load def file
    . "$def"

    if [ -z "$FILE" -o -z "$COLUMN" -o -z "$SIZE" -o -z "$STARTX" -o -z "$STARTY" -o -z "$STEP" -o -z "$NAMES" ]; then
        echo "Invalid def file found: $def"
        continue
    fi

    # Extract colors
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

        out="$INTERMEDIATE/${COLUMN}_${s}_${NAMES[$i]}.png"
        convert "$SOURCE/$FILE" -crop $SIZE+$x+$y "$out"

        y=$(($y+$STEP))
        i=$(($i+1))

        echo -n "."
    done
    echo -n "#"
}

function initFile {
    cat "$SOURCE"/README | while IFS= read line; do
        echo "# $line"
    done
    echo
}

function computeColor {
    file="$1"
    col="$(basename "$file" .png | cut -d_ -f1)"
    num="$(basename "$file" .png | cut -d_ -f2)"
    colornum="$(basename "$file" .png | cut -d_ -f3)"

    color="$(convert "$file" -resize 1x1 -modulate 100,150 txt:- | grep -e '\#[0-9A-F]\{6\}' -o | cut -d# -f2 )"

    if [ "$num" = "000" ]; then
        echo "# $col"
    fi
    echo "$NAME $colornum:$color"
}

function main {
    init

    echo -n "Extracting colors..."
    for def in "$SOURCE"/*.def; do
        extractColors "$def"
    done
    echo

    initFile > "$INTERMEDIATE_OUTPUT"

    echo -n "Compute colors..."
    for file in "$INTERMEDIATE"/*.png; do
        computeColor "$file" >> "$INTERMEDIATE_OUTPUT"
        echo -n "."
    done
    echo

    mv "$INTERMEDIATE_OUTPUT" "$OUTPUT"
}

main

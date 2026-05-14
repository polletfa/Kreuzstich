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
        echo "comment:$line"
    done
    echo "empty"
}

function computeColor {
    file="$1"
    col="$(basename "$file" .png | cut -d_ -f1)"
    num="$(basename "$file" .png | cut -d_ -f2)"
    colornum="$(basename "$file" .png | cut -d_ -f3)"
    color="$(convert "$file" -resize 1x1 -modulate 100,150 txt:- | grep -e '\#[0-9A-F]\{6\}' -o | cut -d# -f2 )"
    if [ "$num" = "000" ]; then
        echo "block:$col"
    fi
    echo "color:$colornum:$color"
}

function preToThreads {
    while IFS= read line; do
        linetype="${line%%:*}"
        linevalue="${line#*:}"
        case "$linetype" in
            "empty")
                echo
                ;;
            "comment"|"block")
                echo "# $linevalue"
                ;;
            "color")
                echo "$NAME $linevalue"
                ;;
        esac
    done
}

function preToSQL {
    blockopen=n
    firstinblock=y
    while IFS= read line; do
        linetype="${line%%:*}"
        linevalue="${line#*:}"
        case "$linetype" in
            "empty")
                echo
                ;;
            "comment")
                echo "-- $linevalue"
                ;;
            "block")
                if [ "$blockopen" = "y" ]; then
                    echo
                    echo ";"
                    firstinblock=y
                else
                    echo "INSERT INTO threadlists(user_id, name) VALUES(NULL, '$NAME');"
                    echo
                fi
                echo "-- $linevalue"
                echo "WITH list AS (SELECT id FROM threadlists WHERE user_id IS NULL AND name = '$NAME')"
                echo "INSERT INTO threads(list_id,name,color) VALUES";
                blockopen=y
                ;;
            "color")
                if [ "$firstinblock" = "y" ]; then
                    firstinblock=n
                else
                    echo ","
                fi
                IFS=: read num color <<< "$linevalue"
                echo -n "    ((SELECT id FROM list), '$NAME $num', '$color')"
                ;;
        esac
    done
    if [ "$blockopen" = "y" ]; then
        echo
        echo ";"
    fi
}

function main {
    init

    echo -n "Extracting colors..."
    for def in "$SOURCE"/*.def; do
        extractColors "$def"
    done
    echo

    initFile > "$INTERMEDIATE_OUTPUT".pre

    echo -n "Compute colors..."
    for file in "$INTERMEDIATE"/*.png; do
        computeColor "$file" >> "$INTERMEDIATE_OUTPUT".pre
        echo -n "."
    done
    echo

    echo "Creating $OUTPUT.threads..."
    preToThreads < "$INTERMEDIATE_OUTPUT".pre > "$INTERMEDIATE_OUTPUT".threads && \
        mv "$INTERMEDIATE_OUTPUT".threads "$OUTPUT".threads

    echo "Creating $OUTPUT.sql..."
    preToSQL < "$INTERMEDIATE_OUTPUT".pre > "$INTERMEDIATE_OUTPUT".sql && \
        mv "$INTERMEDIATE_OUTPUT".sql "$OUTPUT".sql
}

main

#!/usr/bin/env bash

#
# Create a list from the files in extracted_colors
# Use --html to generate a HTML page. Otherwise the output is a
# *.colors text file.
#

namePrefix="DMC "
type=txt

if [ "$1" = "--html" ]; then
    type=html
    echo "<html><body><table>"
fi

for i in extracted_colors/*.png; do
    col="$(basename "$i" .png | cut -d_ -f1)"
    num="$(basename "$i" .png | cut -d_ -f2)"
    colornum="$(basename "$i" .png | cut -d_ -f3)"
    name="$namePrefix$colornum"

    intensity="$(convert "$i" -colorspace HSI -resize 1x1 txt:- |tail -n1|cut -d, -f4|cut -d% -f1|cut -d. -f1)"

    # For image with high intensity, we increase the brightness to compensate
    # for the shadows
    increase_brightness="$(($intensity / 5))"

    color="$(convert "$i" -resize 1x1 -brightness-contrast $increase_brightness -modulate 100,150 txt:- | grep -e '\#[0-9A-F]\{6\}' -o | cut -d# -f2 )"

    if [ "$type" = "txt" ]; then
        if [ "$num" = "000" ]; then
            echo "# $col" >&2
            echo "# $col"
        fi
        echo "$name:$color"
    else
        if [ "$num" = "000" ]; then
            echo "# $col" >&2
            echo "<tr><th colspan=\"2\">$col</th></tr>"
        fi
        echo "<tr><td>$name</td><td bgcolor=\"#$color\" width=\"100px\">&nbsp;</td></tr>"
    fi
done

if [ "$type" = "html" ]; then
    echo "</table></body></html>"
fi

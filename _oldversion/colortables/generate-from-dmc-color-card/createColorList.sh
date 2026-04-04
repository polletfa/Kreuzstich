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
else
    echo "#"
    echo "# Generated from pictures of the DMC color card"
    echo "#"
    echo
fi

for i in extracted_colors/*.png; do
    col="$(basename "$i" .png | cut -d_ -f1)"
    num="$(basename "$i" .png | cut -d_ -f2)"
    colornum="$(basename "$i" .png | cut -d_ -f3)"
    name="$namePrefix$colornum"

    color="$(convert "$i" -resize 1x1 -modulate 100,150 txt:- | grep -e '\#[0-9A-F]\{6\}' -o | cut -d# -f2 )"

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

#!/bin/bash

function generate-colortable() {
    name="$1"; shift
    filename="$1"; shift
    echo "Color table for $name (../$filename.colors)"
    (
        echo "#"
        echo "# Color table for $name"
        echo "# Created using the conversion tables at "
        echo "# http://www.cyberstitchers.com/stitching_tools/floss_conversion_charts"
        echo "#"
        cat $* | ./extract.pl "$name"
    ) > ../"$filename".colors
}
generate-colortable Anchor anchor anchor1 anchor2
generate-colortable DMC dmc dmc1 dmc2
generate-colortable Bucilla bucilla bucilla1 bucilla2
generate-colortable Candamar candamar candamar1
generate-colortable "Design Works Crafts" designworks designworks1
generate-colortable "Dimensions" dimensions dimensions1
generate-colortable "J & P Coats" jpcoats jpcoats1 jpcoats2
generate-colortable Sullivans sullivans sullivans1

#!/bin/bash

MODE="$1"; shift
if [ "$MODE" != "debug" -a "$MODE" != "release" ]; then
    echo "Syntax:"
    echo "   $0 debug|release [<make arguments>]"
    echo
    echo "Run cmake for the specified build and call make with the specified arguments"
    exit 1
fi
cmake -B _build/$MODE -DCMAKE_BUILD_TYPE=$MODE
(
    cd _build/$MODE
    make $*
)

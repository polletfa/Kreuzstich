#!/bin/bash

# Kreuzstich
# Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
# MIT License, see LICENSE file.

MODE="$1"; shift
if [ "$MODE" != "debug" -a "$MODE" != "release" ]; then
    echo "Syntax:"
    echo "   $0 debug|release [<make arguments>]"
    echo
    echo "Run cmake for the specified build and call make with the specified arguments"
    echo
    echo "Useful targets:"
    echo "  all          Build everything"
    echo "  unittests    Build unit tests"
    echo "  test         Run unit tests (no rebuild)"
    echo "  coverage     Build, run test and create coverage report"
    exit 1
fi
cmake -B build/$MODE -DCMAKE_BUILD_TYPE=${MODE^}
(
    cd build/$MODE
    make $*
)

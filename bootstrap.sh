#!/bin/bash

(
    cd $(dirname $0)

    mkdir -p build/debug
    (
        cd build/debug
        cmake -DCMAKE_BUILD_TYPE=Debug ../..
    )

    mkdir -p build/release
    (
        cd build/release
        cmake -DCMAKE_BUILD_TYPE=Release ../..
    )
)

echo
echo "To build in DEBUG mode:   cd build/debug/ && make"
echo "To build in RELEASE mode: cd build/release/ && make"

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

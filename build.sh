#!/bin/bash

case $1 in
    "clean")
        rm -rf build
        exit 0
        ;;
    "*")
        echo "Nothing to do"
        exit 0
        ;;
esac

mkdir -p build
cd build && cmake .. && make

#!/bin/bash

function help {
    cat <<EOF
    Usage:
    -b set buildsystem (MAKE or NINJA), defaults to MAKE
    -c erase the build directory
    -h help
EOF
}

BUILDSYS=MAKE

while getopts ":b:ch" opt; do
    case $opt in
        b)
            BUILDSYS=$OPTARG
            ;;
        c)
            rm -rf build
            exit 0
            ;;
        h)
            help
            exit 0
            ;;
        \?)
            echo "Invalid option: -$OPTARG" >&2
            help
            exit 1
            ;;
        :)
            echo "Option -$OPTARG requires an argument" >&2
            help
            exit 1
            ;;
    esac
done

mkdir -p build

#TODO use multiple jobs for make
if [ "$BUILDSYS" == "MAKE" ] ; then
    cd build && cmake .. && make
elif [ "$BUILDSYS" == "NINJA" ] ; then
    cd build && cmake -GNinja .. && ninja -v
else
    echo "Invalid buildsystem $BUILDSYS specified - should be one of [MAKE, NINJA]" >&2
fi

exit 0

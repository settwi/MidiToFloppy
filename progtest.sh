#!/bin/sh

MTOF=mtof
CLEANOUTS=clean

if [ ! -e "$MTOF" ]; then
    echo "HERE"
    exit 1
fi

make $CLEANOUTS

for d in */; do
    for f in $d*.mid; do
        if [ -e "$f" ]; then
            ./mtof $f $(basename $f) 
            if (( $? )); then
                echo "Error: file $f"
            fi
        fi
    done
done

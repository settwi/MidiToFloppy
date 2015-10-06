#!/bin/bash

MTOF=mtof
CLEANOUTS=clean

if [ ! -e "$MTOF" ]; then
    exit 1
fi

make $CLEANOUTS

for d in ./music/**/; do
    for f in $d*.mid; do
        if [ -e "$f" ]; then
	    fn=$(basename $f)
            ./mtof $f ${fn%%.*} 
            if (( $? )); then
                echo "Error: file $f"
            fi
        fi
    done
done

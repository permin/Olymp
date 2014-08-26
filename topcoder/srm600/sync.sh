#!/bin/bash

for i in $@;
do
    for c in 500 1000;
    do
        cp 250/${i} ${c}/${i}
    done;
done;

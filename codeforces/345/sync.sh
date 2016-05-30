#!/bin/bash

for i in $@;
do
    for c in B C D E F G H I J K L;
    do
        cp A/${i} ${c}/${i}
    done;
done;

#!/bin/bash

make $1

for x in `ls t[0-9]`; do
    echo '====================='$x'====================='
    cat $x | ./problem
done;
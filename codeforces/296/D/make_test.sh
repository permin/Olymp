#!/bin/bash

make prod

for x in `ls t[0-9]`; do
    echo '====================='$x'====================='
    cat $x | ./problem
done;
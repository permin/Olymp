#!/bin/bash

for x in `ls t[0-9]`; do
    echo '====================='$x'====================='
    cat $x | ./solution.py
done;

#!/bin/bash -e

#7z x inputs_test.zip

make

for x in `ls pap*.in`; do
    y=`echo $x | sed -e 's/in/out/g'`
    printf "\033[0;34m${x}\033[0m\n"
    cat $x | ./problem > $y
    printf "\033[0;32mDone!\033[0m\n"
done;

zip answer.zip *.out

printf "\033[0;32mSolved!\033[0m\n"

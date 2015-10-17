#!/bin/bash -e

#7z x inputs_test.zip

NAME=""
FROM="01"
TO="99"

make

for x in `ls ${NAME}*.in`; do
    if [[ ! "$x" < "${NAME}${FROM}.in" && ! "$x" > "${NAME}${TO}.in" ]]; then
        y=`echo $x | sed -e 's/in/out/g'`
        printf "\033[0;34m${x}\033[0m\n"
        cat $x | ./problem > $y
        printf "\033[0;32mDone!\033[0m\n"
    fi
done;

zip answer.zip *.out

printf "\033[0;32mSolved!\033[0m\n"
ls -lh answer.zip

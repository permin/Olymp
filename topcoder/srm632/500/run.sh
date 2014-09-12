#!/bin/sh
if [ "$1" -z ]
then
    make && ./problem
else
    make && $1 ./problem
fi

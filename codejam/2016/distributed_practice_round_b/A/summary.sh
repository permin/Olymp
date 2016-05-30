#!/bin/sh -e

TESTS=$1
NAME=$2

for test in `seq ${TESTS}`;\
do HEADERNAME="${NAME}-${test}.h"; \
  echo '------------------------------'
  cat $HEADERNAME

done
echo '------------------------------'




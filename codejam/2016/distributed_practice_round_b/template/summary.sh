#!/bin/sh -e

TESTS=TESTS_NUMBER
NAME=PROBLEM_NAME

for test in `seq ${TESTS}`;\
do HEADERNAME="${NAME}-${test}.h"; \
  echo '------------------------------'
  cat $HEADERNAME

done
echo '------------------------------'




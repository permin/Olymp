#!/bin/sh -e

TESTS=$1
NAME=$2
NODES=$3


for test in `seq ${TESTS}`;\
do BINARYNAME=problem-${test}; \
  echo '------------------------------'
  echo "Running ${BINARYNAME} ..."; \
  ../../../distributed_testing_tool/dcj.sh run --executable=./${BINARYNAME} \
    --nodes=${NODES} --output=all
done
echo '------------------------------'



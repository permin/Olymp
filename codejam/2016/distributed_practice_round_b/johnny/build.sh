#!/usr/local/bin/bash -e

TESTS=$1
NAME=$2

function safe_run {
    "$@"
    local status=$?
    if [ $status -ne 0 ]; then
        echo "error with $1" >&2
    fi
    return $status
}

for test in `seq ${TESTS}`;\
  do BINARYNAME=problem-${test}; \
  CPPNAME=${BINARYNAME}.cpp; \
  echo "Compiling ${CPPNAME} into ${BINARYNAME} ..."; \
  sed "s/#include \"${NAME}.h\"/#include \"${NAME}-${test}.h\"/g" problem.cpp > ${CPPNAME};
  safe_run ../../../distributed_testing_tool/dcj.sh build --source=${CPPNAME};

done

wait
echo "Everything is built!"


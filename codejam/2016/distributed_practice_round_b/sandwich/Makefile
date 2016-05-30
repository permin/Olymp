TESTS=3
NAME=sandwich
NODES=2

all:
	./build.sh 1 ${NAME}

test:
	./build.sh ${TESTS} ${NAME} &&	./make_test.sh ${TESTS} ${NAME} ${NODES}

tidy:
	~/Documents/Olymp/tidy-olymp.sh problem.cpp

summary:
	./summary.sh  ${TESTS} ${NAME}

clean:
	rm -f *.pyc \
	rm problem-* \
	rm problem-*.cpp



all:
	g++-4.9 problem.cpp -o problem -std=c++0x -Wpedantic -Wextra -Wall -Warray-bounds -Wmaybe-uninitialized -Wmaybe-uninitialized -Wuninitialized -Werror -Wno-sign-compare  -D_GLIBCXX_DEBUG  -DLOCAL_RUN -O2
test:
	./make_test.sh
clean:
	rm -f *.pyc \
	rm problem


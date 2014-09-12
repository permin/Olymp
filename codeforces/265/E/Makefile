all:
	g++-4.9 problem.cpp -o problem -std=c++0x -O3 -Wpedantic -Wextra -Wall -Warray-bounds -Wmaybe-uninitialized -Wmaybe-uninitialized -Wuninitialized -Werror -Wno-sign-compare -DLOCAL_RUN
test:
	./make_test.sh
clean:
	rm -f *.pyc \
	rm problem


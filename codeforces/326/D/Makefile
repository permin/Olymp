all:
	clang++ -O2 -std=c++11 -stdlib=libc++ -DLOCAL_RUN problem.cpp -o problem

prod:
	g++-4.9 problem.cpp -o problem -O2 -Wall -Werror -Wextra -Wno-sign-compare -fwhole-program -std=c++14 -DLOCAL_RUN2

test:
	./make_test.sh
clean:
	rm -f *.pyc \
	rm problem


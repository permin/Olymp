all:
	g++-4.9 problem.cpp -o problem   -fno-stack-limit -O2 -Wall -Warray-bounds -Wcast-align -Wconversion -Werror -Wextra -Wfloat-equal -Wlogical-op -Wmaybe-uninitialized -Wno-sign-compare -Wpedantic -pedantic -Wuninitialized -fsanitize=undefined -fstack-protector -std=c++14 -fno-omit-frame-pointer -time -D_FORTIFY_SOURCE=2 -D_GLIBCXX_DEBUG_PEDANTIC -DLOCAL_RUN

prod:
	g++-4.9 problem.cpp -o problem -O2 -Wall -Werror -Wextra -Wno-sign-compare -std=c++14 -DLOCAL_RUN

tidy:
	~/Documents/Olymp/tidy-olymp.sh problem.cpp

test:
	./make_test.sh
clean:
	rm -f *.pyc \
	rm problem


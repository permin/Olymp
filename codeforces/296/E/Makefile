all:
	g++-4.9 problem.cpp -o problem -O2 -Wall -Warray-bounds -Wcast-align -Wconversion -Werror -Wextra -Wfloat-equal -Wlogical-op -Wmaybe-uninitialized -Wno-sign-compare -Wpedantic -pedantic -Wuninitialized -fsanitize=address -fsanitize=undefined -fstack-protector -fwhole-program -std=c++14 -fno-omit-frame-pointer -time -D_FORTIFY_SOURCE=2 -D_GLIBCXX_DEBUG_PEDANTIC -DLOCAL_RUN
prod:
	g++-4.9 problem.cpp -o problem -O2 -Wall -Warray-bounds -Wcast-align -Wconversion -Werror -Wextra -Wfloat-equal -Wlogical-op -Wmaybe-uninitialized -Wno-sign-compare -Wpedantic -pedantic -Wuninitialized -fstack-protector -fwhole-program -std=c++14 -fno-omit-frame-pointer -time -D_FORTIFY_SOURCE=2 -D_GLIBCXX_DEBUG_PEDANTIC -DLOCAL_RUN
prod2:
	g++-4.9 problem.cpp -o problemm -O2 -Wall -Werror -Wextra -Wno-sign-compare -fwhole-program -std=c++14


test:
	./make_test.sh
clean:
	rm -f *.pyc \
	rm problem


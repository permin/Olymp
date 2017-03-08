all:
	g++-6 problem.cpp -o problem -fno-stack-limit -O2 -Wall -Warray-bounds -Wcast-align -Wconversion -Werror -Wextra -Wfloat-equal -Wlogical-op -Wmaybe-uninitialized -Wno-sign-compare -Wpedantic -pedantic -Wuninitialized -fsanitize=undefined -fstack-protector -std=c++1z -fno-omit-frame-pointer -time -D_FORTIFY_SOURCE=2 -D_GLIBCXX_DEBUG_PEDANTIC -DLOCAL_RUN2

clang:
	clang problem.cpp -o problem -O2 -Wall -Warray-bounds -Wcast-align -Wconversion -Werror -Wextra -Wno-unused-const-variable -Wno-sign-conversion -Wfloat-equal -Wuninitialized -Wno-sign-compare -Wpedantic -pedantic -Wuninitialized -fsanitize=undefined -fstack-protector -std=c++1z -fno-omit-frame-pointer -D_FORTIFY_SOURCE=2 -D_GLIBCXX_DEBUG_PEDANTIC -DLOCAL_RUN

prod:
	g++-6 problem.cpp -o problem -O2 -Wall -Werror -Wextra -Wno-sign-compare -std=c++1z -DLOCAL_RUN2

tidy:
	~/Documents/Olymp/tidy-olymp.sh problem.cpp

test:
	./make_test.sh all

clean:
	rm -f *.pyc \
	rm problem




# Set the command for your C++ compiler, and specify any compiler flags you
# want to use (e.g. -g -Werror).
CXX		= g++-4.9
CXXFLAGS	= -O2 -Wall -Warray-bounds -Wcast-align -Wconversion -Werror -Wextra -Wfloat-equal -Wlogical-op -Wmaybe-uninitialized -Wno-sign-compare -Wpedantic -pedantic -Wuninitialized -fsanitize=address -fsanitize=undefined -fstack-protector -fwhole-program -std=c++14 -fno-omit-frame-pointer -time -D_FORTIFY_SOURCE=2 -D_GLIBCXX_DEBUG_PEDANTIC -DLOCAL_RUN

# The driver outputs TAP (Test Anything Protocol), so it can also be used with
# any TAP test harness (e.g. prove).  Set the path to your test harness here,
# then use the `prove' target to run the tests with that harness.
PROVE		= prove
PROVEFLAGS	= -e ""


ifeq ($(OS),Windows_NT)
EXEEXT = .exe
endif


all: driver$(EXEEXT)

clean:
	rm -f driver$(EXEEXT)

distclean: clean
	rm -f LittleElephantAndBallsAgain

run: all
	./driver$(EXEEXT)

test: all
	./driver$(EXEEXT) --abort-on-fail

prove: all
	$(PROVE) $(PROVEFLAGS) ./driver$(EXEEXT)


%$(EXEEXT): %.cc
	$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

driver$(EXEEXT): LittleElephantAndBallsAgain.cc

.PHONY: all clean distclean run test prove

# vim:ft=make:noet:ts=8

#!/usr/bin/python

import random
import sys
import time
import subprocess
import resource
from termcolor import colored, cprint
import os
from optparse import OptionParser


def print_lines(string, max_num=10):
    lines = string.split('\n')
    if len(lines) <= max_num:
        for l in lines:
            print l
    else:
        first = max_num / 2
        last = max_num - first
        for l in lines[:first]:
            print l
        print '...(%d lines skipped)...' % (len(lines) - max_num)
        for l in lines[-last:]:
            print l


def main():
    '''
        a) set params string
        b) implement gen_test.py
    '''
    parser = OptionParser()
    parser.add_option("--seed", dest="initial_seed",
                      default=0,
                      help="initial seed")
    parser.add_option("--no-stdout",
                      action="store_false", dest="print_stdout", default=True,
                      help="don't print stdout of ./problem")
    parser.add_option("--no-stderr",
                      action="store_false", dest="print_stderr", default=True,
                      help="don't print stderr of ./problem")
    parser.add_option("--time-limit",
                      dest="time_limit",
                      default=1.0,
                      type=float,
                      help="time limit in seconds")
    parser.add_option("--full-stdout",
                      action="store_true", dest="full_stdout", default=False,
                      help="print full stdout of ./problem")
    parser.add_option("--full-stderr",
                      action="store_true", dest="full_stderr", default=False,
                      help="print full stderr of ./problem")

    (options, args) = parser.parse_args()

    initial_seed = options.initial_seed
    time_limit = options.time_limit
    print time_limit

    # TODO set!

    oks = 0
    tls = 0
    res = 0

    for seed in range(initial_seed, initial_seed + 10):
        print '=' * 80
        print "Seed = %d" % seed
        random.seed(seed)
        #### TODO set!
        n = 800 * 1000
        m = 10**5

        params = (n, m)
        ####

        cprint("test info:", attrs=['bold'])
        print "Generator params: %s" % str(params)
        test = subprocess.check_output(
            ["./gen_test.py", "%d" % seed] + [str(x) for x in params], stderr=subprocess.PIPE)

        (utime, stime, cutime, cstime, elapsed_time) = os.times()
        p = subprocess.Popen(["./problem"],
                             stdin=subprocess.PIPE,
                             stdout=subprocess.PIPE,
                             stderr=subprocess.PIPE,
                             bufsize=1)
        (stdout, stderr) = p.communicate(test)
        returncode = p.wait()
        (utime1, stime1, cutime1, cstime1, elapsed_time1) = os.times()
        #print "Return Code = %d" % returncode
        print
        if options.print_stdout:
            cprint("stdout:", attrs=['bold'])
            if options.full_stdout:
                print stdout
            else:
                print_lines(stdout)
        if options.print_stderr:
            cprint("stderr:", attrs=['bold'])
            if options.full_stderr:
                print stderr
            else:
                print_lines(stderr)
        time_spent = (cutime1 + cstime1 -
                      cutime - cstime)
        if returncode == 0:
            time_color = 'blue'
            if time_spent > time_limit:
                time_color = 'red'
                tls += 1
            else:
                oks += 1
            cprint("%0.2f sec." % time_spent,
                   time_color, attrs=['bold'])
        else:
            cprint("Crash!", 'red', attrs=['bold'])
            res += 1

    print '=' * 80
    cprint("OK:", 'green', attrs=['bold'], end=' ')
    cprint("%d" % oks, attrs=['bold'])
    cprint("TL:", 'red', attrs=['bold'], end=' ')
    cprint("%d" % tls, attrs=['bold'])
    cprint("RE:", 'red', attrs=['bold'], end=' ')
    cprint("%d" % res, attrs=['bold'])

main()

#!/usr/bin/python

from optparse import OptionParser
import os
import sys
import shutil
import subprocess


import build


def run_test(test_id, nodes, flags):
    print '=' * 80
    p = subprocess.Popen(
        [os.path.join(build.config['path_to_dcj.sh'], 'executable', 'parunner'),
         "-n=%d" % nodes,
         "-stdout=tagged",
         "-stderr=tagged"
         ] + flags +
        ["problem-%d" % test_id],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        bufsize=1)
    (stdout, stderr) = p.communicate()
    print stdout,
    print >>sys.stderr, stderr,
    returncode = p.wait()
    return returncode


def main():
    parser = OptionParser()
    parser.add_option("--name", dest="problem_name",
                      help="problem_name", metavar="problem_name",
                      default='gas_stations.h')
    parser.add_option('-t', "--tests",
                      dest="tests",
                      default="1-3",
                      type=str,
                      help="tests")
    parser.add_option('-n', "--nodes",
                      dest="nodes",
                      default="2",
                      type=int,
                      help="nodes")
    parser.add_option(
        '-s', '--stat',
        action='store_true',
        dest="print_stat",
        help='-print_stats',
        default=False)
    parser.add_option(
        '--trace',
        action='store_true',
        dest="trace_comm",
        help='--trace_comm',
        default=False)

    (options, args) = parser.parse_args()
    flags = []
    if options.print_stat:
        flags.append('-print_stats=true')
    if options.trace_comm:
        flags.append('-trace_comm=true')

    for t in build.get_list_of_test_ids(options.tests):
        print "Test id: %d" % t
        r = build.make(options.problem_name, t)
        if r != 0:
            sys.exit(r)
        r = run_test(t, options.nodes, flags)
        if r != 0:
            sys.exit(r)
        print

    pass

if __name__ == '__main__':
    main()

#!/usr/bin/python

from optparse import OptionParser
import os
import sys
import shutil
import subprocess

from config import config


def get_list_of_test_ids(str):
    def f(s):
        if '-' in s:
            a, _, b = s.partition('-')
            return range(int(a), 1 + int(b))
        else:
            return [int(s)]
    return reduce(list.__add__,
                  (f(s) for s in str.split(',')), [])


def make(problem_name, test_id):

    #test = subprocess.check_output(
    #    stderr=subprocess.PIPE)
    #subproces

    print '=' * 80
    link_name = '%s.h' % problem_name

    os.remove(link_name)
    os.symlink('%s-%d.h' % (problem_name, test_id), link_name)
    p = subprocess.Popen([os.path.join(config['path_to_dcj.sh'], "dcj.sh"),
                          "build", "--source=%s" % config['cpp_name']],
                         stdin=subprocess.PIPE,
                         stdout=subprocess.PIPE,
                         stderr=subprocess.PIPE,
                         bufsize=1)
    (stdout, stderr) = p.communicate()
    print stdout,
    print >>sys.stderr, stderr,
    returncode = p.wait()
    os.remove(link_name)
    os.symlink('%s-1.h' % (problem_name), link_name)
    if returncode == 0:
        shutil.move('problem', 'problem-%d' % test_id)
    return returncode


def main():
    parser = OptionParser()
    parser.add_option("--name", dest="problem_name",
                      help="problem_name", metavar="problem_name",
                      default='gas_stations.h')
    parser.add_option('-t', "--tests",
                      dest="tests",
                      default="1",
                      #default="1-3",
                      type=str,
                      help="tests")
    (options, args) = parser.parse_args()

    for t in get_list_of_test_ids(options.tests):
        print "Test id: %d" % t
        r = make(options.problem_name, t)
        if r != 0:
            sys.exit(r)
        print


if __name__ == '__main__':
    main()
    #print get_list_of_test_ids('1,4-22')

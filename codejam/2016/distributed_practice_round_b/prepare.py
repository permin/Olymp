#!/usr/bin/python

from optparse import OptionParser
import os
import sys
import shutil


def main():
    parser = OptionParser()
    parser.add_option("--name", dest="problem_name",
                      help="problem_name", metavar="problem_name", default=None)
    parser.add_option("--tests",
                      dest="tests_number", default=3,
                      type=int,
                      help="Number of tests")

    (options, args) = parser.parse_args()

    template_folder = 'template'
    downloads_folder = '/Users/permin/Downloads/'
    files = ['problem.cpp', 'Makefile', 'build.sh', 'make_test.sh', 'run.sh']
    replaces = {'PROBLEM_NAME': options.problem_name,
                'TESTS_NUMBER': str(options.tests_number)}

    print >>sys.stderr, 'Creating folder [%s] ...' % options.problem_name
    os.mkdir(options.problem_name)
    for name in files:
        print >>sys.stderr, 'Creating file [%s] ...' % name
        source_name = os.path.join(template_folder, name)
        target_name = os.path.join(options.problem_name, name)
        with open(source_name, "r") as source:
            with open(target_name, "w") as target:
                data = source.read()
                for placeholder in replaces:
                    value = replaces[placeholder]
                    data = data.replace(placeholder, value)
                target.write(data)
        shutil.copymode(source_name, target_name)
    for test_id in range(1, options.tests_number + 1):
        source = os.path.join(downloads_folder, "%s%s.h" % (
            options.problem_name,
            '' if test_id == 1 else "-%d" % test_id,
        ))
        target = os.path.join(options.problem_name, '%s-%d.h' %
                              (options.problem_name, test_id))

        print >>sys.stderr, 'Copy test header from %s to %s ...' % (
            source, target)
        if test_id == 1:
            link_name = os.path.join(options.problem_name, "%s.h" % (
                options.problem_name))
            link_content = '%s-1.h' % options.problem_name
            print >>sys.stderr, 'Making symlink %s pointing to %s ...' % (
                link_name, link_content)
            os.symlink(link_content, link_name)

        shutil.copy(source, target)


main()

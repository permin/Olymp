#!/usr/bin/python

from optparse import OptionParser
import os
import sys
import shutil
from config import config


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
    downloads_folder = config['path_to_downloaded_headers']
    files = [config['cpp_name'],
             'build.py',
             'run.py',
             'Makefile',
             '../config.py']
    replaces = {'PROBLEM_NAME_PLACEHOLDER': options.problem_name,
                'TESTS_NUMBER_PLACEHOLDER': str(options.tests_number)}

    print >>sys.stderr, 'Creating folder [%s] ...' % options.problem_name
    os.mkdir(options.problem_name)
    for name in files:
        source_name = os.path.join(template_folder, name)
        target_name = os.path.join(
            options.problem_name,
            name.split('/')[-1])
        print >>sys.stderr, 'Creating file [%s] from [%s] ...' % (
            target_name, source_name)
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

        print >>sys.stderr, 'Copying test header from [%s] to [%s] ...' % (
            source, target)
        if test_id == 1:
            link_name = os.path.join(options.problem_name, "%s.h" % (
                options.problem_name))
            link_content = '%s-1.h' % options.problem_name
            print >>sys.stderr, 'Making symlink [%s] pointing to [%s] ...' % (
                link_name, link_content)
            os.symlink(link_content, link_name)

        shutil.copy(source, target)


main()

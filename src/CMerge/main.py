#!/bin/python3.5
import os
import argparse
import re


def get_src_path():
    """
    Get the source directory
    :return:
    """
    return os.path.abspath('../')


def get_ccore():
    """
    Get the CCore source code.

    The exporter is NOT included in this, as it has a large dependency on json.
    :return:
    """
    files = [
        'Directions.h',
        'Point.h',
        'Point.cpp',
        'PrimalityTester.h',
        'PrimalityTester.cpp',
        'Path.h',
        'Path.cpp',
        'Progress.h',
        'Progress.cpp',
        'CCore.h',
        'CCore.cpp',
    ]

    source = ''

    for file in files:

        with open(os.path.join(get_src_path(), 'CCore', file), 'r') as f:

            source += f.read()
            f.close()

    return source


def get_exercise(name):
    """
    Get the source for a single exercise
    :param name:
    :return:
    """
    name = name.upper()

    if name not in ('C1', 'C2', 'C3', 'C4'):
        raise Exception('Exercise {} not known'.format(name))

    source = ''

    with open(os.path.join(get_src_path(), name, 'main.cpp'), 'r') as f:
        source += f.read()
        f.close()

    return source


def remove_relative_imports(source):
    """
    Remove all the relative imports from the source code
    :param source:
    :return:
    """
    return re.sub(r"^#include \"(.+)\"$", "", source, flags=re.MULTILINE)


if __name__ == '__main__':

    parser = argparse.ArgumentParser(description='Merge CCore and an exercise into a single file.')

    # Exercise
    parser.add_argument(
        '-e',
        '--exercise',
        help='The exercise to use, possible values are: C1, C2, C3 and C4',
        required=False)

    # File
    parser.add_argument(
        '-f',
        '--file',
        help='The file to print to. If empty, output will be printed to stdout',
        required=False
    )

    # Human readable
    parser.add_argument(
        '--human',
        action='store_true',
        default=False,
        help='Turns human messages on (Extra output). DOES CREATE INVALID OUTPUT FOR THE OLYMPIADE.',
        required=False
    )

    args = parser.parse_args()

    while not args.exercise:
        args.exercise = input('The exercise to use, possible values are: C1, C2, C3, C4: ')

    source = get_ccore() + get_exercise(args.exercise)
    source = remove_relative_imports(source)

    if args.human:
        source = '#define HUMAN_MESSAGES\n' + source

    while not args.file:
        args.file = input('The file to write to: ')

    with open(args.file, 'w') as f:
        f.write(source)
        f.close()

    print('Done!')

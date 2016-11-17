#!/bin/python
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
    Get the CCore source code
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
        'CCore.h',
        'CCore.cpp'
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
    parser.add_argument('-e', '--exercise', help='The exercise to use, possible values are: C1, C2, C3 and C4')
    parser.add_argument('-f', '--file', help='The file to print to. If empty, output will be printed to stdout')

    args = parser.parse_args()

    while not args.exercise:

        args.exercise = input('The exercise to use, possible values are: C1, C2, C3, C4: ')

    source = get_ccore() + get_exercise(args.exercise)
    source = remove_relative_imports(source)

    if args.file:
        with open(args.file, 'w') as f:
            f.write(source)
            f.close()
    else:
        print(source)

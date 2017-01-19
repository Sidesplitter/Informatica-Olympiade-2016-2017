#!/bin/python3.5
import os
import argparse
import re


def get_src_path() -> str:
    """
    Get the source directory
    :return:
    """
    path = os.path.abspath('../')

    if path.split('/')[-1] != 'src':
        path = os.path.abspath(os.path.join('.', 'src'))

    return path


def get_ccore() -> str:
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
        'WorkDivider.h',
        'WorkDivider.cpp',
        'CCore.h',
        'CCore.cpp',
    ]

    source = ''

    for file in files:

        with open(os.path.join(get_src_path(), 'CCore', file), 'r') as f:

            source += f.read()
            f.close()

    return source


def get_exercise(name: str) -> str:
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


def remove_relative_imports(source) -> str:
    """
    Remove all the relative imports from the source code
    :param source:
    :return:
    """
    return re.sub(r"^#include \"(.+)\"$", "", source, flags=re.MULTILINE)


def main():

    parser = argparse.ArgumentParser(description='Merge CCore and an exercise into a single file. Prints the output to'
                                                 'stdout')

    # Exercise
    parser.add_argument(
        'exercise',
        help='The exercise to use, possible values are: C1, C2, C3 and C4',
        type=lambda value: value.upper(),
        choices=['C1', 'C2', 'C3', 'C4']
    )

    # Human readable
    parser.add_argument(
        '-hm',
        '--human',
        action='store_true',
        default=False,
        help='Turns human messages on (Extra output). DOES CREATE INVALID OUTPUT FOR THE OLYMPIADE.',
        required=False
    )

    # Human readable
    parser.add_argument(
        '-mt',
        '--multi-threaded',
        action='store_true',
        default=False,
        help='Turns on multi threaded processing for the CCore library. DOES NOT WORK BY DEFAULT FOR THE OLYMPIADE',
        required=False
    )

    args = parser.parse_args()

    source = get_ccore() + get_exercise(args.exercise)
    source = remove_relative_imports(source)

    if args.human:
        source = '#define HUMAN_MESSAGES\n' + source

    if args.multi_threaded:
        source = '#define MULTI_THREADING\n' + source

    source = '/**\n' \
             ' * (C) Jord Nijhuis 2017\n\n' \
             ' * This is the merged source of CCore and {exercise}. The language is C++11\n' \
             ' * This code is merged with multi-threading option {multi_threading}.\n' \
             ' * A faster processor does improve the performance regardless of multi-threading.\n' \
             ' * The Human option was turned {human}.\n'\
             ' */\n\n'.format(
                exercise=args.exercise,
                multi_threading='ON, meaning that multiple cores improve the performance.\n'
                ' * Make sure that when compile this file, std::async is available'
                ' (for g++ add -pthread to the arguments)'
                if args.multi_threaded else
                'OFF',
                human='ON, this will generate additional output, but does mark the exercise as\n '
                      '* invalid for the grader.'
                if args.human else 'OFF'
            ) + source

    print(source)


if __name__ == '__main__':
    main()

#!/usr/bin/env python3
"""
Generates a ctag file for the given target.

Does not handle header files currently.
"""

import argparse
import subprocess
import re
import glob


def parse_args():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("target")

    return parser.parse_args()


def main():
    args = parse_args()

    packages = set()

    dep = subprocess.check_output(
        "newt target dep {}".format(args.target).split())

    for line in dep.decode().splitlines()[1:]:
        res = re.search('\* (@?[\w/-]+)', line)
        if not res:
            import pdb
            pdb.set_trace()
        pkg = res.groups(1)[0]

        packages.add(pkg)

    packages = list(packages)
    packages.sort()

    print("Found the following:\n{}".format('\n'.join(packages)))

    files = []

    for pkg in packages:
        if pkg.startswith('@'):
            pkg = pkg.replace('@', 'repos/', 1)
        files += glob.glob(pkg + '/src/**/*.c', recursive=True)
        files += glob.glob(pkg + '/include/**/*.h', recursive=True)

    subprocess.call('ctags --extra=+f'.split() + files)


if __name__ == '__main__':
    main()

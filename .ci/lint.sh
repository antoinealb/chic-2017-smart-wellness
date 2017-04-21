#!/usr/bin/env bash

cd $(dirname $0)/..
./beautify

if [ ! -z $(git diff-index --name-only HEAD --) ]
then
    echo "Some files were changed by uncrustify, raising an error!"
    git diff
    exit 1
fi

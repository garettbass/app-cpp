#!/usr/bin/env bash
set -e
testdir="$(cd "$(dirname "$0")" && pwd)"
testrun="$testdir/testrun"

CXX="clang++ -std=c++11 -Wall -g"
FRAMEWORKS="-framework CoreFoundation -framework Foundation -framework Cocoa"

rm -f "$testrun"
$CXX $CXXFLAGS $FRAMEWORKS "$testdir/main.cpp" -o "$testrun"

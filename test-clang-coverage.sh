#!/bin/bash
# argument should be the cpp file for testing a single module
clang++-18 -g -O0 -coverage -Wall -Wextra -Wpedantic -std=c++23 -Iinclude "$1" && \
./a.out "${@:2}" && \
rm -r ./tmp && \
mkdir ./tmp && \
gcovr --gcov-executable "llvm-cov-18 gcov" --html-details tmp/index.html && \
rm ./*.gcda ./*.gcno

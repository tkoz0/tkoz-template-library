#!/bin/bash
# argument should be the cpp file for testing a single module
clang++ -g -O0 -Wall -Wextra -Wpedantic -std=c++23 -Iinclude "$1" && \
./a.out "${@:2}"

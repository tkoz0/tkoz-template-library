#!/bin/bash
# argument should be the cpp file for testing a single module
clang++ -g -O0 -Wall -Wextra -Werror -std=c++23 -Iinclude "$1" && \
valgrind --leak-check=full --track-origins=yes ./a.out "${@:2}"

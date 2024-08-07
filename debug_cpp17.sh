#!/bin/bash
g++ -g -Wall -Wextra -Werror -std=c++17 $1 && valgrind --leak-check=full --track-origins=yes ./a.out ${@:2}

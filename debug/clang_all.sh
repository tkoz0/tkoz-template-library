#!/bin/bash
./debug_clang_cpp11.sh "$@" && \
./debug_clang_cpp14.sh "$@" && \
./debug_clang_cpp17.sh "$@" && \
./debug_clang_cpp20.sh "$@" && \
./debug_clang_cpp23.sh "$@"

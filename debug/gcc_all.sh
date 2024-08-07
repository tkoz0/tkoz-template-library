#!/bin/bash
./debug_gcc_cpp11.sh "$@" && \
./debug_gcc_cpp14.sh "$@" && \
./debug_gcc_cpp17.sh "$@" && \
./debug_gcc_cpp20.sh "$@" && \
./debug_gcc_cpp23.sh "$@"

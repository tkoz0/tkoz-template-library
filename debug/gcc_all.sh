#!/bin/bash -x
SDIR=$(dirname "$0")
"$SDIR/gcc_cpp11.sh" "$@" && \
"$SDIR/gcc_cpp14.sh" "$@" && \
"$SDIR/gcc_cpp17.sh" "$@" && \
"$SDIR/gcc_cpp20.sh" "$@" && \
"$SDIR/gcc_cpp23.sh" "$@"

#!/bin/bash -x
SDIR=$(dirname "$0")
"$SDIR/clang_cpp11.sh" "$@" && \
"$SDIR/clang_cpp14.sh" "$@" && \
"$SDIR/clang_cpp17.sh" "$@" && \
"$SDIR/clang_cpp20.sh" "$@" && \
"$SDIR/clang_cpp23.sh" "$@"

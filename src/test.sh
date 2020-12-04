#!/bin/bash

# Echo any provided arguments.
# [ $# -gt 0 ] && echo "#:$# 1:$1 2:$2 3:$3"

SKELETON="${1:-skeleton}"

testDefault()
{
  assertEquals $'Welcome to skeleton.' \
    "$(${SKELETON})"
}

# Eat all command-line arguments before calling shunit2.
shift $#
if [ "$(uname)" == "Darwin" ]; then
. /usr/local/bin/shunit2
elif [ "$(uname)" == "Linux" ]; then
# Linux
. shunit2
# TODO no shunit2 on windows/msys2/mingw64 platform
fi

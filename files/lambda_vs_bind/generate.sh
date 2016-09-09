#!/bin/sh
mkdir -p stats_gcc
CC=g++ CXX_FLAGS='-Os -std=c++11 -Wall -Wextra -pedantic' OUT_FILE=stats_gcc/sizes make
CC=g++ CXX_FLAGS='-Os -std=c++11 -Wall -Wextra -pedantic -fno-rtti' OUT_FILE=stats_gcc/sizes_no_rtti make
CC=g++ CXX_FLAGS='-Os -std=c++11 -Wall -Wextra -pedantic -fno-rtti -fno-exceptions' OUT_FILE=stats_gcc/sizes_no_rtti_no_exceptions make
g++ --version > stats_gcc/cc_version.txt

if [ -n "$(command -v clang++)" ]; then
  mkdir -p stats_clang
  CC=clang++ CXX_FLAGS='-Os -std=c++11 -Wall -Wextra -pedantic' OUT_FILE=stats_clang/sizes make
  CC=clang++ CXX_FLAGS='-Os -std=c++11 -Wall -Wextra -pedantic -fno-rtti' OUT_FILE=stats_clang/sizes_no_rtti make
  CC=clang++ CXX_FLAGS='-Os -std=c++11 -Wall -Wextra -pedantic -fno-rtti -fno-exceptions' OUT_FILE=stats_clang/sizes_no_rtti_no_exceptions make
  clang++ --version > stats_clang/cc_version.txt
fi

#! /usr/bin/env bash
if [ ! -d "build" ]; then
	mkdir build
fi

rm BMtoBMPCpp
rm BMtoBMPCpp_*

cd build

echo "Building Linux executable."
rm -f CMakeCache.txt
cmake ..
make full

echo "Building x86_64 Windows executable."
rm -f CMakeCache.txt
cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/mingw-w64-x86_64.cmake ..
make

echo "Building i686 Windows executable."
rm -f CMakeCache.txt
cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/mingw-w64-i686.cmake ..
make

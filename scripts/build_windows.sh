#! /bin/sh

cd ../
rm -r build
mkdir build && cd build

cmake ../pitch -BwindowBuild \
	-DCMAKE_TOOLCHAIN_FILE=./scripts/win64.cmake \
	-DCMAKE_SYSTEM_NAME=win64 \

cmake --build windowBuild --config Release 

#! /bin/sh

cd ../
rm -r build
mkdir build && cd build 

cmake ../pitch -BlinuxBuild \
	-DCMAKE_SYSTEM_NAME=linux \

cmake --build linuxBuild --config Release

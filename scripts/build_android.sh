#! /bin/sh

# NDK_ROOT=/Users/good/Documents/ABV/Android/android-ndk-r16b r10e r21e

NDK_ROOT=/Users/good/Documents/ABV/Android/android-ndk-r16b
export PATH=$NDK_ROOT:$PATH

cd ../
rm -r build
mkdir build && cd build 

cmake ../pitch -Barm64-v8a \
	-DCMAKE_ANDROID_API=21 \
	-DCMAKE_SYSTEM_NAME=android \
	"-DCMAKE_ANDROID_ARCH_ABI=arm64-v8a"  \
	-DCMAKE_ANDROID_NDK=$NDK_ROOT \
	-DCMAKE_BUILD_TYPE=Release \
	-DCMAKE_ANDROID_NDK_TOOLCHAIN_VERSION=clang \
	-DCMAKE_ANDROID_STL_TYPE=gnustl_static \
	-DCMAKE_ANDROID_SKIP_ANT_STEP=1 \

# make -j8
cmake --build arm64-v8a --config Release 

cmake ../pitch -Barmeabi-v7a \
	-DCMAKE_SYSTEM_NAME=android \
	"-DANDROID_ABI=armeabi-v7a"  \
	"-DCMAKE_ANDROID_ARCH_ABI=armeabi-v7a"  \
	-DANDROID_NDK=$NDK_ROOT \
	-DCMAKE_ANDROID_NDK=$NDK_ROOT \
	-DANDROID_TOOLCHAIN=clang \
	-DANDROID_NATIVE_API_LEVEL=21 \
	-DASSIMP_BUILD_TESTS=OFF \
	-DASSIMP_NO_EXPORT=TRUE \
	-DANDROID_ARM_NEON=TRUE	 \
	-DCMAKE_ANDROID_STL_TYPE=gnustl_static \


# make -j8
cmake --build armeabi-v7a --config Release 

cmake ../pitch -Barmeabi \
	-DCMAKE_SYSTEM_NAME=android \
	"-DANDROID_ABI=armeabi"  \
	"-DCMAKE_ANDROID_ARCH_ABI=armeabi"  \
	-DANDROID_NDK=$NDK_ROOT \
	-DCMAKE_ANDROID_NDK=$NDK_ROOT \
	-DANDROID_TOOLCHAIN=clang \
	-DANDROID_NATIVE_API_LEVEL=21 \
	-DASSIMP_BUILD_TESTS=OFF \
	-DASSIMP_NO_EXPORT=TRUE \
	-DANDROID_ARM_NEON=TRUE	 \
	-DCMAKE_ANDROID_STL_TYPE=gnustl_static \


# make -j8
cmake --build armeabi --config Release 











	


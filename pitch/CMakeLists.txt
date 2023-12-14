cmake_minimum_required(VERSION 3.5)
project(pitch)

aux_source_directory(vector vector)
aux_source_directory(util util)
aux_source_directory(dsp dsp)
aux_source_directory(. SOURCES)

list(APPEND SOURCES ${vector} ${util} ${dsp} )

if(${CMAKE_SYSTEM_NAME} MATCHES "iOS")
	set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -DHAVE_ACCELERATE")

	# set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")

	add_library(pitch
				${SOURCES})

	target_link_libraries(pitch
						"-framework Accelerate")

	install(TARGETS pitch DESTINATION lib)

elseif (${CMAKE_SYSTEM_NAME} MATCHES "darwin")
	set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -DHAVE_ACCELERATE")

	add_library(pitch
				SHARED
				${SOURCES})

	target_link_libraries(pitch
						"-framework Accelerate")

	install(TARGETS pitch DESTINATION lib)

elseif (${CMAKE_SYSTEM_NAME} MATCHES "android")
	set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -std=c99 ")

	# strip
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")

	# add dylib, include source path
	add_library(pitch
				SHARED
				${SOURCES})

	# search system lib, ndk-10e is not support
	find_library( # Sets the name of the path variable.
				syslibs
				log 
				android)

	install(TARGETS pitch DESTINATION lib)

elseif (${CMAKE_SYSTEM_NAME} MATCHES "linux")
	set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ")

	# add so, include source path
	add_library(pitch
				SHARED
				${SOURCES})

	install(TARGETS pitch DESTINATION lib)

elseif (${CMAKE_SYSTEM_NAME} MATCHES "win64")
	# -Wl,-rpath=. 
	# -Wl,--out-implib,./pitch.lib  MSVC lib
	set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wl,-rpath=.  ")

	set(BUILD_SHARED_LIBS true)
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)
	
	link_directories(${PROJECT_SOURCE_DIR})
	include_directories(${PROJECT_SOURCE_DIR})

	# add so, include source path
	add_library(pitch
				SHARED
				${SOURCES})

	install(TARGETS pitch DESTINATION lib)

endif()







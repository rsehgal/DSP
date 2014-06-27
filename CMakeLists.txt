cmake_minimum_required(VERSION 2.8)
set(OUTDIR ${PROJECT_SOURCE_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTDIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTDIR}/bin)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} $ENV{HOME}/cmake/modules)
find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIR})

include_directories(inc)

#############################################################
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()
#############################################################

file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h)
#file(GLOB libsources src/*.cpp)
#
#message(STATUS "----------------------")
#message(STATUS ${headers})
#message(STATUS "----------------------")
#if( MAKELIB )
#	add_library(DSP SHARED ${headers}) # ${libsources})
#	target_link_libraries(DSP ${ROOT_LIBRARIES} -lEG -lGeom)
#	SET_TARGET_PROPERTIES(DSP PROPERTIES LINKER_LANGUAGE CXX)
#endif( MAKELIB )

#include_directories(inc)
#file(GLOB testsources DSP.cpp)

file(GLOB testsources tests/*.cpp)
if( MAKETEST )
foreach( test ${testsources} )
        get_filename_component( TESTEXEC ${test} NAME_WE)
        add_executable(${TESTEXEC} ${BASEFLAGS} ${test} src/MemoryMapped.cpp)
		#target_link_libraries( ${TESTEXEC} ${ROOT_LIBRARIES} "-lSpectrum" ) #-L${CMAKE_LIBRARY_OUTPUT_DIRECTORY} -lDSP")
		#target_link_libraries(${TESTEXEC} "-L${CMAKE_LIBRARY_OUTPUT_DIRECTORY} -lhelperClass")
endforeach( test )
endif( MAKETEST )

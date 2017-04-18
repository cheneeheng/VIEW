cmake_minimum_required(VERSION 2.8)

project(VIEW)

add_compile_options(-std=c++11)

set(GSL_LIBS_DIR "/home/chen/gsl/lib")
set(GSL_INCLUDE_DIR "/home/chen/gsl/include")

set(GCC_GDB_COMPILE_FLAGS "-g")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_GDB_COMPILE_FLAGS}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY /home/chen/HMAR/KINECT/Build)

#add_compile_options(-std=c++11)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

include_directories( 
	${GSL_INCLUDE_DIR})

link_directories( 
	${GSL_LIBS_DIR})

add_executable( VIEW
	./src/util.cpp
	./src/vtkExtra.cpp
	./src/algo.cpp
	./src/main.cpp)

target_link_libraries( VIEW 
	${VTK_LIBRARIES}
	gsl gslcblas)



#message("CMAKE_CXX_FLAGS is ${CMAKE_CXX_FLAGS}")
#message("CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_CXX_FLAGS_DEBUG}")
#message("CMAKE_CXX_FLAGS_RELEASE is ${CMAKE_CXX_FLAGS_RELEASE}")
#message("CMAKE_CXX_FLAGS_RELWITHDEBINFO is ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
#message("CMAKE_CXX_FLAGS_MINSIZEREL is ${CMAKE_CXX_FLAGS_MINSIZEREL}")

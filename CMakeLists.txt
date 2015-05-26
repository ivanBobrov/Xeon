cmake_minimum_required(VERSION 2.8.11)

project(XeonSolver)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

if ( WIN32 )
	set(CMAKE_GENERATOR_TOOLSET "Intel C++ Compiler XE 14.0" CACHE STRING "Platform Toolset" FORCE)
	add_definitions(-DMIC_TARGET)
	add_definitions(-DMKL)
	set(CMAKE_CXX_FLAGS "/Qopenmp /GR-")
else()
	set(CMAKE_CXX_FLAGS "-fopenmp")
endif()

subdirs(src)
#main library

set(MAIN_SOURCE "" PARENT_SCOPE)
set(MAIN_INCLUDE_DIRS "" PARENT_SCOPE)

add_subdirectory(matrix)
add_subdirectory(solver)

add_library(xeonSolverLib ${MAIN_SOURCE})
target_include_directories(xeonSolverLib PUBLIC ${MAIN_INCLUDE_DIRS})

#if ( WIN32 )
#	set(CMAKE_CXX_FLAGS "-Qopenmp")
#else()
#	set(CMAKE_CXX_FLAGS "-fopenmp")
#endif()

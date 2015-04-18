#test executables

set(TEST_SOURCES "" PARENT_SCOPE)
set(TEST_INCLUDE_DIRS "" PARENT_SCOPE)

add_subdirectory(test)
add_subdirectory(unit)

add_executable(testXeonSolverLib ${TEST_SOURCES})
target_include_directories(testXeonSolverLib PUBLIC ${TEST_INCLUDE_DIRS})
target_link_libraries(testXeonSolverLib xeonSolverLib)
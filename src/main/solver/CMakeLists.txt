#Solver module /src/main/solver/CMakeLists.txt

set(SOLVER_SOURCE "" PARENT_SCOPE)
set(SOLVER_INCLUDE_DIRS "" PARENT_SCOPE)

add_subdirectory(sequential)
add_subdirectory(superLU)
add_subdirectory(pcr)

set(MAIN_INCLUDE_DIRS
    ${MAIN_INCLUDE_DIRS}
    ${SOLVER_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    PARENT_SCOPE
)

set(MAIN_SOURCE
    ${MAIN_SOURCE}
    ${SOLVER_SOURCE}
    PARENT_SCOPE
)
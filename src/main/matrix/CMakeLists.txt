set(MAIN_INCLUDE_DIRS
    ${MAIN_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    PARENT_SCOPE
)

set(MAIN_SOURCE
    ${MAIN_SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/HarwellBoeingMatrix.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ArraySquareMatrix.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TridiagonalMatrix.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ArrayVector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MatrixUtils.cpp
    PARENT_SCOPE
)
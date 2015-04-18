#Matrix test module

set(TEST_TEST_SOURCE
    ${TEST_TEST_SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/MatrixTests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ArraySquareMatrixTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ArrayVectorTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HarwellBoeingMatrixTest.cpp
    PARENT_SCOPE
)

set(TEST_TEST_INCLUDE_DIRS
    ${TEST_TEST_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    PARENT_SCOPE
)

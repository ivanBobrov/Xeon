#include "ArraySquareMatrixTest.h"

ArraySquareMatrixTest::ArraySquareMatrixTest() {
    info = "No info. Run test first.";
}

std::string ArraySquareMatrixTest::getInfo() {
    return info;
}

bool ArraySquareMatrixTest::runTests() {
    return arraySquareMatrixTest();
}

bool ArraySquareMatrixTest::arraySquareMatrixTest() {
    ISquareMatrix * matrix = new ArraySquareMatrix(TEST_SIZE);

    bool result = MatrixTests::arbitraryMatrixTest(matrix);
    info = result ? "ArraySquareMatrix test: SUCCESS" : "ArraySquareMatrix test: FAILED";

    return result;
}

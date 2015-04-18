#include "ArrayVectorTest.h"

ArrayVectorTest::ArrayVectorTest() {
    info = "No info. Run test first.";
}

std::string ArrayVectorTest::getInfo() {
    return info;
}

bool ArrayVectorTest::runTests() {
    return runVectorTest();
}

bool ArrayVectorTest::runVectorTest() {
    IVector *vector = new ArrayVector(TEST_SIZE);

    bool result = MatrixTests::arbitraryVectorTest(vector);
    info = result ? "ArrayVector test: SUCCESS" : "ArrayVector test: FAILED";

    return result;
}
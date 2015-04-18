#ifndef ARRAY_SQUARE_MATRIX_TEST_H
#define ARRAY_SQUARE_MATRIX_TEST_H

#include <string>
#include <TestCase.h>
#include <ArraySquareMatrix.h>

#include "MatrixTests.h"

class ArraySquareMatrixTest : public TestCase {
private:
    static const int TEST_SIZE = 30;
    std::string info;

public:
    ArraySquareMatrixTest();
    virtual bool runTests();
    virtual std::string getInfo();

    bool arraySquareMatrixTest();
};

#endif
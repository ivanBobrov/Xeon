#ifndef HARWELL_BOEING_MATRIX_TEST_H
#define HARWELL_BOEING_MATRIX_TEST_H

#include <string>
#include <TestCase.h>
#include <HarwellBoeingMatrix.h>
#include <ISquareMatrix.h>
#include <MatrixUtils.h>
#include "MatrixTests.h"

class HarwellBoeingMatrixTest : public TestCase {
private:
    static const int DEFAULT_TEST_SIZE = 100;
    std::string info;

public:
    HarwellBoeingMatrixTest();

    bool setGetTest();
    bool setGetRandomTest();
    bool matrixConstructorTest();
    virtual std::string getInfo();
    virtual bool runTests();
};

#endif
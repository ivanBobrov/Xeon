#ifndef ARRAY_VECTOR_TEST_H
#define ARRAY_VECTOR_TEST_H

#include <string>
#include <TestCase.h>
#include <ArrayVector.h>

#include "MatrixTests.h"

class ArrayVectorTest : public TestCase {
private:
    static const int TEST_SIZE = 100;
    std::string info;

public:
    ArrayVectorTest();
    virtual bool runTests();
    virtual std::string getInfo();

    bool runVectorTest();
};

#endif
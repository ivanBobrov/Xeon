#ifndef MATRIX_TESTS
#define MATRIX_TESTS

#include <string>

#include <IMatrix.h>
#include <ISquareMatrix.h>
#include <IVector.h>
#include <MatrixUtils.h>
#include <ArraySquareMatrix.h>
#include <ArrayVector.h>
#include <TestCase.h>

class MatrixTests : public TestCase {
private:
    std::string info;

public:
    static bool arbitraryMatrixTest(IMatrix* matrix);
    static bool arbitraryVectorTest(IVector* vector);

    MatrixTests();

    virtual bool runTests();
    virtual std::string getInfo();
    bool squareMatrixProductTest();
    bool squareMatrixVectorProduct();
};


#endif
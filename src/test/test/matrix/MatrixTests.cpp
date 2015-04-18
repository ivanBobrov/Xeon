#include "MatrixTests.h"

//TODO: You shouldn't compare doubles through operator ==

bool MatrixTests::arbitraryMatrixTest(IMatrix * matrix) {
    int rowSize = matrix->rowCount();
    int colSize = matrix->columnCount();

    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            matrix->set(i, j, i + 5 + j*j);
        }
    }

    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            double expectedValue = i + 5 + j*j;
            double actualValue = matrix->get(i, j);
            if (expectedValue - actualValue > 0.0000001) {
                return false;
            }
        }
    }

    return true;
}

bool MatrixTests::arbitraryVectorTest(IVector *vector) {
    int vSize = vector->size();
    
    for (int i = 0; i < vSize; i++) {
        vector->set(i, i*i + 10);
    }
    
    for (int i = 0; i < vSize; i++) {
        double expectedValue = i*i + 10;
        double actualValue = vector->get(i);
        if (expectedValue - actualValue > 0.0000001) {
            return false;
        }
    }

    return true;
}

MatrixTests::MatrixTests() {
    info = "No info. Run test first.";
}

std::string MatrixTests::getInfo() {
    return info;
}


bool MatrixTests::runTests() {
    std::string outInfo = "";
    bool result;

    result = squareMatrixProductTest();
    outInfo.append(info);
    result &= squareMatrixVectorProduct();
    outInfo.append("\n").append(info);

    info = outInfo;
    return result;
}


bool MatrixTests::squareMatrixProductTest() {
    //TODO: make non square matrices test
    IMatrix *matrixA = new ArraySquareMatrix(3);
    IMatrix *matrixB = new ArraySquareMatrix(3);

    IMatrix *expected = new ArraySquareMatrix(3);
    IMatrix *actual   = new ArraySquareMatrix(3);

    matrixA->set(0, 0, -7); matrixA->set(0, 1, 5); matrixA->set(0, 2, 9);
    matrixA->set(1, 0, -1); matrixA->set(1, 1, 3); matrixA->set(1, 2, 1);
    matrixA->set(2, 0, 4);  matrixA->set(2, 1, 9); matrixA->set(2, 2, 0);

    matrixB->set(0, 0, 3); matrixB->set(0, 1, -2); matrixB->set(0, 2, 7);
    matrixB->set(1, 0, 2); matrixB->set(1, 1, -5); matrixB->set(1, 2, 0);
    matrixB->set(2, 0, 1);  matrixB->set(2, 1, 5); matrixB->set(2, 2, 2);

    expected->set(0, 0, -2); expected->set(0, 1, 34);  expected->set(0, 2, -31);
    expected->set(1, 0, 4);  expected->set(1, 1, -8);  expected->set(1, 2, -5);
    expected->set(2, 0, 30); expected->set(2, 1, -53); expected->set(2, 2, 28);

    MatrixUtils::product(matrixA, matrixB, actual);

    if (MatrixUtils::compare(expected, actual, 0.0000001)) {
        info = "SquareMatrixProduct test: SUCCESS";
        return true;
    } else {
        info = "SquareMatrixProduct test: FAILED";
        return false;
    }
}


bool MatrixTests::squareMatrixVectorProduct() {
    IMatrix *matrix = new ArraySquareMatrix(3);
    IVector *vector = new ArrayVector(3);

    IVector *expected = new ArrayVector(3);
    IVector *actual = new ArrayVector(3);

    matrix->set(0, 0, 1); matrix->set(0, 1, -1); matrix->set(0, 2, -9);
    matrix->set(1, 0, 4); matrix->set(1, 1, 5);  matrix->set(1, 2, 8);
    matrix->set(2, 0, 3); matrix->set(2, 1, -3); matrix->set(2, 2, 1);

    vector->set(0, 1); vector->set(1, 7); vector->set(2, 2);
    expected->set(0, -24); expected->set(1, 55); expected->set(2, -17);

    MatrixUtils::product(matrix, vector, actual);

    if (MatrixUtils::compare(expected, actual, 0.0000001)) {
        info = "Matrix to vector product test: SUCCESS";
        return true;
    } else {
        info = "Matrix to vector product test: FAILED";
        return false;
    }

}

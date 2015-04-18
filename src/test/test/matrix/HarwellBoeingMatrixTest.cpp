#include "HarwellBoeingMatrixTest.h"

HarwellBoeingMatrixTest::HarwellBoeingMatrixTest() {
    info = "No info. Run test first.";
}

std::string HarwellBoeingMatrixTest::getInfo() {
    return info;
}

bool HarwellBoeingMatrixTest::runTests() {
    std::string outInfo = "";
    bool result;

    result = setGetTest();
    outInfo.append(info);
    result &= setGetRandomTest();
    outInfo.append("\n").append(info);
    result &= matrixConstructorTest();
    outInfo.append("\n").append(info);

    info = outInfo;
    return result;
}

bool HarwellBoeingMatrixTest::setGetTest() {
    ISquareMatrix *matrix = new HarwellBoeingMatrix(DEFAULT_TEST_SIZE);

    bool result = MatrixTests::arbitraryMatrixTest(matrix);
    info = result ? "HarwellBoeingMatrix arbitrary test: SUCCESS" : "HarwellBoeing arbitrary test: FAILED";

    return result;
}


bool HarwellBoeingMatrixTest::setGetRandomTest() {
    ISquareMatrix *matrix = new HarwellBoeingMatrix(DEFAULT_TEST_SIZE);
    srand((unsigned int)time(NULL));

    for (int test = 0; test < DEFAULT_TEST_SIZE * DEFAULT_TEST_SIZE; test++) {
        int i = rand() % DEFAULT_TEST_SIZE;
        int j = rand() % DEFAULT_TEST_SIZE;
        double value = (double) rand();

        matrix->set(i, j, value);
        double actual = matrix->get(i, j);
        if (actual != value) {
            info = "HarwellBoeingMatrix random get/set test: FAILED";
            return false;
        }
    }

    info = "HarwellBoeingMatrix random get/set test: SUCCESS";
    return true;
}


bool HarwellBoeingMatrixTest::matrixConstructorTest() {
    ISquareMatrix *matrix = new ArraySquareMatrix(DEFAULT_TEST_SIZE);
    MatrixUtils::fillRandomMatrix(matrix);
    HarwellBoeingMatrix *hbMatrix = new HarwellBoeingMatrix(matrix, 10);

    if (MatrixUtils::compare(matrix, hbMatrix, 10)) {
        info = "HarwellBoeingMatrix constructor test: SUCCESS";
        return true;
    } else {
        info = "HarwellBoeingMatrix constructor test: FAILED";
        return false;
    }
}

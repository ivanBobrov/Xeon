#ifndef SEQUENTIAL_SOLVER_TEST_H
#define SEQUENTIAL_SOLVER_TEST_H

#include <matrix.h>
#include <IMatrix.h>
#include <ISquareMatrix.h>
#include <IVector.h>
#include <TestCase.h>
#include <ArraySquareMatrix.h>
#include <ArrayVector.h>
#include <SequentialSolver.h>
#include "SolverTests.h"

class SequentialSolverTest : public TestCase {
private:
    std::string info;

public:
    SequentialSolverTest();

    bool runTests();
    std::string getInfo();

    bool sequentialSolverTest();
};

#endif
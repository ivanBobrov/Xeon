#ifndef SOLVER_TESTS_H
#define SOLVER_TESTS_H

#include <IMatrix.h>
#include <ArraySquareMatrix.h>
#include <IVector.h>
#include <ArrayVector.h>
#include <AbstractSolver.h>
#include <MatrixUtils.h>

class SolverTests {
private:
    static const int TEST_SIZE = 50;

public:
    static bool abstractSolverTest(AbstractSolver *unpreparedSolver);
};

#endif
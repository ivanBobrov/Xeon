#ifndef SUPER_LU_SOLVER_TEST_H
#define SUPER_LU_SOLVER_TEST_H

#include "TestCase.h"
#include <matrix.h>
#include <solver.h>

class SuperLUSolverTest : public TestCase {
private:
    static const int MATRIX_SIZE = 100;
    std::string info;

    bool checkSolver();

public:
    SuperLUSolverTest();

    bool runTests();
    std::string getInfo();

};

#endif

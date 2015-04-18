#include "SolverTests.h"

bool SolverTests::abstractSolverTest(AbstractSolver *unpreparedSolver) {
    ISquareMatrix *matrix = new ArraySquareMatrix(TEST_SIZE);
    IVector *vector = new ArrayVector(TEST_SIZE);
    IVector *check = new ArrayVector(TEST_SIZE);
    IVector *original;

    MatrixUtils::fillRandomMatrix(matrix);
    MatrixUtils::fillRandomVector(vector);
    original = new ArrayVector(vector);

    unpreparedSolver->setMatrix(matrix);
    unpreparedSolver->prepare();
    unpreparedSolver->solve(vector);

    MatrixUtils::product(matrix, vector, check);

    return MatrixUtils::compare(check, original, 0.0000001);
}
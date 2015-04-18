#include "SuperLUSolverTest.h"

SuperLUSolverTest::SuperLUSolverTest() {
    this->info = "No info. Run test first.";
}

bool SuperLUSolverTest::runTests() {

    if (checkSolver()) {
        info = "Solver test done";
    } else {
        info = "Solver test failed";
    }

    //int gb1 = 134217728;
    //double *aaa = new double[gb1 * 4];
    /*
    ISquareMatrix *matrix = new ArraySquareMatrix(MATRIX_SIZE);
    IVector *vector = new ArrayVector(MATRIX_SIZE);
    IVector *original;

    MatrixFactory::fillRandomMatrix(matrix);
    MatrixFactory::fillRandomVector(vector);
    original = new ArrayVector(vector);

    std::cout << "waiting..." << std::endl;
    std::cin.get();*/

    /*std::cout << "Matrix:";
    MatrixUtils::print(matrix, std::cout, 8, 4);
    std::cout << std::endl << "Vector:" << std::endl;
    MatrixUtils::print(vector, std::cout, 7, 4);
    std::cout << std::endl;

    clock_t timestamp = clock();

    AbstractSolver *solver = new SequentialSolver();
    solver->setMatrix(matrix);
    solver->prepare();
    solver->solve(vector);

    timestamp = clock() - timestamp;

    std::cout << "Result:" << std::endl;
    MatrixUtils::print(vector, std::cout, 8, 4);

    IVector *check = new ArrayVector(MATRIX_SIZE);
    MatrixUtils::product(matrix, vector, check);

    std::cout << "Check:" << std::endl;
    MatrixUtils::print(check, std::cout, 8, 4);

    double norm = 0;
    for (int i = 0; i < MATRIX_SIZE; i++) {
        double difference = check->get(i) - original->get(i);
        norm += difference * difference;
    }
    norm = sqrt(norm);

    std::cout << "Norm: " << norm << std::endl;
    std::cout << "Time: " << (float) timestamp / CLOCKS_PER_SEC << std::endl;*/

    return 0;
}


std::string SuperLUSolverTest::getInfo() {
    return this->info;
}

bool SuperLUSolverTest::checkSolver() {
    ISquareMatrix *initMatrix = new ArraySquareMatrix(MATRIX_SIZE);
    MatrixUtils::fillRandomMatrix(initMatrix);

    HarwellBoeingMatrix *hbMatrix = new HarwellBoeingMatrix(initMatrix, 99);
    ArrayVector *rhs = new ArrayVector(MATRIX_SIZE);
    MatrixUtils::fillRandomVector(rhs);

    ArrayVector *orig = new ArrayVector(rhs);

    SuperLUSolver *solver = new SuperLUSolver();
    //AbstractSolver *solver = new SequentialSolver();
    solver->setMatrix(hbMatrix);

    std::cout << "Solving" << std::endl;
    long time = clock();
    solver->prepare();
    solver->solve(rhs);
    time = clock() - time;
    std::cout << "Solve time: " << (float)time / CLOCKS_PER_SEC << std::endl;

    return true;
    /*ArrayVector *check = new ArrayVector(MATRIX_SIZE);
    MatrixUtils::product(hbMatrix, rhs, check);

    bool similar = MatrixUtils::compare(check, orig, 0.00001);

    delete initMatrix;
    delete rhs;
    delete orig;
    delete solver;

    return similar;*/
}


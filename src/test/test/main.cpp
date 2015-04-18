#include <stdlib.h>
#include <iomanip>

#include <solver.h>
#include <matrix.h>

#include "TestRunner.h"
#include "ArraySquareMatrixTest.h"
#include "ArrayVectorTest.h"
#include "HarwellBoeingMatrixTest.h"
#include "SequentialSolverTest.h"

#define MATRIX_SIZE 2500
/**
* NEXT TO DO list
* 0. Check windows memory usage
* 1. std::fill to standard library
* 2. Common include file for libraries (?)
* 3. Exceptions
*/


bool checkSolver() {
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

void run() {

	//#pragma offload target(mic : 0)
	{

	#pragma omp parallel for
		for (int i = 0; i < MATRIX_SIZE; i++) {
			for (int j = 0; j < MATRIX_SIZE; j++) {
				for (int k = 0; k < MATRIX_SIZE; k++) {}
			}
		}

	}

	/*if (checkSolver()) {
		std::cout << "Solver test done" << std::endl;
	} else {
		std::cout << "Solver test failed" << std::endl;
	}*/

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
}

std::vector<TestCase*> getTests() {
	std::vector<TestCase*> tests;

	tests.push_back(new ArraySquareMatrixTest());
	tests.push_back(new ArrayVectorTest());
	tests.push_back(new MatrixTests());
	tests.push_back(new HarwellBoeingMatrixTest());
	tests.push_back(new SequentialSolverTest());

	return tests;
}

int main(int argc, const char* argv[]) {
	run();
	return 0;

	/*std::cout << "Running tests..." << std::endl << std::endl;

	TestRunner *runner = new TestRunner();
	std::vector<TestCase*> tests = getTests();

	bool result = runner->runTests(tests);

	if (result) {
		std::cout << std::endl << "--- All tests successfully done ---" << std::endl;
	} else {
		std::cout << std::endl << "*** Test failed ***" << std::endl;
	}

	return 0;*/
}

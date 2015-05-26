#include <stdlib.h>
#include <iomanip>

#pragma offload_attribute(push, target(mic))
#include <solver.h>
#include <matrix.h>

#pragma offload_attribute(pop)

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
void PCRTest();
void MKLTDTest();

bool checkSolver() {
	#pragma offload target(mic : 0)
	{
	ISquareMatrix *initMatrix = new ArraySquareMatrix(MATRIX_SIZE);
	MatrixUtils::fillRandomMatrix(initMatrix);

	HarwellBoeingMatrix *hbMatrix = new HarwellBoeingMatrix(initMatrix, 0);
	ArrayVector *rhs = new ArrayVector(MATRIX_SIZE);
	MatrixUtils::fillRandomVector(rhs);

	ArrayVector *orig = new ArrayVector(rhs);

	SuperLUSolver *solver = new SuperLUSolver();
	//AbstractSolver *solver = new SequentialSolver();
	solver->setMatrix(hbMatrix);
	
	//std::cout << "Solving" << std::endl;
	printf("Solving\n");
	long time = clock();
	solver->prepare();
	solver->solve(rhs);
	time = clock() - time;
	//std::cout << "Solve time: " << (float)time / CLOCKS_PER_SEC << std::endl;
	printf("Solve time: %f\n", (float)time / CLOCKS_PER_SEC);

	}

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
	
	/*int size = 134217728 * 3;
	double *a = (double*)malloc(size * sizeof(double));
	//in(a:length(size)) in(size)	
	double as;
	#pragma offload target(mic : 0) out(as) in(a)
	{
		//double *a = new double[size];
		//double *a = (double*)malloc(size * sizeof(double));
		for (int i = 0; i < size; i++) {
			a[i] = i + i;
		}

		as = a[10000];
	}

	int stop;
	std::cout << "DONE " << as << std::endl;
	std::cin >> stop;*/
	
	bool check;
	//#pragma offload target(mic : 0)
	{
		check = checkSolver();
	}

	if (check) {
		std::cout << "Solver test done" << std::endl;
	} else {
		std::cout << "Solver test failed" << std::endl;
	}

	int stop;
	std::cout << "DONE" << std::endl;
	std::cin >> stop;

	/*#pragma omp parallel for
		for (int i = 0; i < MATRIX_SIZE; i++) {
			for (int j = 0; j < MATRIX_SIZE; j++) {
				for (int k = 0; k < MATRIX_SIZE; k++) {}
			}
		}

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

/*std::vector<TestCase*> getTests() {
	std::vector<TestCase*> tests;

	tests.push_back(new ArraySquareMatrixTest());
	tests.push_back(new ArrayVectorTest());
	tests.push_back(new MatrixTests());
	tests.push_back(new HarwellBoeingMatrixTest());
	tests.push_back(new SequentialSolverTest());

	return tests;
}*/

int main(int argc, const char* argv[]) {
	//run();
	//PCRTest();
	MKLTDTest();
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

void MKLTDTest() {
	int size = 20;
	TridiagonalMatrix* matrix = new TridiagonalMatrix(size);
	IVector* rh = new ArrayVector(size);
	MatrixUtils::fillRandomMatrix(matrix);
	MatrixUtils::fillRandomVector(rh);

	IVector* check = new ArrayVector(rh);

	AbstractSolver* solver = new MKLTDSolver();
	solver->setMatrix(matrix);
	solver->prepare();
	solver->solve(rh);


	IVector* probe = new ArrayVector(size);
	MatrixUtils::product(matrix, rh, probe);

	MatrixUtils::print(check, std::cout);
	MatrixUtils::print(probe, std::cout);

	if (MatrixUtils::compare(probe, check, 0.0001)) {
		printf("Success\n");
	} else {
		printf("Something went wrong\n");
	}

	printf("Done");
	//int ccc;
	//std::cin >> ccc;
}

void PCRTest() {
	int size = 1024 * 1024 * 32;
	TridiagonalMatrix* matrix = new TridiagonalMatrix(size);
	IVector* rh = new ArrayVector(size);
	MatrixUtils::fillRandomMatrix(matrix);
	MatrixUtils::fillRandomVector(rh);

	IVector* check = new ArrayVector(rh);

	AbstractSolver* solver = new PCRSolver();
	solver->setMatrix(matrix);
	solver->prepare();
	solver->solve(rh);
	
	/*
	IVector* probe = new ArrayVector(size);
	MatrixUtils::product(matrix, rh, probe);

	MatrixUtils::print(check, std::cout);
	MatrixUtils::print(probe, std::cout);

	if (MatrixUtils::compare(probe, check, 0.0001)) {
		printf("Success\n");
	} else {
		printf("Something went wrong\n");
	}
	*/
	printf("Done");
	//int ccc;
	//std::cin >> ccc;

}



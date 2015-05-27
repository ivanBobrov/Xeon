#ifdef MKL

#include "MKLTDSolver.h"

MKLTDSolver::MKLTDSolver() {
	//Nothing to do
}

void MKLTDSolver::setMatrix(ISquareMatrix *matrix) {
	this->matrix = (TridiagonalMatrix*) matrix;
}

void MKLTDSolver::prepare() {

}

void MKLTDSolver::solve(IVector *b) {
	int size = matrix->size();
	int nrhs = 1;
	int info;

	double* lower = matrix->getLowerDiagonal();
	double* main = matrix->getMainDiagonal();
	double* upper = matrix->getUpperDiagonal();
	double* rh = new double[size];
	
	#pragma omp for
	for (int i = 0; i < size; i++) {
		rh[i] = b->get(i);
	}

	printf("solving\n");
	//mkl_mic_enable();
	dgtsv(&size, &nrhs, lower+1, main, upper, rh, &size, &info);
	printf("done\n");

	#pragma omp for
	for (int i = 0; i < size; i++) {
		b->set(i, rh[i]);
	}

	delete[] rh;
}

#endif //MKL

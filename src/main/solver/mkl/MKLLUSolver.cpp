#ifdef MKL

#include "MKLLUSolver.h"

MKLLUSolver::MKLLUSolver() {
	//Nothing to do
}

void MKLLUSolver::setMatrix(ISquareMatrix *matrix) {
	this->matrix = matrix;
}

void MKLLUSolver::prepare() {
	//Nothing to do
}

void MKLLUSolver::solve(IVector *b) {
	int size = matrix->size();
	int nrhs = 1;
	int lda = size; int ldb = size;
	int info;

	double* matr = new double[size*size];
	double* vect = new double[size];
	int* ipiv = new int[size];

	#pragma omp for
	for (int i = 0; i < size; i++) {
		//ipiv[i] = 0;
		vect[i] = b->get(i);
		for (int j = 0; j < size; j++) {
			matr[size*j + i] = matrix->get(i, j);
		}
	}

	printf("Start solving\n");
	dgesv(&size, &nrhs, matr, &lda, ipiv, vect, &ldb, &info);
	printf("done\n");

	#pragma omp for
	for (int i = 0; i < size; i++) {
		b->set(i, vect[i]);
	}

	delete[] matr;
	delete[] vect;
	delete[] ipiv;
}

#endif //MKL

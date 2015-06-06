#ifdef MKL

#include "MKLLUSolver.h"
#include <fstream>
#include <iostream>

MKLLUSolver::MKLLUSolver() {
	//Nothing to do
}

void MKLLUSolver::setMatrix(ISquareMatrix *matrix) {
	this->matrix = (HarwellBoeingMatrix*)matrix;
}

void MKLLUSolver::prepare() {
	
}

void MKLLUSolver::solve(IVector *b) {
	int size = matrix->size();
	
	int nnz = matrix->getNonZeroNumber();
	double* nzval = new double[nnz];

	#pragma omp parallel for
	for (int i = 0; i < nnz; i++) {
        nzval[i] = matrix->getNZVal(i);
    }

	int* rowind = new int[nnz];

	#pragma omp parallel for
	for (int i = 0; i < nnz; i++) {
        rowind[i] = matrix->getRowInd(i) + 1;
    }

	int *colptr = new int[size + 1];

	#pragma omp parallel for
	for (int i = 0; i < size + 1; i++) {
        colptr[i] = matrix->getColPtr(i) + 1;
    }

	double *rhs = new double[size];
	double *rhs2 = new double[size];
    #pragma omp parallel for
	for (int i = 0; i < size; i++) {
        rhs[i] = b->get(i);
		rhs2[i] = b->get(i);
    }

	//mkl_mic_enable();
	//mkl_set_num_threads(1);
	printf("Start solving\n");

	double start = omp_get_wtime();
	
	int* perm = new int[size];
	for (int i = 0; i < size; i++) {
		perm[i] = 0;
	}
	int* iparm = new int[64];
	for (int i = 0; i < 64; i++) {
		iparm[i] = 0;
	}
	

	int error = 0;
	int msglvl = 1;
	int nrhs = 1;
	int mode = 13;
	int mtype = 11;
	int mxfct = 1;
	int mnum = 1;
	
	int* pt = new int[64*8];
	for (int i = 0; i < 64*8; i++) {
		pt[i] = 0;
	}
	
	pardisoinit(pt,  &mtype, iparm);
	
	pardiso(pt, &mxfct, &mnum, &mtype, &mode, &size, nzval, colptr, rowind, perm, &nrhs, iparm, &msglvl, rhs, rhs2, &error);
	//dgesv(&size, &nrhs, matr, &lda, ipiv, vect, &ldb, &info);
	double stop = omp_get_wtime();
	printf("done time: %f\n", stop - start);

	std::ofstream file("out.txt", std::ios_base::app);
	file << stop - start << std::endl;
	file.close();

	/*#pragma omp for
	for (int i = 0; i < size; i++) {
		b->set(i, vect[i]);
	}

	delete[] matr;
	delete[] vect;
	delete[] ipiv;*/
}

#endif //MKL

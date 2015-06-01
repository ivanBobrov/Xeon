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
	mkl_set_num_threads(1);
	//mkl_mic_set_workdivision(MKL_TARGET_HOST, 0, 0.0);
	//mkl_mic_set_workdivision(MKL_TARGET_MIC, 0, 1.0);
	double start = omp_get_wtime();
	dgtsv(&size, &nrhs, lower+1, main, upper, rh, &size, &info);
	double stop =  omp_get_wtime();
	
	printf("done : %f\n", stop - start);

	#pragma omp for
	for (int i = 0; i < size; i++) {
		b->set(i, rh[i]);
	}

	delete[] rh;
}

#endif //MKL

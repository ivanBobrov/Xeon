#ifdef MIC_TARGET
	#pragma offload_attribute(push, target(mic))
#endif

#include "SuperLUSolver.h"
#include <fstream>
#include <iostream>

const double SuperLUSolver::EPSILON = 0.00000001;

SuperLUSolver::SuperLUSolver() {
    //Nothing to do
}

SuperLUSolver::~SuperLUSolver() {
    delete matrix;
}

void SuperLUSolver::setMatrix(ISquareMatrix *matrix) {
	this->matrix = (HarwellBoeingMatrix*) matrix;
	//this->matrix = new HarwellBoeingMatrix(matrix, EPSILON);
}

void SuperLUSolver::setMatrix(HarwellBoeingMatrix *matrix) {
    this->matrix = matrix;
}

void SuperLUSolver::prepare() {
	int a = 2;
	#pragma offload target(mic : 0) inout(a)
	{
		for (int i = 0; i < 10; i++) {
			a*=2;
		}
	}
}


void SuperLUSolver::solve(IVector *b) {	
	printf("Solve procedure started\n");
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
        rowind[i] = matrix->getRowInd(i);
    }

	int *colptr = new int[size + 1];

	#pragma omp parallel for
	for (int i = 0; i < size + 1; i++) {
        colptr[i] = matrix->getColPtr(i);
    }

	double *rhs = new double[size];
    #pragma omp parallel for
	for (int i = 0; i < size; i++) {
        rhs[i] = b->get(i);
    }

	printf("Pdgssv call\n");
	double start, stop;
	double timeOffload;
	start = omp_get_wtime();
	//#pragma offload target(mic : 0) in(size, nnz) in(nzval, rowind : length(nnz)) in(colptr : length(size+1)) in(rhs : length(size)) out(timeOffload)
	{
		double offloadStart, offloadStop;
		int info;
		int processesNumber = 32;
		
		offloadStart = omp_get_wtime();
		
		SuperMatrix *input = new SuperMatrix();
		dCreate_CompCol_Matrix(input, size, size, nnz, nzval, rowind, colptr, SLU_NC, SLU_D, SLU_GE);
		
		SuperMatrix *rightHand  = new SuperMatrix();
		dCreate_Dense_Matrix(rightHand, size, 1, rhs, size, SLU_DN, SLU_D, SLU_GE);
		
		int *perm_c = new int[size];
		int *perm_r = new int[size];
		get_perm_c(0, input, perm_c);
		
		SuperMatrix *L = new SuperMatrix;
		SuperMatrix *U = new SuperMatrix;
		
		pdgssv(processesNumber, input, perm_c, perm_r, L, U, rightHand, &info);
		
		offloadStop = omp_get_wtime();

		timeOffload = offloadStop - offloadStart;
	}
	
	stop = omp_get_wtime();
	printf("time superLU: %f | clean: %f\n", (stop - start), timeOffload);
	std::ofstream file("out.txt", std::ios_base::app);
	file << stop - start << "\t" << timeOffload << std::endl;
	file.close();
}

#ifdef MIC_TARGET
	#pragma offload_attribute(pop)
#endif

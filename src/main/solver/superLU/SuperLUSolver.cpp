#ifdef MIC_TARGET
	#pragma offload_attribute(push, target(mic))
#endif

#include "SuperLUSolver.h"

const double SuperLUSolver::EPSILON = 0.00000001;

SuperLUSolver::SuperLUSolver() {
    //Nothing to do
}

SuperLUSolver::~SuperLUSolver() {
    delete matrix;
}

void SuperLUSolver::setMatrix(ISquareMatrix *matrix) {
    this->matrix = new HarwellBoeingMatrix(matrix, EPSILON);
    delete matrix;
}

void SuperLUSolver::setMatrix(HarwellBoeingMatrix *matrix) {
    this->matrix = matrix;
}

void SuperLUSolver::prepare() {
	//Nothing to do
}


void SuperLUSolver::solve(IVector *b) {	
	int size = matrix->size();
    int processesNumber = 240;//228;
    double start, stop;
	int info;
	
    SuperMatrix *input      = new SuperMatrix();
    SuperMatrix *L          = new SuperMatrix();
    SuperMatrix *U          = new SuperMatrix();
    SuperMatrix *rightHand  = new SuperMatrix();
	int *perm_c = new int[size];
    int *perm_r = new int[size];

    convertToSuperMatrix(input, matrix);
    convertVectorToSM(rightHand, b);
    get_perm_c(0, input, perm_c);


    start = omp_get_wtime();
    printf("Pdgssv call\n");
    pdgssv(processesNumber, input, perm_c, perm_r, L, U, rightHand, &info);
	stop = omp_get_wtime();

	printf("time superLU: %f\n", (stop - start));

    convertSMToVector(b, rightHand);
}

void SuperLUSolver::convertToSuperMatrix(SuperMatrix *superMatrix, HarwellBoeingMatrix *ncMatrix) {
    int size = ncMatrix->size();
    int nnz = matrix->getNonZeroNumber();
    
    double *nzval = new double[nnz];
    int *rowind = new int[nnz];
    int *colptr = new int[size + 1];

    for (int i = 0; i < nnz; i++) {
        nzval[i] = matrix->getNZVal(i);
    }

    for (int i = 0; i < nnz; i++) {
        rowind[i] = matrix->getRowInd(i);
    }

    for (int i = 0; i < size + 1; i++) {
        colptr[i] = matrix->getColPtr(i);
    }

    dCreate_CompCol_Matrix(superMatrix, size, size, nnz, nzval, rowind, colptr, SLU_NC, SLU_D, SLU_GE);
}

void SuperLUSolver::convertVectorToSM(SuperMatrix *superMatrix, IVector *b) {
    int size = b->size();

    double *rhs = new double[size];
    for (int i = 0; i < size; i++) {
        rhs[i] = b->get(i);
    }

    dCreate_Dense_Matrix(superMatrix, size, 1, rhs, size, SLU_DN, SLU_D, SLU_GE);
}


void SuperLUSolver::convertSMToVector(IVector *out, SuperMatrix *matrix) {
    int size = matrix->nrow;
    DNformat *dnformat = (DNformat*)matrix->Store;
    double *nzval = (double*)dnformat->nzval;
    for (int i = 0; i < size; i++) {
        out->set(i, nzval[i]);
    }
}

#ifdef MIC_TARGET
	#pragma offload_attribute(pop)
#endif

#ifdef MIC_TARGET
    #pragma offload_attribute(push, target(mic))
#endif

#include "PCRSolver.h"
#include <stdio.h> //TOOD: remove it now

PCRSolver::PCRSolver() {
    //Nothing to do
}

void PCRSolver::setMatrix(ISquareMatrix *matrix) {
    this->matrix = (TridiagonalMatrix*) matrix; //TODO: dynamic cast
}

void PCRSolver::prepare() {
    //send arrays to Xeon
    matrix->allocateOnXeonPhi();
}

void PCRSolver::solve(IVector *b) {
    PCRKernel(matrix, b, b, b->size(), 10);
}

void PCRSolver::PCRKernel(TridiagonalMatrix *triDiagMatrix, IVector *bv, IVector *xi, int size, int numThreads) {
    int actSize = 1;
    while (actSize < size) {
        actSize *= 2;
    }

    double* a = new double[actSize];
    double* b = new double[actSize];
    double* c = new double[actSize];
    double* d = new double[actSize];
    double* x = new double[actSize];

    #pragma omp parallel num_threads(numThreads)
    {
        int delta = 1;
        const unsigned int systemSize = (unsigned int) actSize;
        int iteration = (int) log2(systemSize/2);

        #pragma omp for
        for (int i = 0; i < size; i++) {
            a[i] = triDiagMatrix->getLowerDiagonal(i);
            b[i] = triDiagMatrix->getMainDiagonal(i);
            c[i] = triDiagMatrix->getUpperDiagonal(i);
            d[i] = bv->get(i);
        }

        for (int i = size; i < systemSize; i++) {
            a[i] = 0;
            b[i] = 1;
            c[i] = 0;
            d[i] = 1;
        }

        double* aNew = new double[systemSize];
        double* bNew = new double[systemSize];
        double*	cNew = new double[systemSize];
        double* dNew = new double[systemSize];

        for (int j = 0; j < iteration; j++) {
            #pragma omp for
            for (int i = 0; i < systemSize; i++) {
                if (i < delta) {
                    double tmp2 = c[i] / b[i + delta];
                    bNew[i] = b[i] - a[i + delta] * tmp2;
                    dNew[i] = d[i] - d[i + delta] * tmp2;
                    aNew[i] = 0;
                    cNew[i] = -c[i + delta] * tmp2;
                } else {
                    if ((systemSize - i - 1) < delta) {
                        double tmp = a[i] / b[i - delta];
                        bNew[i] = b[i] - c[i - delta] * tmp;
                        dNew[i] = d[i] - d[i - delta] * tmp;
                        aNew[i] = -a[i - delta] * tmp;
                        cNew[i] = 0;
                    } else {
                        double tmp1 = a[i] / b[i - delta];
                        double tmp2 = c[i] / b[i + delta];
                        bNew[i] = b[i] - c[i - delta] * tmp1 - a[i + delta] * tmp2;
                        dNew[i] = d[i] - d[i - delta] * tmp1 - d[i + delta] * tmp2;
                        aNew[i] = -a[i - delta] * tmp1;
                        cNew[i] = -c[i + delta] * tmp2;
                    }
                }
            }

            #pragma omp for
            for (int i = 0; i < systemSize; i++) {
                b[i] = bNew[i];
                d[i] = dNew[i];
                a[i] = aNew[i];
                c[i] = cNew[i];
            }

            delta *= 2;
        }

        #pragma omp for
        for (int i = 0; i < systemSize; i++) {
            if (i < delta) {
                int addr1 = i;
                int addr2 = i + delta;
                double tmp3 = b[addr2] * b[addr1] - c[addr1] * a[addr2];
                x[addr1] 	= (b[addr2] * d[addr1] - c[addr1] * d[addr2]) / tmp3;
                x[addr2] 	= (d[addr2] * b[addr1] - d[addr1] * a[addr2]) / tmp3;
            }
        }

        #pragma omp for
        for (int i = 0; i < size; i++) {
            xi->set(i, x[i]);
        }
    }
}

#ifdef MIC_TARGET
    #pragma offload_attribute(pop)
#endif



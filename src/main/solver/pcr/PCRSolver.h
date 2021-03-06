#ifndef PCRSOLVER_H
#define PCRSOLVER_H

#include <math.h>
#include <omp.h>
#include <AbstractSolver.h>
#include <TridiagonalMatrix.h>
#include <matrix.h>
#include "stdio.h"

#define M_LOG2 0.69314718055994530943

class PCRSolver : public AbstractSolver {
private:
    TridiagonalMatrix* matrix;

    void PCRKernel(double* oa, double* ob, double* oc, double *bv, double *xi, int size, int numThreads);

public:
    PCRSolver();

    virtual void setMatrix(ISquareMatrix *matrix);
    virtual void prepare();
    virtual void solve(IVector *b);
};

#endif //PCRSOLVER_H

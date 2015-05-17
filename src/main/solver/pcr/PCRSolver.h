#ifndef PCRSOLVER_H
#define PCRSOLVER_H

#include <math.h>
#include <omp.h>
#include <AbstractSolver.h>
#include <TridiagonalMatrix.h>

class PCRSolver : public AbstractSolver {
private:
    TridiagonalMatrix* matrix;

    void PCRKernel(TridiagonalMatrix *triDiagMatrix, IVector *bv, IVector *xi, int size, int numThreads);

public:
    PCRSolver();

    virtual void setMatrix(ISquareMatrix *matrix);
    virtual void prepare();
    virtual void solve(IVector *b);
};

#endif //PCRSOLVER_H

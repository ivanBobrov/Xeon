#ifndef MKLLUSOLVER_H
#define MKLLUSOLVER_H

#ifdef MKL

#include "AbstractSolver.h"
#include <mkl.h>
#include <stdio.h>

class MKLLUSolver : public AbstractSolver {
private:
	ISquareMatrix* matrix;
public:
	MKLLUSolver();

	virtual void setMatrix(ISquareMatrix *matrix);
	virtual void prepare();
	virtual void solve(IVector *b);
};

#else //MKL
//stub

class MKLLUSolver : public AbstractSolver {
public:
    virtual void setMatrix(ISquareMatrix *matrix) {};
    virtual void prepare() {};
    virtual void solve(IVector *b) {};
};

#endif //MKL

#endif //MKLLUSOLVER_H

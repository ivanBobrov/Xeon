#include "AbstractSolver.h"

#ifndef MKLTDSOLVER_H
#define MKLTDSOLVER_H

#ifdef MKL

#include "AbstractSolver.h"

class MKLTDSolver : public AbstractSolver {
private:

public:
    MKLTDSolver();

    virtual void setMatrix(ISquareMatrix *matrix);
    virtual void prepare();
    virtual void solve(IVector *b);
};

#else //MKL

//Stub
class MKLTDSolver : public AbstractSolver {
public:
    virtual void setMatrix(ISquareMatrix *matrix) {};
    virtual void prepare() {};
    virtual void solve(IVector *b) {};
};

#endif //MKL

#endif //MKLTDSOLVER_H
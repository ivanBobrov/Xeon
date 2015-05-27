#ifndef MKLLUSOLVER_H
#define MKLLUSOLVER_H

#include "AbstractSolver.h"

#ifdef MKL

class MKLLUSolver : public AbstractSolver {
private:

public:

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

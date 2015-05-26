#ifndef SUPER_LU_SOLVER_H
#define SUPER_LU_SOLVER_H

#include "ISquareMatrix.h"
#include "IVector.h"
#include "HarwellBoeingMatrix.h"
#include "AbstractSolver.h"

#define EXIT return
#include "time.h"
#include <stdio.h>

#ifdef MKL
    #include "mkl.h"
#endif

class SuperLUSolver : public AbstractSolver {
private:
    static const double EPSILON;
    HarwellBoeingMatrix *matrix;

    //void convertToSuperMatrix(SuperMatrix *superMatrix, HarwellBoeingMatrix *ncMatrix);
    //void convertVectorToSM(SuperMatrix *superMatrix, IVector *b);
    //void convertSMToVector(IVector *out, SuperMatrix *matrix);

public:
    SuperLUSolver();

    void setMatrix(HarwellBoeingMatrix *matrix);
    virtual void setMatrix(ISquareMatrix *matrix);
    virtual void prepare();
    virtual void solve(IVector *b);

    ~SuperLUSolver();
};

#endif
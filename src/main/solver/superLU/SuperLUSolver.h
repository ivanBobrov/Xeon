#ifndef SUPER_LU_SOLVER_H
#define SUPER_LU_SOLVER_H

#include "ISquareMatrix.h"
#include "IVector.h"
#include "HarwellBoeingMatrix.h"
#include "AbstractSolver.h"

#define EXIT return
#include "time.h"
#include "omp.h"
#include <stdio.h>
#include "pdsp_defs.h"

class SuperLUSolver : public AbstractSolver {
private:
    static const double EPSILON;
    HarwellBoeingMatrix *matrix;

public:
    SuperLUSolver();

    void setMatrix(HarwellBoeingMatrix *matrix);
    virtual void setMatrix(ISquareMatrix *matrix);
    virtual void prepare();
    virtual void solve(IVector *b);

    ~SuperLUSolver();
};

#endif
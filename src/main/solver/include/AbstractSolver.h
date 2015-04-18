#ifndef ABSTRACT_SOLVER_H
#define ABSTRACT_SOLVER_H

#include "ISquareMatrix.h"
#include "IVector.h"

class AbstractSolver {
public:
	virtual void setMatrix(ISquareMatrix *matrix) = 0;
	virtual void prepare() = 0;
	virtual void solve(IVector * b) = 0;
};

#endif
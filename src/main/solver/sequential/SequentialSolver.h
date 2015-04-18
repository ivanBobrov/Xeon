#ifndef SEQUENTIAL_SOLVER_H
#define SEQUENTIAL_SOLVER_H

#include "AbstractSolver.h"
#include <ISquareMatrix.h>
#include <IVector.h>
#include "MatrixUtils.h"
#include <ArraySquareMatrix.h>

class SequentialSolver : public AbstractSolver {
private:
	ISquareMatrix * matrix;
	ISquareMatrix * lowerTriangular;
	ISquareMatrix * upperTriangular;

	void decompose();
	void lowerSolve(ISquareMatrix *matrix, IVector *right);
	void upperSolve(ISquareMatrix *matrix, IVector *right);

public:
	SequentialSolver();

	virtual void setMatrix(ISquareMatrix *matrix);
	virtual void prepare();
	virtual void solve(IVector * b);
};

#endif
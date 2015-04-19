#ifdef MIC_TARGET
	#pragma offload_attribute(push, target(mic))
#endif

#include "SequentialSolver.h"


//TODO: should not be there
#include <stdio.h>

SequentialSolver::SequentialSolver() {
    lowerTriangular = NULL;
    upperTriangular = NULL;
}

void SequentialSolver::setMatrix(ISquareMatrix *matrix) {
    this->matrix = matrix;
}

void SequentialSolver::prepare() {
    decompose();
}

void SequentialSolver::solve(IVector *b) {
    lowerSolve(lowerTriangular, b);
    upperSolve(upperTriangular, b);
}

void SequentialSolver::decompose() {
    //TODO: error handling
    int size = matrix->size();
    if (lowerTriangular != NULL || upperTriangular != NULL) {
        //TODO: report error
        printf("ERROR");
        return;
    }

    lowerTriangular = new ArraySquareMatrix(size);
    upperTriangular = new ArraySquareMatrix(size);

    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            double upperSum = 0;
            for (int k = 0; k <= i-1; k++) {
                upperSum += upperTriangular->get(k, j) * lowerTriangular->get(i, k);
            }

            double upperValue = matrix->get(i, j) - upperSum;
            upperTriangular->set(i, j, upperValue);

            double lowerSum = 0;
            for (int k = 0; k <= i-1; k++) {
                lowerSum += upperTriangular->get(k, i) * lowerTriangular->get(j, k);
            }

            double lowerValue = (matrix->get(j,i) - lowerSum) / upperTriangular->get(i, i);
            lowerTriangular->set(j, i, lowerValue);
        }
    }
}

void SequentialSolver::lowerSolve(ISquareMatrix *matrix, IVector *right) {
    if (matrix->size() != right->size()) {
        //TODO: throw an exception
        printf("Error in lowerSolve");
    }

    int size = matrix->size();
    for (int i = 0; i < size; i++) {
        double value = right->get(i);
        double sum = 0;
        for (int j = 0; j < i; j++) {
            sum += matrix->get(i, j) * right->get(j);
        }

        right->set(i, (value - sum) / matrix->get(i, i));
    }
}

void SequentialSolver::upperSolve(ISquareMatrix *matrix, IVector *right) {
    if (matrix->size() != right->size()) {
        //TODO: throw an exception
        printf("Error in lowerSolve");
    }

    int size = matrix->size();
    for (int i = size-1; i >= 0; i--) {
        double value = right->get(i);
        double sum = 0;
        for (int j = size-1; j > i; j--) {
            sum += matrix->get(i, j) * right->get(j);
        }

        right->set(i, (value - sum) / matrix->get(i, i));
    }
}

#ifdef MIC_TARGET
	#pragma offload_attribute(pop)
#endif

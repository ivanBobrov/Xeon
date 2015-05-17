#ifndef TRIDIAGONALMATRIX_H
#define TRIDIAGONALMATRIX_H

#include <ISquareMatrix.h>
#include "XeonAllocatable.h"
#include <algorithm>

class TridiagonalMatrix : public ISquareMatrix, public XeonAllocatable {
private:
    double* lowerDiagonal;
    double* mainDiagonal;
    double* upperDiagonal;

    int mSize;

public:
    TridiagonalMatrix(int size);
    ~TridiagonalMatrix();

    virtual int size() const;
    virtual void set(const int i, const int j, const double value);
    virtual double get(const int i, const int j) const;

    virtual void allocateOnXeonPhi();
    virtual void freeOnXeonPhi();

    double getLowerDiagonal(const int i) const;
    double getMainDiagonal(const int i) const;
    double getUpperDiagonal(const int i) const;
};

#endif //TRIDIAGONALMATRIX_H

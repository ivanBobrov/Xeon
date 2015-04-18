#ifndef ARRAY_SQUARE_MATRIX_H
#define ARRAY_SQUARE_MATRIX_H

#include "ISquareMatrix.h"
#include <algorithm>

class ArraySquareMatrix : public ISquareMatrix {
private:
    int mSize;
    double *data;

public:
    ArraySquareMatrix(int size);
    ~ArraySquareMatrix();

    virtual void set(const int i, const int j, const double value);
    virtual double get(const int i, const int j) const ;
    virtual int size() const;
};

#endif

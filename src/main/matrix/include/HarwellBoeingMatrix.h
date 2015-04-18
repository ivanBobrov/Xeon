#ifndef HARWELL_BOEING_MATRIX_H
#define HARWELL_BOEING_MATRIX_H

#include <algorithm>
#include <math.h>
#include <vector>
#include "ISquareMatrix.h"

class HarwellBoeingMatrix : public ISquareMatrix {
private:
    static const double ZERO_VALUE;
    int mSize;
    double *values;
    int *rowIndex;
    int *colBeginsIndex;

public:
    HarwellBoeingMatrix(int size);
    HarwellBoeingMatrix(ISquareMatrix *squareMatrix, double epsilon); //TODO: implement

    double getNZVal(int index) const;
    int getNonZeroNumber() const;
    int getRowInd(int index) const;
    int getColPtr(int index) const;
    bool isElementZero(const int i, const int j) const;
    virtual void set(int const i, int const j, double const value);
    virtual double get(int const i, int const j) const;
    virtual int size() const;

    ~HarwellBoeingMatrix();
};

#endif
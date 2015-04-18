#ifndef ARRAY_VECTOR_H
#define ARRAY_VECTOR_H

#include "IVector.h"
#include <algorithm>

class ArrayVector : public IVector {
private:
    int mSize;
    double *data;

public:
    ArrayVector(int size);
    ArrayVector(IVector *vector);
    ~ArrayVector();

    virtual double get(const int i) const;
    virtual void set(const int i, const double value);
    virtual int size() const;
};

#endif
#ifndef I_SQUARE_MATRIX_H
#define I_SQUARE_MATRIX_H

#include "IMatrix.h"

class ISquareMatrix : public IMatrix {
public:
    virtual int columnCount() const {return size();};
    virtual int rowCount() const {return size();};
    virtual int size() const = 0;
};

#endif

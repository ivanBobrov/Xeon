#ifndef I_MATRIX_H
#define I_MATRIX_H

class IMatrix {
public:
    virtual void set(const int i, const int j, const double value) = 0;
    virtual double get(const int i, const int j) const = 0;
    virtual int columnCount() const = 0;
    virtual int rowCount() const = 0;
};

#endif
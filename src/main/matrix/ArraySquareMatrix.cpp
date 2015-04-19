#ifdef MIC_TARGET
	#pragma offload_attribute(push, target(mic))
#endif

#include "ArraySquareMatrix.h"

ArraySquareMatrix::ArraySquareMatrix(int size) {
    this->mSize = size;
    this->data = new double[size * size];
    std::fill(this->data, this->data + size * size, 0);
}

ArraySquareMatrix::~ArraySquareMatrix() {
    delete(this->data);
}

void ArraySquareMatrix::set(const int i, const int j, const double value) {
    this->data[i + this->mSize * j] = value;
}

double ArraySquareMatrix::get(const int i, const int j) const {
    return this->data[i + this->mSize * j];
}

int ArraySquareMatrix::size() const {
    return this->mSize;
}

#ifdef MIC_TARGET
	#pragma offload_attribute(pop)
#endif

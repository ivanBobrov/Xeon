#ifdef MIC_TARGET
	#pragma offload_attribute(push, target(mic))
#endif

#include "ArrayVector.h"

ArrayVector::ArrayVector(int size) {
    this->mSize = size;
    this->data = new double[size];
    std::fill(this->data, this->data + size, 0);
}


ArrayVector::ArrayVector(IVector *vector) {
    this->mSize = vector->size();
    this->data = new double[mSize];

    for (int i = 0; i < mSize; i++) {
        data[i] = vector->get(i);
    }
}

ArrayVector::~ArrayVector() {
    delete(this->data);
}

double ArrayVector::get(const int i) const {
    return this->data[i];
}

void ArrayVector::set(const int i, const double value) {
    this->data[i] = value;
}

int ArrayVector::size() const {
    return this->mSize;
}

#ifdef MIC_TARGET
	#pragma offload_attribute(pop)
#endif

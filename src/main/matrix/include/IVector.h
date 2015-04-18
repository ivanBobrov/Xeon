#ifndef VECTOR_H
#define VECTOR_H

class IVector {
public:
	virtual double get(const int i) const = 0;
	virtual void set(const int i, const double value) = 0;
	virtual int size() const = 0;
};

#endif
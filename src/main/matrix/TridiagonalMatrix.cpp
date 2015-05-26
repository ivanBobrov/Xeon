#ifdef MIC_TARGET
    #pragma offload_attribute(push, target(mic))
#endif

#include "TridiagonalMatrix.h"

TridiagonalMatrix::TridiagonalMatrix(int size) {
    this->mSize = size;

    this->lowerDiagonal = new double[size];
    this->mainDiagonal = new double[size];
    this->upperDiagonal = new double[size];

    std::fill(this->lowerDiagonal, this->lowerDiagonal + size, 0);
    std::fill(this->mainDiagonal, this->mainDiagonal + size, 0);
    std::fill(this->upperDiagonal, this->upperDiagonal + size, 0);
}

TridiagonalMatrix::TridiagonalMatrix() {
	//Empty private constructor for filling in Xeon
}

TridiagonalMatrix::~TridiagonalMatrix() {
    delete[] this->lowerDiagonal;
    delete[] this->mainDiagonal;
    delete[] this->upperDiagonal;
}

void TridiagonalMatrix::set(const int i, const int j, const double value) {
    if (abs(i - j) > 1 || i >= this->mSize || j >= this->mSize || i < 0 || j < 0 ) {
        //TODO: throw exception
        return;
    }

    if (i == j) {
        this->mainDiagonal[i] = value;
    }

    if (i > j) {
        this->lowerDiagonal[i] = value;
    }

    if (i < j) {
        this->upperDiagonal[i] = value;
    }
}

double TridiagonalMatrix::get(const int i, const int j) const {
    if (abs(i - j) > 1 || i >= this->mSize || j >= this->mSize || i < 0 || j < 0 ) {
        return 0;
    }

    if (i == j) {
        return this->mainDiagonal[i];
    }

    if (i > j) {
        return this->lowerDiagonal[i];
    }

    if (i < j) {
        return this->upperDiagonal[i];
    }

    return 0;
}

int TridiagonalMatrix::size() const {
    return this->mSize;
}


double* TridiagonalMatrix::getLowerDiagonal() const {
	return this->lowerDiagonal;

}

double* TridiagonalMatrix::getMainDiagonal() const {
	return this->mainDiagonal;
}

double* TridiagonalMatrix::getUpperDiagonal() const {
	return this->upperDiagonal;
}


void TridiagonalMatrix::allocateOnXeonPhi(TridiagonalMatrix* matrix) {
	/*TridiagonalMatrix *xeonCopy = this;
	int xeonMSize = this->mSize;
	double* xeonLower = this->lowerDiagonal;
	double* xeonMain = this->mainDiagonal;
	double* xeonUpper = this->upperDiagonal;

	#pragma offload target(mic : 0) in(xeonMSize) in(xeonLower, xeonMain, xeonUpper : length(xeonMSize) ALLOC) nocopy(xeonCopy : ALLOC)
	{
		xeonCopy = new TridiagonalMatrix();
		xeonCopy->mSize = xeonMSize;
		xeonCopy->lowerDiagonal = xeonLower;
		xeonCopy->mainDiagonal = xeonMain;
		xeonCopy->upperDiagonal = xeonUpper;
	}

	#pragma offload target(mic : 0) nocopy(xeonCopy : REUSE)
	{
		int size = xeonCopy->size();
	}*/
	
	#pragma offload target(mic : 0) nocopy(matrix)
	{
		matrix = new TridiagonalMatrix(100);
	}
}

void TridiagonalMatrix::freeOnXeonPhi() {
    //#pragma offload_transfer target(mic : 0)
}

#ifdef MIC_TARGET
    #pragma offload_attribute(pop)
#endif


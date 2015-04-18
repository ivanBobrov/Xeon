#include "HarwellBoeingMatrix.h"

const double HarwellBoeingMatrix::ZERO_VALUE = 0.0;

HarwellBoeingMatrix::HarwellBoeingMatrix(int size) {
    this->mSize = size;
    this->values = new double[0];
    this->rowIndex = new int[0];
    this->colBeginsIndex = new int[mSize + 1];
    std::fill(colBeginsIndex, colBeginsIndex + mSize + 1, 0);
}

HarwellBoeingMatrix::HarwellBoeingMatrix(ISquareMatrix *squareMatrix, double epsilon) {
    this->mSize = squareMatrix->size();
    std::vector<double> *vValues = new std::vector<double>();
    std::vector<int> *vRowIndex = new std::vector<int>();
    std::vector<int> *vColBegins = new std::vector<int>();

    int nonZeros = 0;
    for (int j = 0; j < mSize; j++) {
        vColBegins->push_back(nonZeros);
        for (int i = 0; i < mSize; i++) {
            double value = squareMatrix->get(i, j);
            if (fabs(value) > epsilon ) {
                nonZeros++;
                vValues->push_back(value);
                vRowIndex->push_back(i);
            }
        }
    }
    vColBegins->push_back(nonZeros);

    this->values = new double[vValues->size()];
    this->rowIndex = new int[vRowIndex->size()];
    this->colBeginsIndex = new int[vColBegins->size()];
    std::copy(vValues->data(), vValues->data() + vValues->size(), this->values);
    std::copy(vRowIndex->data(), vRowIndex->data() + vRowIndex->size(), this->rowIndex);
    std::copy(vColBegins->data(), vColBegins->data() + vColBegins->size(), this->colBeginsIndex);

    delete vValues;
    delete vRowIndex;
    delete vColBegins;
}

HarwellBoeingMatrix::~HarwellBoeingMatrix() {
    delete[] values;
    delete[] rowIndex;
    delete[] colBeginsIndex;
}

double HarwellBoeingMatrix::get(int const i, int const j) const {
    /*if (i > mSize || j > mSize) {
        TODO: throw exception
    }*/

    int nonZerosInColumn = this->colBeginsIndex[j+1] - this->colBeginsIndex[j];
    if (nonZerosInColumn == 0) {
        return ZERO_VALUE;
    }

    for (int row = colBeginsIndex[j]; row < colBeginsIndex[j+1]; row++) {
        if (this->rowIndex[row] == i) {
            return this->values[row];
        }
    }

    return ZERO_VALUE;
}


void HarwellBoeingMatrix::set(int const i, int const j, double const value) {
    if (isElementZero(i, j)) {
        int idxToPaste = colBeginsIndex[j];
        for (idxToPaste; idxToPaste < colBeginsIndex[j+1]; idxToPaste++) {
            if (rowIndex[idxToPaste] > j) {
                break;
            }
        }

        for (int col = j+1; col < mSize + 1; col++) {
            this->colBeginsIndex[col]++;
        }

        int nonZeros = colBeginsIndex[mSize];
        int *newRowIndex = new int[nonZeros];
        double *newValues = new double[nonZeros];

        std::copy(rowIndex, rowIndex + idxToPaste, newRowIndex);
        std::copy(rowIndex + idxToPaste, rowIndex + nonZeros - 1, newRowIndex + idxToPaste + 1);
        std::copy(values, values + idxToPaste, newValues);
        std::copy(values + idxToPaste, values + nonZeros - 1, newValues + idxToPaste + 1);

        newRowIndex[idxToPaste] = i;
        newValues[idxToPaste] = value;

        delete[] rowIndex;
        delete[] values;
        this->rowIndex = newRowIndex;
        this->values = newValues;
    } else {
        int nonZerosInColumn = this->colBeginsIndex[j+1] - this->colBeginsIndex[j];
        if (nonZerosInColumn == 0) {
            //TODO: throw exception. Implementation error.
        }

        for (int row = colBeginsIndex[j]; row < colBeginsIndex[j+1]; row++) {
            if (this->rowIndex[row] == i) {
                this->values[row] = value;
            }
        }
    }
}

double HarwellBoeingMatrix::getNZVal(int index) const {
    if (index >= getNonZeroNumber()) {
        //TODO: throw exception
        return -1;
    }

    return this->values[index];
}


int HarwellBoeingMatrix::getRowInd(int index) const {
    if (index >= getNonZeroNumber()) {
        //TODO: throw exception
        return -1;
    }

    return this->rowIndex[index];
}


int HarwellBoeingMatrix::getColPtr(int index) const {
    if (index > mSize) {
        //TODO: throw exception
        return -1;
    }
    return this->colBeginsIndex[index];
}


bool HarwellBoeingMatrix::isElementZero(const int i, const int j) const {
    int nonZerosInColumn = this->colBeginsIndex[j+1] - this->colBeginsIndex[j];
    if (nonZerosInColumn == 0) {
        return true;
    }

    for (int row = colBeginsIndex[j]; row < colBeginsIndex[j+1]; row++) {
        if (this->rowIndex[row] == i) {
            return false;
        }
    }

    return true;
}

int HarwellBoeingMatrix::getNonZeroNumber() const {
    return this->colBeginsIndex[mSize];
}

int HarwellBoeingMatrix::size() const {
    return this->mSize;
}

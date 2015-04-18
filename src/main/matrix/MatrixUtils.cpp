#include "MatrixUtils.h"

void MatrixUtils::product(IMatrix const *A, IMatrix const *B, IMatrix *result) {
    if ((A->columnCount() != B->rowCount()) ||
            A->rowCount() != result->rowCount() ||
            B->columnCount() != result->columnCount()) {

        //TODO: throw exception
        result = NULL;
        return;
    }

    for (int i = 0; i < A->rowCount(); i++) {
        for (int j = 0; j < B->columnCount(); j++) {
            double element = 0.0;
            for (int k = 0; k < A->columnCount(); k++) {
                element += A->get(i, k) * B->get(k, j);
            }

            result->set(i, j, element);
        }
    }
}


void MatrixUtils::product(IMatrix const *A, IVector const *v, IVector *result) {
    if (A->columnCount() != v->size() ||
            v->size() != result->size()) {

        //TODO: throw exception
        result = NULL;
        return;
    }

    for (int i = 0; i < A->rowCount(); i++) {
        double value = 0;
        for (int j = 0; j < A->columnCount(); j++) {
            value += A->get(i, j) * v->get(j);
        }

        result->set(i, value);
    }
}

bool MatrixUtils::compare(IMatrix const *A, IMatrix const *B, const double epsilon) {
    if (A->columnCount() != B->columnCount() || A->rowCount() != B->rowCount()) {
        return false;
    }

    int rows = A->rowCount();
    int cols = A->columnCount();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (A->get(i, j) - B->get(i, j) > epsilon) {
                return false;
            }
        }
    }

    return true;
}


bool MatrixUtils::compare(IVector const *A, IVector const *B, const double epsilon) {
    if (A->size() != B->size()) {
        return false;
    }

    int size = A->size();

    for (int i = 0; i < size; i++) {
        if (A->get(i) - B->get(i) > epsilon) {
            return false;
        }
    }

    return true;
}

void MatrixUtils::print(IMatrix const *matrix, std::ostream &out, int symbols, int precision) {
    int rows = matrix->rowCount();
    int cols = matrix->columnCount();

    out << std::setprecision(precision);
    for(int i = 0; i < rows; i++) {
        out << std::endl;
        for (int j = 0; j < cols; j++) {
            out << std::setw(symbols) << matrix->get(i, j);
        }
    }
    out << std::endl;
}

void MatrixUtils::print(IMatrix const *matrix, std::ostream &out) {
    print(matrix, out, DEFAULT_SYMBOLS, DEFAULT_PRECISION);
}


void MatrixUtils::print(IVector const *vector, std::ostream &out, int symbols, int precision) {
    int size = vector->size();

    out << std::setprecision(precision);
    for(int i = 0; i < size; i++) {
        out << std::setw(symbols) << vector->get(i);
    }
    out << std::endl;
}

void MatrixUtils::print(IVector const *vector, std::ostream &out) {
    print(vector, out, DEFAULT_SYMBOLS, DEFAULT_PRECISION);
}

double MatrixUtils::getRandomDouble(double minValue, double maxValue) {
    double value = (double)rand() / RAND_MAX;
    return minValue + value * (maxValue - minValue);
}

void MatrixUtils::fillRandomMatrix(IMatrix *matrix) {
    srand((unsigned int)time(NULL));

    for (int i = 0; i < matrix->rowCount(); i++) {
        for (int j = 0; j < matrix->columnCount(); j++) {
            matrix->set(i, j, getRandomDouble(DEFAULT_MIN_VALUE, DEFAULT_MAX_VALUE));
        }
    }
}

void MatrixUtils::fillRandomVector(IVector *vector) {
    srand((unsigned int)time(NULL));

    for (int i = 0; i < vector->size(); i++) {
        vector->set(i, getRandomDouble(DEFAULT_MIN_VALUE, DEFAULT_MAX_VALUE));
    }
}

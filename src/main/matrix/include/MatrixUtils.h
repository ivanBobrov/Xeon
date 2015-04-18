#ifndef STATIC_MATRIX_H
#define STATIC_MATRIX_H

#include <stddef.h>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include "IMatrix.h"
#include "IVector.h"

class MatrixUtils {
private:
    static const int DEFAULT_SYMBOLS = 20;
    static const int DEFAULT_PRECISION = 15;
    static const int DEFAULT_MIN_VALUE = 0;
    static const int DEFAULT_MAX_VALUE = 100;

    static double getRandomDouble(double minValue, double maxValue);

public:
    static void product(IMatrix const *A, IMatrix const *B, IMatrix *result);
    static void product(IMatrix const *A, IVector const *v, IVector *result);
    static bool compare(IMatrix const *A, IMatrix const *B, const double epsilon);
    static bool compare(IVector const *A, IVector const *B, const double epsilon);
    static void print(IMatrix const *matrix, std::ostream &out);
    static void print(IVector const *vector, std::ostream &out);
    static void print(IMatrix const *matrix, std::ostream &out, int symbols, int precision);
    static void print(IVector const *vector, std::ostream &out, int symbols, int precision);
    static void fillRandomMatrix(IMatrix *matrix);
    static void fillRandomVector(IVector *vector);

};

#endif
#ifndef SQUARE_SOLVER_H_INCLUDED
#define SQUARE_SOLVER_H_INCLUDED

#include <stdlib.h>
const double EPS = 1e-3;

#define meow_assert(expression, fmt, ...) \
do { \
    if (!(expression)) { \
        printf("Assertion failed: %s, file %s, function %s, line %d\n", \
                #expression, __FILE__, __func__, __LINE__); \
        printf(fmt "\n", ##__VA_ARGS__); \
        abort(); \
    } \
} while(0)

enum LessMore{
    LESS  = -1,
    EQUAL = 0,
    MORE  = 1
};

enum RootsCount{
    ZERO_ROOTS     = 0,
    ONE_ROOT       = 1,
    TWO_ROOTS      = 2,
    INFINITE_ROOTS = 3
};

struct QuadraticEquation{ //ax^2 + bx + c = a(x - x1)(x - x2)
    double a, b, c;       //коэффициенты квадратного уравнения
    RootsCount nroots;    //количество его корней
    double x1, x2;        //его корни (если один корень, то он будет лежать в x1,
};//                         а если ноль или бесконечность корней, то ни в одном из них)

int Pow(int base, int power);
void SwapDouble(double* a, double* b);
LessMore CmpDouble(double a, double b);
bool IsZero(double a);
RootsCount FindLinearRoots(double k, double c, double* root);
RootsCount FindSquareRoots(QuadraticEquation *quadratic_eq);

#endif

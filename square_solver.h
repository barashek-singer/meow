#ifndef SQUARE_SOLVER_H_INCLUDED
#define SQUARE_SOLVER_H_INCLUDED

const double EPS = 1e-3;

 //__func__    __PRETTYFUNC__      __FILE__    __LINE__   макросы

#define meow_assert(expression, fmt, ...) \
do{\
    if(!(expression)){\
        printf("Assertion failed: %s, file %s, function %s, line %d\n", #expression, __FILE__, __func__, __LINE__);\
        printf(fmt, __VA_ARGS__);\
    }\
} while(0)
//__VA_ARGS__

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
    double a, b, c;
    RootsCount nroots;
    double x1, x2;
};

int Pow(int base, int power);
void SwapDouble(double* a, double* b);
LessMore CmpDouble(double a, double b);
bool IsZero(double a);
RootsCount FindLinearRoots(double k, double c, double* root);
RootsCount FindSquareRoots(QuadraticEquation *quadratic_eq);

#endif

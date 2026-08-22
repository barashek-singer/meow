#ifndef SQUARE_SOLVER_H_INCLUDED

#define SQUARE_SOLVER_H_INCLUDED

const double EPS = 1e-6;

enum InputErrors
{
    NO_INPUT_ERROR                  = 0,
    INPUT_ERROR_SCANF               = 1,
    INPUT_ERROR_EXTRA_SYMBOLS_AFTER = 2,
    INPUT_ERROR_INF_NAN             = 3
};

enum QuantityRoots
{
    ZERO_ROOTS     = 0,
    ONE_ROOT       = 1,
    TWO_ROOTS      = 2,
    INFINITE_ROOTS = 3
};

struct QuadraticEquation{ //ax^2 + bx + c = a(x - first_root)(x - second_root)
    double a, b, c;
    double first_root, second_root;
};

int ComparisonDouble(double a, double b);
int IsZero(double a);
void ShowError(int error_vale);
int InputCoefficient(double* coefficient, char letter_coefficient);
void PrintAddend(double num, const char* name);
void PrintSign(double num);
void SkipToEndStr();
void PrintRoots(QuadraticEquation quadratic_equation, int roots_count);

#endif

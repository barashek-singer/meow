#ifndef MATH_FUNC_H_INCLUDED

#define MATH_FUNC_H_INCLUDED

const double EPS = 1e-6;
const int INFINITE_ROOTS = 10000000;

int ComparisonDouble(double a, double b);
int IsZero(double a);
int FindLinearRoots(double k, double c, double* root);
int FindSquareRoots(double a, double b, double c, double *first_root, double *second_root);

#endif

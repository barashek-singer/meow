#include <assert.h>
#include <math.h>
#include "math_func.h"

int ComparisonDouble(double a, double b){
    return fabs(a - b) < EPS;
}

int IsZero(double a){
    return ComparisonDouble(a, 0);
}

int FindLinearRoots(double k, double c, double* root){
    assert(root != NULL);

    if(IsZero(k) && IsZero(c)) //Бесконечное число корней
        return INFINITE_ROOTS;

    if(IsZero(k)) //нет корней
        return 0;

    //один корень
    *root = -c / k;
    return 1;
}

int FindSquareRoots(double a, double b, double c, double *first_root, double *second_root){
    assert(first_root != NULL);
    assert(second_root != NULL);
    assert(first_root != second_root);

    if(IsZero(a))
        return FindLinearRoots(b, c, first_root);

    double D = b * b - 4 * a * c; //Дискриминант квадратного уравнения

    if(D < 0) //нет корней
        return 0;

    if(IsZero(D)){
        //один корень
        *first_root = -b / (2. * a);
        return 1;
    }
    //два корня
    *first_root = (-b - sqrt(D)) / (2. * a);
    *second_root = (-b + sqrt(D)) / (2. * a);
    return 2;
}

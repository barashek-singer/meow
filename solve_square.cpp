#include <math.h>
#include <stdio.h>
#include <assert.h>
#include "comparison_double.h"
#include "solve_linear.h"

int FindSquareRoots(double a, double b, double c, double *first_root, double *second_root){
    assert(first_root != NULL);
    assert(second_root != NULL);
    assert(first_root != second_root);

    if(ComparisonDouble(a, 0))
        return FindLinearRoots(b, c, first_root);

    double D = b * b - 4 * a * c; //Дискриминант квадратного уравнения

    if(D < 0) //нет корней
        return 0;

    if(ComparisonDouble(D, 0)){
        //один корень
        *first_root = -b / (2. * a);
        return 1;
    }
    //два корня
    *first_root = (-b + sqrt(D)) / (2. * a);
    *second_root = (-b - sqrt(D)) / (2. * a);
    return 2;
}

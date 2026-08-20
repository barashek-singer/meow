#include <assert.h>
#include "solve_linear.h"
#include "comparison_double.h"

int FindLinearRoots(double k, double c, double* root){
    assert(root != NULL);

    if(ComparisonDouble(k, 0) && ComparisonDouble(c, 0)) //Ѕесконечное число корней
        return INF;

    if(ComparisonDouble(k, 0)) //нет корней
        return 0;

    //один корень
    *root = -c / k;
    return 1;
}


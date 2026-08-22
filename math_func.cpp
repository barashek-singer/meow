#include <math.h>
#include "square_solver.h"

int ComparisonDouble(double a, double b){
    if(fabs(a - b) < EPS)
        return 0;

    return (a < b) ? -1 : 1;
}

int IsZero(double a){
    return !ComparisonDouble(a, 0);
}

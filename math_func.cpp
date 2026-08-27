#include <math.h>
#include <assert.h>
#include "square_solver.h"

LessMore CmpDouble(double a, double b){
    if (fabs(a - b) < EPS)
        return EQUAL;

    return (a < b) ? LESS : MORE;
}

bool IsZero(double a){
    return CmpDouble(a, 0) == EQUAL;
}

RootsCount FindLinearRoots(double b, double c, double* root){ //bx + c = 0
    assert(root != NULL);

    if (IsZero(b) && IsZero(c)) //Ѕесконечное число корней
        return INFINITE_ROOTS;

    if (IsZero(b)) //нет корней
        return ZERO_ROOTS;

    //один корень
    *root = -c / b;
    return ONE_ROOT;
}

RootsCount FindSquareRoots(QuadraticEquation *quadratic_eq){
    assert(quadratic_eq != NULL);

    if (IsZero(quadratic_eq->a)) //ѕри a = 0 выражение становитс€ линейным
        return FindLinearRoots(quadratic_eq->b, quadratic_eq->c, &(quadratic_eq->x1));

    double discriminant = quadratic_eq->b * quadratic_eq->b - 4 * quadratic_eq->a * quadratic_eq->c; //ƒискриминант квадратного уравнени€

    if (discriminant < 0) //нет корней
        return ZERO_ROOTS;

    if (IsZero(discriminant)){ //один корень
        quadratic_eq->x1 = -quadratic_eq->b / (2 * quadratic_eq->a);
        return ONE_ROOT;
    }

    double sqrt_d = sqrt(discriminant);

    //два корн€
    quadratic_eq->x1 = (-quadratic_eq->b - sqrt_d) / (2 * quadratic_eq->a);
    quadratic_eq->x2 = (-quadratic_eq->b + sqrt_d) / (2 * quadratic_eq->a);
    return TWO_ROOTS;
}

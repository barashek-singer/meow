#include <stdio.h>
#include <TXLib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include "square_solver.h"

int FindLinearRoots(double k, double c, double* root);
int FindSquareRoots(QuadraticEquation *quadratic_equation);

int main(void) {
    QuadraticEquation quadratic_equation = {NAN, NAN, NAN, NAN, NAN};

    puts("Введите коэффициенты квадратного уравнения вида: ax^2 + bx + c = 0");
    while (InputCoefficient(&quadratic_equation.a, 'a') != NO_INPUT_ERROR)
        continue;
    while (InputCoefficient(&quadratic_equation.b, 'b') != NO_INPUT_ERROR)
        continue;
    while (InputCoefficient(&quadratic_equation.c, 'c') != NO_INPUT_ERROR)
        continue;

    int roots_count = FindSquareRoots(&quadratic_equation);
    PrintRoots(quadratic_equation, roots_count);

    puts("Mew~");
    return 0;
}

int FindLinearRoots(double b, double c, double* root){ //bx + c = 0
    assert(root != NULL);

    if(IsZero(b) && IsZero(c)) //Бесконечное число корней
        return INFINITE_ROOTS;

    if(IsZero(b)) //нет корней
        return ZERO_ROOTS;

    //один корень
    *root = -c / b;
    return ONE_ROOT;
}

int FindSquareRoots(QuadraticEquation *quadratic_equation){
    assert(quadratic_equation != NULL);

    if(IsZero(quadratic_equation->a)) //При a = 0 выражение становится линейным
        return FindLinearRoots(quadratic_equation->b, quadratic_equation->c, &(quadratic_equation->first_root));

    double D = quadratic_equation->b * quadratic_equation->b - 4 * quadratic_equation->a * quadratic_equation->c; //Дискриминант квадратного уравнения

    if(D < 0) //нет корней
        return ZERO_ROOTS;

    if(IsZero(D)){ //один корень
        quadratic_equation->first_root = -quadratic_equation->b / (2. * quadratic_equation->a);
        return ONE_ROOT;
    }

    //два корня
    quadratic_equation->first_root = (-quadratic_equation->b - sqrt(D)) / (2. * quadratic_equation->a);
    quadratic_equation->second_root = (-quadratic_equation->b + sqrt(D)) / (2. * quadratic_equation->a);
    return TWO_ROOTS;
}

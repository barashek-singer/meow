#include <TXLib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "square_solver.h"

void SkipToEndStr(){
    scanf("%*[^\n]");
}

void SkipBlancSymbols(){
    scanf("%*[ \t]");
}

ErrCode InputCoefficient(double* coefficient, const char letter_coefficient){
    assert(coefficient != NULL);

    printf("Введите %c: ", letter_coefficient);

    int temp_ch = '\0';
    ErrCode error_val = NO_ERRORS_FOUND;

    if (scanf("%lg", coefficient) != 1){ //успешный ли ввод
        error_val = ERROR_SCANF;
        SkipToEndStr();
    }

    else //нет ли символов после
        while ((temp_ch = getchar()) != '\n')
            if (!isspace(temp_ch)){
                error_val = ERROR_EXTRA_SYMBOLS_AFTER;
                SkipToEndStr(); //ПИЗДА(то)
            }

    if (error_val == NO_ERRORS_FOUND && !isfinite(*coefficient)) //является ли числом
        error_val = ERROR_INF_NAN;

    ShowError(error_val);

    return error_val;
}

ErrCode InputStruct(FILE* fp, QuadraticEquation* quadratic_eq){
    assert(fp != NULL);
    assert(quadratic_eq != NULL);

    int nroots = 0;

    if(fscanf(fp, "%lg %lg %lg %d %lg %lg", &quadratic_eq->a, &quadratic_eq->b, &quadratic_eq->c, &nroots, &quadratic_eq->x1, &quadratic_eq->x2) != 6)
        return ERROR_FSCANF;

    quadratic_eq->nroots = (RootsCount)nroots;

    return NO_ERRORS_FOUND;
}

void InputCoefficients(QuadraticEquation *quadratic_eq){
    assert(quadratic_eq != NULL);
    puts("Введите коэффициенты квадратного уравнения вида: ax^2 + bx + c = 0");

    while (InputCoefficient(&quadratic_eq->a, 'a') != NO_ERRORS_FOUND)
        continue;

    while (InputCoefficient(&quadratic_eq->b, 'b') != NO_ERRORS_FOUND)
        continue;

    while (InputCoefficient(&quadratic_eq->c, 'c') != NO_ERRORS_FOUND)
        continue;
}

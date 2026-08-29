#include <TXLib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>
#include "meowio.h"
#include "square_solver.h"

void SkipToEndStr(){
    scanf("%*[^\n]");
}

void SkipBlancSymbols(){
    scanf("%*[ \t]");
}

ErrCode InputCoefficient(double* coefficient, const char letter_coefficient){
    meow_assert(coefficient != NULL, "%s", "-,-\n");

    ChooseModification(YELLOW_TEXT);
    printf("Введите %c: ", letter_coefficient);
    ChooseModification(RESET_TEXT);

    int temp_ch = '\0';

    if (scanf("%lg", coefficient) != 1){ //успешный ли ввод
        SkipToEndStr();
        return WARNING_SCANF;
    }

    while ((temp_ch = getchar()) != '\n')
            if (!isspace(temp_ch)){
                SkipToEndStr();
                return WARNING_EXTRA_SYM_AFTER;
            }

    if (!isfinite(*coefficient)) //является ли числом
        return WARNING_INF_NAN;

    return NO_ERRORS_FOUND;
}

ErrCode InputStruct(FILE* fp, QuadraticEquation* quadratic_eq){
    meow_assert(fp != NULL, "%s", "-,-\n");
    meow_assert(quadratic_eq != NULL, "%s", "-,-\n");

    int nroots = 0;

    if(fscanf(fp, "%lg %lg %lg %d %lg %lg", &quadratic_eq->a, &quadratic_eq->b, &quadratic_eq->c, &nroots, &quadratic_eq->x1, &quadratic_eq->x2) != 6)
        return ERROR_FSCANF;

    quadratic_eq->nroots = (RootsCount)nroots;

    return NO_ERRORS_FOUND;
}

void InputCoefficients(QuadraticEquation *quadratic_eq){
    meow_assert(quadratic_eq != NULL, "%s", "-,-\n");
    puts("Введите коэффициенты квадратного уравнения вида: ax^2 + bx + c = 0");

    ErrCode error_code = NO_ERRORS_FOUND;
    while ((error_code = InputCoefficient(&quadratic_eq->a, 'a')) != NO_ERRORS_FOUND)
        ManageErrors(error_code);

    while ((error_code = InputCoefficient(&quadratic_eq->b, 'b')) != NO_ERRORS_FOUND)
        ManageErrors(error_code);

    while ((error_code = InputCoefficient(&quadratic_eq->c, 'c')) != NO_ERRORS_FOUND)
        ManageErrors(error_code);
}

#include <TXLib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>
#include "meowio.h"
#include "square_solver.h"

ErrCode UniteErrorCodes(ErrCode error_code1, ErrCode error_code2){
    return (ErrCode)((int)error_code1 | (int)error_code2);
}

ErrCode IntersectErrorCodes(ErrCode error_code1, ErrCode error_code2){
    return (ErrCode)((int)error_code1 & (int)error_code2);
}

void SkipToEndStr(){
    scanf("%*[^\n]");
}

void SkipBlancSymbols(){ //пропускает только пробелы и табы
    scanf("%*[ \t]");
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

void InputCoefficient(double* coefficient, const char letter_coefficient){
    meow_assert(coefficient != NULL, "%s", "-,-\n");
    ErrCode error_code = NO_ERRORS_FOUND;
    do{
        ChooseModification(YELLOW_TEXT);
        printf("¬ведите %c: ", letter_coefficient);
        ChooseModification(RESET_TEXT);

        int temp_ch = '\0';
        error_code = NO_ERRORS_FOUND;

        if (scanf("%lg", coefficient) != 1){
            SkipToEndStr();
            error_code = WARNING_SCANF;
        }

        else
            while ((temp_ch = getchar()) != '\n')
                if (!isspace(temp_ch)) {
                    SkipToEndStr();
                    error_code = WARNING_EXTRA_SYM_AFTER;
                }


        if (error_code == NO_ERRORS_FOUND && !isfinite(*coefficient))
            error_code = WARNING_INF_NAN;

        ManageErrors(error_code);
    } while(error_code != NO_ERRORS_FOUND);
}

void InputCoefficients(QuadraticEquation *quadratic_eq){
    meow_assert(quadratic_eq != NULL, "%s", "-,-\n");
    puts("¬ведите коэффициенты квадратного уравнени€ вида: ax^2 + bx + c = 0");

    InputCoefficient(&quadratic_eq->a, 'a');
    InputCoefficient(&quadratic_eq->b, 'b');
    InputCoefficient(&quadratic_eq->c, 'c');
}

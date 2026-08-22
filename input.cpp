#include <TXLib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "square_solver.h"

void ShowError(int error_vale){
    switch (error_vale){
        case INPUT_ERROR_SCANF:
            puts("Ну, число как минимум должно начинаться с цифры или его знака (не более одного)");
            break;

        case INPUT_ERROR_EXTRA_SYMBOLS_AFTER:
            puts("После числа не должно быть символов за исключением пробельных");
            break;

        case INPUT_ERROR_INF_NAN:
            puts("Не, ну ты издеваешься");
            break;

        default:
            //Ура блять
            break;
    }
}

void SkipToEndStr(){
    scanf("%*[^\n]");
}

int InputCoefficient(double* coefficient, char letter_coefficient){

    printf("Введите %c: ", letter_coefficient);

    int temp_ch = '\0';
    int error_vale = NO_INPUT_ERROR;

    if(!scanf("%lf", coefficient)){ //успешный ли ввод
        error_vale = INPUT_ERROR_SCANF;
        SkipToEndStr();
    }

    else //нет ли символов после
        while((temp_ch = getchar()) != '\n')
            if(!isspace(temp_ch)){
                error_vale = INPUT_ERROR_EXTRA_SYMBOLS_AFTER;
                SkipToEndStr();
            }

    if(!error_vale && !isfinite(*coefficient)) //является ли числом
        error_vale = INPUT_ERROR_INF_NAN;

    ShowError(error_vale);

    return error_vale;
}

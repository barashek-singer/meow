#include <TXLib.h>
#include <stdio.h>
#include "input.h"

enum InputErrors
{
    NO_INPUT_ERROR,
    INPUT_ERROR_SCANF,
    INPUT_ERROR_EXTRA_SYMBOLS_AFTER,
    INPUT_ERROR_INF_NAN
};

void ShowError(int error_vale){
    switch (error_vale){
        case INPUT_ERROR_SCANF:
            puts("Ошибка ввода, число должно состоять из цифр и не более одной точки");
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

int InputCoefficient(double* coefficient, char letter_coefficient){

    printf("Введите %c: ", letter_coefficient);

    int ch = '\0';
    int error_vale = NO_INPUT_ERROR;

    if(!scanf("%lf", coefficient)){ //успешный ли ввод
        error_vale = INPUT_ERROR_SCANF;
        scanf("%*[^\n]");
    }

    else //нет ли символов после
        while((ch = getchar()) != '\n')
            if(!isspace(ch)){
                error_vale = INPUT_ERROR_EXTRA_SYMBOLS_AFTER;
                scanf("%*[^\n]");
            }

    if(!error_vale && !isfinite(*coefficient)) //является ли числом
        error_vale = INPUT_ERROR_INF_NAN;

    ShowError(error_vale);

    return error_vale;
}

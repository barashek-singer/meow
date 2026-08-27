#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "square_solver.h"
#include "print.h"

const int SIGN_LEN = 1;

bool CheckTestFlag(const char* arg);
void PrintErrorFlag(const char* text, const char* in_flag);
ErrCode ParseFlags(int argc, char* argv[]);
bool IsNumber(const char* str);

int main(int argc, char* argv[]) {
    /*
    --help - Сводка флагов и что вообще делает программа (действительно)
    --tests rand_tests_count - запуск проверки корректности вычисления корней квадратного уравнения, rand_tests_count из которых - рандомные (по умолчанию 0)
    */

    ErrCode error_code = ParseFlags(argc, argv);
    ShowError(error_code);

    bool continue_program = true;

    while (continue_program){
        QuadraticEquation quadratic_eq = {0, 0, 0, ZERO_ROOTS, 0, 0};

        InputCoefficients(&quadratic_eq);

        quadratic_eq.nroots = FindSquareRoots(&quadratic_eq);
        PrintResult(quadratic_eq);

        continue_program = AskQuestion();
    }

    puts("Mew~ (end of program <3)");
    return 0;
}

ErrCode ParseFlags(int argc, char* argv[]){
    for (int arg_num = 1; arg_num < argc; ++arg_num){
        assert(0 <= arg_num && arg_num < argc);
        if (!strcmp(argv[arg_num], TEST_FLAG)){
            int rand_tests_count = 0;

            if (arg_num + 1 < argc && strcmp(argv[arg_num + 1], "--")){

                bool correct_input = CheckTestFlag(argv[++arg_num]);

                if(!correct_input)
                    exit(1);

                rand_tests_count = atoi(argv[arg_num]);
            }

            ErrCode error_code = RunTests(rand_tests_count);
            if(error_code != NO_ERRORS_FOUND)
                return error_code;
        }

        else if (!strcmp(argv[arg_num], HELP_FLAG))
            PrintHelp();

        else{
            printf("%s - неизвестный флаг\n"
                   "Советую написать мне в лс, являетесь ли вы фурри"
                   "Ну или может написать просто \"%s %s\"",
                        argv[arg_num], argv[0], HELP_FLAG);
            exit(0);
        }
    }

    return NO_ERRORS_FOUND;
}

bool CheckTestFlag(const char* arg){
    assert(arg != NULL);

    if(!IsNumber(arg)){
        PrintErrorFlag("Введённый аргумент не является числом", TEST_FLAG); //TODO
        return false;
    }

    if(arg[0] == '-'){
        PrintErrorFlag("Количество тестов должно быть неотрицательным", TEST_FLAG);
        return false;
    }

    if (strlen(arg) > 6){ //TODO 6 - порядок степени 10 (менее 10^6 тестов вот тута v)
        PrintErrorFlag("Слишком большее число: максимальное количество тестов - 999999", TEST_FLAG);
        return false;
    }

    return true;
}

void PrintErrorFlag(const char* text, const char* in_flag){
    assert(text != NULL);
    assert(in_flag != NULL);

    printf("in arg_num %s: %s", in_flag, text);
}

bool IsNumber(const char* str){ /////////
    assert(str != NULL);
    if(!strncmp(str, "-", SIGN_LEN + 1) || !strncmp(str, "+", SIGN_LEN + 1))
        return false;

    if((*str) == '-' || (*str) == '+')
        ++str;

    while(*str != '\0')
        if(!isdigit(*str++))
            return false;

    return true;
}

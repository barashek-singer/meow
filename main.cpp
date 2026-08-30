#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "square_solver.h"
#include "math_func.cpp"
#include "meowio.h"
#include "input.cpp"
#include "print.cpp"
#include "testing_system.h"
#include "testing_system.cpp"

const int SIGN_LEN = 1;
const int DECIMAL_ORDER = 6;

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

    if (error_code != NO_ERRORS_FOUND){
        ShowError(error_code);
        return 1;
    }

    bool continue_program = true;

    while (continue_program){
        QuadraticEquation quadratic_eq = {0, 0, 0, ZERO_ROOTS, 0, 0};

        InputCoefficients(&quadratic_eq);

        quadratic_eq.nroots = FindSquareRoots(&quadratic_eq);
        PrintResult(quadratic_eq);

        continue_program = AskQuestion();
    }

    ChooseModification(PURPLE_TEXT);
    ChooseModification(SLOW_BLINK_TEXT);
    puts("Mew~ (end of program <3)");
    ChooseModification(RESET_TEXT);

    return 0;
}

ErrCode ParseFlags(int argc, char* argv[]){
    for (int arg_num = 1; arg_num < argc; arg_num++){
        meow_assert(0 <= arg_num && arg_num < argc, "%s", "Ебать ты лох, c массивами работать не умеешь\n");

        if (!strncmp(argv[arg_num], TEST_FLAG, strlen(TEST_FLAG) + 1)){
            size_t rand_tests_count = 0;
            bool correct_input = true;

            if (arg_num + 1 < argc && strncmp(argv[arg_num + 1], "--", 2)){

                correct_input = CheckTestFlag(argv[++arg_num]);
                if (!correct_input)
                    return ERROR_FLAG;

                rand_tests_count = (size_t)atoi(argv[arg_num]);
            }

            ErrCode error_code = RunAllTests(rand_tests_count);
            if (error_code != NO_ERRORS_FOUND)
                return error_code;
        }

        else if (!strncmp(argv[arg_num], HELP_FLAG, strlen(HELP_FLAG) + 1))
            PrintHelp();

        else{
            printf("%s - неизвестный флаг\n"
                   "Советую написать мне в лс (в тг я котик_мяу_фурри_лол_йоу), являетесь ли вы фурри, раз вы любите такие флаги;)\n"
                   "Ну или можете написать просто \"%s %s\"\n",
                        argv[arg_num], argv[0], HELP_FLAG);
            return ERROR_FLAG;
        }
    }

    return NO_ERRORS_FOUND;
}

bool CheckTestFlag(const char* arg){
    meow_assert(arg != NULL, "%s", "-,-\n");

    if(!IsNumber(arg)){
        PrintErrorFlag("Введённый аргумент не является числом\n", TEST_FLAG);
        return false;
    }

    if(arg[0] == '-'){
        PrintErrorFlag("Количество тестов должно быть неотрицательным\n", TEST_FLAG);
        return false;
    }

    //"откидывание" ведущих нулей
    const char* str = arg;
    while(*str == '0')
        ++str;

    //если в итоге число является нулём
    if (*str == '\0')
        return true;

    if (strlen(str) > DECIMAL_ORDER){
        char text[80] = "";
        snprintf(text, sizeof(text), "Слишком большее число, максимальное количество тестов - %d\n", Pow(10, DECIMAL_ORDER) - 1);
        PrintErrorFlag(text, TEST_FLAG);
        return false;
    }

    return true;
}

void PrintErrorFlag(const char* text, const char* in_flag){
    meow_assert(text != NULL, "%s", "-,-\n");
    meow_assert(in_flag != NULL, "%s", "-,-\n");

    ChooseModification(PURPLE_TEXT);
    ChooseModification(BOLD_TEXT);
    printf("error in flag %s: ", in_flag);
    ChooseModification(RESET_TEXT);

    printf("%s", text);
}

bool IsNumber(const char* str){
    meow_assert(str != NULL, "%s", "-,-\n");

    //"-" и "+" не являются числами
    if(!strncmp(str, "-", SIGN_LEN + 1) || !strncmp(str, "+", SIGN_LEN + 1))
        return false;

    if((*str) == '-' || (*str) == '+')
        ++str;

    while(*str != '\0')
        if(!isdigit(*str++))
            return false;

    return true;
}

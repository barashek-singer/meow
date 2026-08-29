#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdarg.h>
#include "meowio.h"
#include "square_solver.h"

void PrintTextError(){
    ChooseModification(RED_TEXT);
    ChooseModification(BOLD_TEXT);
    printf("error: ");
    ChooseModification(RESET_TEXT);
}

void ShowError(ErrCode error_code){
    switch (error_code){
        case WARNING_SCANF:
            puts("Ну, число как минимум должно начинаться с цифры или его знака (не более одного)");
            break;

        case WARNING_EXTRA_SYM_AFTER:
            puts("После числа не должно быть символов за исключением пробельных");
            break;

        case WARNING_INF_NAN:
            ChooseModification(RED_TEXT);
            ChooseModification(BOLD_TEXT);
            puts("Не, ну ты издеваешься");
            ChooseModification(RESET_TEXT);
            break;

        case ERROR_FOPEN:
            PrintTextError();
            puts("Некорректное открытие файла");
            break;

        case ERROR_FCLOSE:
            PrintTextError();
            puts("Некорректное закрытие файла");
            break;

        case ERROR_FSCANF:
            PrintTextError();
            puts("Некорректное считывание с файла");
            break;

        case ERROR_CALLOC:
            PrintTextError();
            puts("Плохое обращение с динамическое памятью, её надо беречь =(");
            break;

        case ERROR_FLAG:
            PrintTextError();
            puts("Некорректный ввод флагов, программа завершается");
            break;

        case NO_ERRORS_FOUND:
            break;

        default:
            meow_assert(false, "%s", "Как блять\n");
    }
}

void ManageErrors(ErrCode error_code){
    for (int bit = 0; bit <= MAX_ERROR_BIT; bit++)
        if (((error_code >> bit) & 1) == 1)
            ShowError((ErrCode)(1 << bit));
}

void ChooseModification(TextModification text_modification){
    printf("\x1b[%dm", (int)text_modification);
}

void PrintSign(double num){
    printf(" %c ", (num < 0) ? '-' : '+');
}

void PrintAddend(double num, const char* name, int* addends_count){
    meow_assert(name != NULL, "%s", "-,-\n");
    meow_assert(addends_count != NULL, "%s", "-,-\n");

    if (!IsZero(num)){
        if (*addends_count > 0){ //если левая часть имеет хотя бы одно слагаемое то печатаем + или -, а затем модуль слагаемого
            PrintSign(num);
            printf("%lg%s", fabs(num), name);
        }

        else //если слагаемых в левой части нет - выводи просто число
            printf("%lg%s", num, name);
        (*addends_count)++;
    }
}

void PrintResult(const QuadraticEquation quadratic_eq){
    printf("Уравнение ");
    int addends_count = 0;

    ChooseModification(YELLOW_TEXT);

    PrintAddend(quadratic_eq.a, "x^2", &addends_count);
    PrintAddend(quadratic_eq.b, "x", &addends_count);
    PrintAddend(quadratic_eq.c, "", &addends_count);

    //Тут проверка на то, выводилась ли вообще хоть что-то в левой части уравнения
    if(addends_count == 0)
        putchar('0');

    //вывод знака равенства и правой части выражения
    printf(" = 0 ");

    ChooseModification(RESET_TEXT);

    PrintRoots(quadratic_eq);
}

bool AskQuestion(){
    printf("Хотите ли запустить программу снова? (y/N): ");

    SkipBlancSymbols();

    int answer = getchar();
    if (answer != 'y')
        return false;

    SkipBlancSymbols();

    if(getchar() != '\n')
        return false;

    return true;
}

void PrintHelp(){
    putchar('\n');
    puts("Данная программа по введённым коэффициентам квадратного трёхчлена решает квадратное уравнение вида ax^2 + bx + c = 0");
    putchar('\n');

    puts("Доступные флаги:");
    putchar('\n');
    printf("%s rand_tests_count - запуск проверки корректности вычисления корней квадратного уравнения, "
        "rand_tests_count из которых - рандомные (по умолчанию 0)\n", TEST_FLAG);
    printf("%s - Сводка флагов и что вообще делает программа (действительно)\n\n", HELP_FLAG);
}

void PrintRoots(const QuadraticEquation quadratic_eq){
    switch (quadratic_eq.nroots){
        case ZERO_ROOTS:
            puts("имеет 0 корней");
            break;

        case ONE_ROOT:
            printf("имеет 1 корень: x = %lg\n", quadratic_eq.x1);
            break;

        case TWO_ROOTS:
            printf("имеет 2 корня: x1 = %lg и x2 = %lg\n", quadratic_eq.x1, quadratic_eq.x2);
            break;

        case INFINITE_ROOTS:
            puts("имеет бесконечное число корней");
            break;

        default:
            meow_assert(2 + 2 == 5, "%s", "Как блять"); //специально ложное выражение для ахуевания от того, как сюда попали
    }
}

void PrintFailedTest(size_t num_of_test, const QuadraticEquation quadratic_eq, const QuadraticEquation quadratic_eq_ref){ //color
    ChooseModification(RED_TEXT);
    ChooseModification(BOLD_TEXT);
    printf("\nFAILED на тесте %zu\n", num_of_test);
    ChooseModification(RESET_TEXT);

    ChooseModification(YELLOW_TEXT);
    printf("Коэффициенты: a = %lg, b = %lg, c = %lg\n", quadratic_eq.a, quadratic_eq.b, quadratic_eq.c);
    ChooseModification(RESET_TEXT);

    ChooseModification(GREEN_TEXT);
    printf("Ожидалось: ");
    ChooseModification(RESET_TEXT);
    PrintRoots(quadratic_eq_ref);

    ChooseModification(PURPLE_TEXT);
    printf("Получено: ");
    ChooseModification(RESET_TEXT);
    PrintRoots(quadratic_eq);
}

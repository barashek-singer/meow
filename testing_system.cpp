#include <TXLib.h>
#include <stdio.h>
#include "square_solver.h"
#include "print.h"

#define TEST_FILE "tests.txt"

int RunOneTest(size_t num_of_test, const QuadraticEquation quadratic_eq_ref){
    QuadraticEquation quadratic_eq = {.a = quadratic_eq_ref.a,
                                      .b = quadratic_eq_ref.b,
                                      .c = quadratic_eq_ref.c};

    quadratic_eq.nroots = FindSquareRoots(&quadratic_eq);

    if (quadratic_eq.nroots != quadratic_eq_ref.nroots) {
        PrintFailedTest(num_of_test, quadratic_eq, quadratic_eq_ref);
        return 0;
    }

    switch (quadratic_eq.nroots){ //NOTE Мэйби сократить
        case ZERO_ROOTS: break;

        case ONE_ROOT:
            if(CmpDouble(quadratic_eq.x1, quadratic_eq_ref.x1)){

                PrintFailedTest(num_of_test, quadratic_eq, quadratic_eq_ref);
                return 0;
            }
            break;

        case TWO_ROOTS:
            if (CmpDouble(quadratic_eq.x1, quadratic_eq_ref.x1) ||
               CmpDouble(quadratic_eq.x2, quadratic_eq_ref.x2)){

                PrintFailedTest(num_of_test, quadratic_eq, quadratic_eq_ref);
                return 0;
            }

        case INFINITE_ROOTS:
            break;

        default:
            assert(false); //специально ложное выражение для ахуевания от того, как сюда попали
    }

    return 1;
}

double RandDouble(){
    return (double)rand() + (double)rand() / (double)RAND_MAX;
}

ErrCode RunTests(int rand_tests_count){ //NOTE тоже мэйби как-то сократить

    FILE* fp = fopen(TEST_FILE, "r");
    if (fp == NULL)
        return ERROR_FOPEN;

    size_t fixed_tests_count = 0;
    if(!fscanf(fp, "%zu", &fixed_tests_count)){
        return ERROR_FSCANF;
    }

    QuadraticEquation* tests = (QuadraticEquation*)calloc(fixed_tests_count, sizeof(QuadraticEquation));
    if (tests == NULL)
        return ERROR_CALLOC;

    ErrCode error_code = NO_ERRORS_FOUND;

    for (size_t i = 0; i < fixed_tests_count; i++){
        error_code = InputStruct(fp, tests + i);
        if (error_code != NO_ERRORS_FOUND){
            free(tests);
            return error_code;
        }
    }

    if (fclose(fp) == EOF){
        free(tests);
        return ERROR_FCLOSE;
    }

    size_t num_of_test = 0;
    size_t success_tests_count = 0;

    for (; num_of_test < fixed_tests_count; ++num_of_test)
        success_tests_count += RunOneTest(num_of_test + 1, tests[num_of_test]);

    free(tests);

    for (; rand_tests_count > 0; --rand_tests_count){
        QuadraticEquation quadratic_eq_ref = {.a = RandDouble(), .x1 = RandDouble(), .x2 = RandDouble()};

        if (CmpDouble(quadratic_eq_ref.x1, quadratic_eq_ref.x2) == EQUAL){
            quadratic_eq_ref.b = -quadratic_eq_ref.a * 2 * quadratic_eq_ref.x1;
            quadratic_eq_ref.c = quadratic_eq_ref.a * quadratic_eq_ref.x1 * quadratic_eq_ref.x1;
            quadratic_eq_ref.nroots = ONE_ROOT;
        }

        else{
            if(CmpDouble(quadratic_eq_ref.x1, quadratic_eq_ref.x2) == MORE)
                SwapDouble(&quadratic_eq_ref.x1, &quadratic_eq_ref.x2);

            quadratic_eq_ref.b = -quadratic_eq_ref.a * (quadratic_eq_ref.x1 + quadratic_eq_ref.x2);
            quadratic_eq_ref.c = quadratic_eq_ref.a * quadratic_eq_ref.x1 * quadratic_eq_ref.x2;
            quadratic_eq_ref.nroots = TWO_ROOTS;
        }

        success_tests_count += RunOneTest(++num_of_test, quadratic_eq_ref);
    }

    EscSeq(BOLD_TEXT, CYAN_TEXT, DEFAULT_COLOR_BACKGROUND);
    printf("\nТестов пройдено %zu/%zu\n\n", success_tests_count, num_of_test);
    ResetStyleText();

    return NO_ERRORS_FOUND;
}

void SwapDouble(double* a, double* b){ /////////
    assert(a != NULL);
    assert(b != NULL);

    double temp = *a;
    *a = *b;
    *b = temp;
}

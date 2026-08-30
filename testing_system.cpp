#include <TXLib.h>
#include <stdarg.h>
#include <stdio.h>
#include "meowio.h"
#include "square_solver.h"
#include "testing_system.h"

const char* TEST_FILE = "tests.txt";

int RunOneTest(size_t num_of_test, const QuadraticEquation quadratic_eq_ref){
    QuadraticEquation quadratic_eq = {.a = quadratic_eq_ref.a,
                                      .b = quadratic_eq_ref.b,
                                      .c = quadratic_eq_ref.c};

    quadratic_eq.nroots = FindSquareRoots(&quadratic_eq);

    if (quadratic_eq.nroots != quadratic_eq_ref.nroots) {
        PrintFailedTest(num_of_test, quadratic_eq, quadratic_eq_ref);
        return 0;
    }

    switch (quadratic_eq.nroots){
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
            meow_assert(false, "%s", " ак бл€ть\n"); //специально ложное выражение дл€ удивлени€ от того, как сюда попали
    }

    return 1;
}

double RandDouble(){
    return (double)rand() + (double)rand() / (double)RAND_MAX;
}

ErrCode SafeClose(bool need_free, void* ptr, bool need_fclose, FILE* fp){
    if(need_free)
        free(ptr);

    if(need_fclose)
        if (fclose(fp) == EOF)
            return ERROR_FCLOSE;

    return NO_ERRORS_FOUND;
}

ErrCode StandardTesting(){
    ErrCode error_code = NO_ERRORS_FOUND;
    bool need_free = false, need_fclose = false;

    FILE* fp = fopen(TEST_FILE, "r");
    if (fp == NULL)
        return ERROR_FOPEN;
    need_fclose = true;

    size_t fixed_tests_count = 0;
    if(fscanf(fp, "%zu", &fixed_tests_count) != 1){
        error_code = SafeClose(need_free, NULL, need_fclose, fp);

        return (ErrCode)((int)error_code | (int)ERROR_FSCANF);
    }

    QuadraticEquation* tests = (QuadraticEquation*)calloc(fixed_tests_count, sizeof(QuadraticEquation));
    if (tests == NULL){
        error_code = SafeClose(need_free, NULL, need_fclose, fp);

        return (ErrCode)((int)error_code | (int)ERROR_CALLOC);
    }
    need_free = true;

    for (size_t i = 0; i < fixed_tests_count; i++){
        error_code = InputStruct(fp, tests + i);
        if (error_code != NO_ERRORS_FOUND){
            error_code = SafeClose(need_free, tests, need_fclose, fp);

            return (ErrCode)((int)error_code | (int)ERROR_FSCANF);
        }
    }

    error_code = SafeClose(need_free, tests, need_fclose, fp);

    if (error_code != NO_ERRORS_FOUND)
        return error_code;

    size_t success_tests_count = 0;
    size_t num_of_test = 0;

    for (; num_of_test < fixed_tests_count; ++num_of_test)
        success_tests_count += RunOneTest(num_of_test + 1, tests[num_of_test]);

    ChooseModification(CYAN_TEXT);
    ChooseModification(BOLD_TEXT);
    printf("\n—тандартных тестов пройдено %zu/%zu\n", success_tests_count, fixed_tests_count);
    ChooseModification(RESET_TEXT);

    return NO_ERRORS_FOUND;
}

//---/\---/\-------Ёто ASCII KOT!--//
//  {  '-'  }                      //
//  {  0 0  }     ƒобавь его себе  //
//  --> V <--  в исходник, и тебе  //
//   \ \|/ /      будет, наверно,  //
//    \___/  при€тно отлаживатьс€  //
//---------------долгими ночами:)--//

void RandomTesting(size_t rand_tests_count){
    size_t success_tests_count = 0;
    for (size_t num_of_test = 0; num_of_test < rand_tests_count; num_of_test++){
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

        success_tests_count += RunOneTest(num_of_test + 1, quadratic_eq_ref);
    }

    ChooseModification(CYAN_TEXT);
    ChooseModification(BOLD_TEXT);
    printf("\n—лучайных тестов пройдено %zu/%zu\n\n", success_tests_count, rand_tests_count);
    ChooseModification(RESET_TEXT);
}

ErrCode RunAllTests(size_t rand_tests_count){
    ErrCode error_code = StandardTesting();

    if (error_code != NO_ERRORS_FOUND)
        return error_code;

    if (rand_tests_count > 0)
        RandomTesting(rand_tests_count);

    return NO_ERRORS_FOUND;
}

void SwapDouble(double* a, double* b){
    meow_assert(a != NULL, "%s", "-,-\n");
    meow_assert(b != NULL, "%s", "-,-\n");

    double temp = *a;
    *a = *b;
    *b = temp;
}

#ifndef PRINT_H_INCLUDED
#define PRINT_H_INCLUDED

#define TEST_FLAG "--tests"
#define HELP_FLAG "--help"

void PrintFailedTest(size_t num_of_test, const QuadraticEquation quadratic_eq, const QuadraticEquation quadratic_eq_ref);
void PrintRoots(const QuadraticEquation quadratic_eq);
void PrintResult(const QuadraticEquation quadratic_eq);
void PrintAddend(double num, const char* name);
void PrintSign(double num);
void PrintHelp();
bool AskQuestion();

#endif

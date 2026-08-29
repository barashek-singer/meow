#ifndef TESTING_SYSTEM_H_INCLUDED
#define TESTING_SYSTEM_H_INCLUDED

double RandDouble();
int RunOneTest(size_t num_of_test, const QuadraticEquation quadratic_eq_ref);
ErrCode StandardTesting();
void RandomTesting(size_t rand_tests_count);
ErrCode SafeClose(bool need_free, void* ptr, bool need_fclose, FILE* fp);
ErrCode RunAllTests(size_t rand_tests_count);

#endif

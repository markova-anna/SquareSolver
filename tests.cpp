#include <stdio.h>
#include "tests.h"


/*!
 *\brief starts a unitest and output an error message if necessary
 *\param[in] num_of_test means number of unittest
 *\param[in,out] fulldataforsolving structure includes all information for solving
 *\param[in,out] cnt_test means the amount of tests went great
 */
static void unittest (int num_of_test, DataForSolvingEquations* fulldataforsolving, int* const cnt_test);

static const int AMOUNT_OF_TESTS = 5; ///< amount of unittests

void launch_tests () 
{ 
    int cnt_test = 0;

    DataForSolvingEquations test [AMOUNT_OF_TESTS] = 
    {
        {.a = 1,  .b =  -5, .c =   6, .x1 =    3, .x2 =  2, .nroots =  2},
        {.a = 1,  .b =  -4, .c =   4, .x1 =    2, .x2 =  2, .nroots =  1},
        {.a = 1,  .b =   2, .c =   4, .x1 =    0, .x2 =  0, .nroots =  0},
        {.a = 1,  .b = 1.5, .c = 0.5, .x1 = -0.5, .x2 = -1, .nroots =  2},
        {.a = 0,  .b =   0, .c =   0, .x1 =    0, .x2 =  0, .nroots = -1},
    };

    for (int num_of_test = 0; num_of_test < AMOUNT_OF_TESTS; num_of_test++)
    {
        unittest(num_of_test+1, &test[num_of_test], &cnt_test);
    }
 
} 

static void unittest (const int num_of_test, DataForSolvingEquations* fulldataforsolving, int* const cnt_test) 
{ 
    assert(isfinite(num_of_test)); 
    assert(fulldataforsolving != nullptr); 
    assert(cnt_test != nullptr);

    double x1_initial = 0, x2_initial = 0;
    int nroots_initial = 0;

    x1_initial     = fulldataforsolving->x1;
    x2_initial     = fulldataforsolving->x2;
    nroots_initial = fulldataforsolving->nroots;

    solve_the_equation(fulldataforsolving);

    double x1_end = 0, x2_end = 0;
    int nroots_end = 0;

    x1_end     = fulldataforsolving->x1;
    x2_end     = fulldataforsolving->x2;
    nroots_end = fulldataforsolving->nroots;

    
    if (comparing_doubles(x1_initial, x1_end) != EQUAL || comparing_doubles(x2_initial, x2_end) != EQUAL || nroots_initial != nroots_end)
    {
        PRINTFRED("error test %d: a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nroots = %d\n" 
        "expected x1 = %lg, x2 = %lg, nroots = %d\n", 
        num_of_test, fulldataforsolving->a, fulldataforsolving->b, fulldataforsolving->c,
         x1_end, x2_end, nroots_end, 
        x1_initial, x2_initial, nroots_initial);
    }
    else
    {
        (*cnt_test)++;
    }

    if (*cnt_test == AMOUNT_OF_TESTS)
        PRINTFGREEN("congratulations! no errors!");
} 

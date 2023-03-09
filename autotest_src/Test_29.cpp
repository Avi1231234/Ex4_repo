//
// Created by User on 7/20/2020.
//

#include "autotest_utils.h"

/***
 * check whether assignment operator is deep
 */
int check_assignment_deep()
{
    Matrix M(4, 5), B;

    M[2] = 1;

    B = M;

    B[2] = 2;

    if(M[2] == B[2])
    {
        return 1;
    }

    return 0;
}

int main()
{
    return check_assignment_deep();
}

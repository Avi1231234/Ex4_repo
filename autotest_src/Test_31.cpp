//
// Created by User on 7/20/2020.
//

#include "autotest_utils.h"

/***
 * check multiplication operator
 */
int check_float_multiplication()
{
    Matrix A = get_ordered_matrix(2, 2);

    Matrix B = 2 * A;
    Matrix C = A * 2;

    // Check correct dimensions
    if(B.get_rows() != 2 || B.get_cols() != 2 || C.get_rows() != 2 || C.get_cols() != 2)
    {
        return 1;
    }

    // Check correct values
    Matrix ans = Matrix(2, 2);
    ans[0] = 0;
    ans[1] = 2;
    ans[2] = 4;
    ans[3] = 6;
    for(int i = 0; i < C.get_cols() * C.get_rows(); i++)
    {
        if(C[i] != ans[i] || B[i] != ans[i])
        {
            return 2;
        }
    }
    return 0;
}

int main()
{
    return check_float_multiplication();
}
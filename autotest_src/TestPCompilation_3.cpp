//
// Created by User on 12/26/2019.
//

#include "Matrix.h"
#include <iostream>

/***
 * check all multiplications are const
 */
void check_const_mults()
{
    std::cout << "checking const mult with matrix" << std::endl;
    // set up const matrix 1,1 with value of 1
    Matrix A = Matrix(1, 1);
    A[0] = 1;
    const Matrix M = A;

    // check * operator with matrix is const
    Matrix B = M * M;
}

int main()
{
    check_const_mults();
}

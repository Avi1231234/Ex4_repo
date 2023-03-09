//
// Created by yuval on 13-Oct-21.
//


#include "Matrix.h"
#include <iostream>
#include "autotest_utils.h"

/**
 * call on const objects to make sure Dense getters are const functions
 * if this compiles and returns true we can pass
 * @return
 */
void check_const_sum()
{
    std::cout << "testing if there is a const version for Matrix::sum" << std::endl;
    const Matrix m = get_ordered_matrix(5, 5);
    float s = m.sum();
    std::cout << "got " << s << std::endl;
}

int main()
{
    check_const_sum();
}

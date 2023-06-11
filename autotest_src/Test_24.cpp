//
// Created by Chend on 3/19/2021.
//

#include "Matrix.h"
#include "autotest_utils.h"

/**
 * Should tell the students to
 * @param m
 * This test should catch an exception and return 0.
 *  If 1 was returned, then there is a mistake.
 *  2 on wrong exception
 */
void test_dot_bad_dims(const Matrix &m)
{
    Matrix A = get_ordered_matrix(3, 3);
    Matrix B = get_ordered_matrix(3, 4);
    A.dot(B);

}

int main()
{
    Matrix A = get_ordered_matrix(2, 10);
    try
    {
        test_dot_bad_dims(A);

    }
    catch(const std::length_error &error)
    {
        std::cout << error.what() << std::endl;
        return 0;
    }
    catch(const std::domain_error &error)
    {
        std::cerr << error.what() << std::endl;
        return 0;

    }
    catch(const std::exception &error)
    {
        std::cout << "wrong exception" << std::endl;
        return 1;
    }
    catch(...)
    {
        std::cout << "non-exception thrown" << std::endl;
        return 2;
    }

    std::cout << "nothing thrown" << std::endl;

    return 3;
}

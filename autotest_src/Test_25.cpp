//
// Created by User on 7/20/2020.
//

#include "autotest_utils.h"

/**
 * Should tell the students to
 * @param m
 * This test should catch an exception and return 0.
 *  If 1 was returned, then there is a mistake.
 *  2 on wrong exception
 */
void check_bad_dims_add()
{
    Matrix M = Matrix(3, 3);

    Matrix B = Matrix();

    std::cout << "checking bad dims for addition" << std::endl;
    // should expect an exception
    M = M + B;
}

int main()
{
    try
    {
        check_bad_dims_add();
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

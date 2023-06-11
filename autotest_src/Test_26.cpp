//
// Created by yuval on 13-Oct-21.
//

#include "autotest_utils.h"

/**
 * Should tell the students to
 * @param m
 * This test should catch an exception and return 0.
 *  If 1 was returned, then there is a mistake.
 *  2 on wrong exception
 */
void check_ctor_bad_dims()
{
    std::cout << "checking bad dims in matrix creation" << std::endl;
    // should expect to an exception
    Matrix m = Matrix(0, -1);
}

int main()
{

    try
    {
        check_ctor_bad_dims();
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
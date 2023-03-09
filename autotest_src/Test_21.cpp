//
// Created by User on 7/21/2020.
//

#include "autotest_utils.h"

void check_bad_dims_mult()
{
    std::cout << "checking bad dims for multiplication" << std::endl;
    Matrix M = Matrix(3, 3);

    Matrix B = Matrix();

    // use a bad multiplcation make sure there is a error print.
    M = M * B;
}

/**
 * checking if there was an exception throwing
 * @return 0 on success
 *         1 in failure
 *         2 on wrong exception
 */
int main()
{
    try
    {
        check_bad_dims_mult();
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
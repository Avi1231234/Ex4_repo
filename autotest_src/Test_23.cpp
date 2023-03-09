//
// Created by User on 7/20/2020.
//

#include "autotest_utils.h"

void check_parenthesis_under_limit()
{
    Matrix M = Matrix(3, 3);

    std::cout << "Checking under limit in parenthesis" << std::endl;
    std::cout << M(-1, -1) << std::endl;
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
        check_parenthesis_under_limit();
    }

    catch(const std::out_of_range &error)
    {
        std::cout << error.what() << std::endl;
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

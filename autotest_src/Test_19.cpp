//
// Created by idan alperin on 26/08/2022.
//

#include "autotest_utils.h"
#include <sstream>

/***
 * check the argmax of a matrix, print and compare with diff
 */
int check_large_matrix()
{
    std::cout << "creating a matrix with large dims" << std::endl;

    try
    {
        Matrix m(get_ordered_matrix(500, 600));

        m[10000] = 10;

        m(100, 500) = 200;

        m.plain_print();
    }
    catch(...)
    {
        std::cout << "something thrown" << std::endl;
        return 1;
    }

    return 0;
}

int main()
{
    return check_large_matrix();
}
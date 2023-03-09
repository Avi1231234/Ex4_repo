//
// Created by idan alperin on 26/08/2022.
//

#include "autotest_utils.h"
#include <sstream>

/***
 * check the argmax of a matrix, print and compare with diff
 */
int check_matrix_read_bad()
{
    Matrix M1(2, 3);

    float data[] = {2, 3, 4, 5};

    std::stringstream s;
    s.write((char *) data, sizeof(data));

    try
    {
        s >> M1;
    }
    catch(const std::runtime_error &error)
    {
        std::cout << "got runtime_error: " << error.what() << std::endl;
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

    M1.plain_print();

    std::cout << "nothing thrown" << std::endl;

    return 3;
}

int main()
{
    return check_matrix_read_bad();
}
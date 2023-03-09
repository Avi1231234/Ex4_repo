//
// Created by User on 7/20/2020.
//

#include "autotest_utils.h"
#include "death_new.h"

#define ITERATIONS 6

/***
 * check whether matrix constructor leaks memory when the matrix is 2-dimensional
 * people who use a single array will probably never fail this
 */
int check_matrix_mem_leak()
{
    std::cout << "checking if matrix constructor leaks" << std::endl;
    for(int i = 0; i < ITERATIONS; ++i)
    {
        counter = i;
        try
        {
            Matrix M(10, 15);
        }
        catch(const std::exception &error)
        {
            std::cout << error.what() << std::endl;
        }
        catch(...)
        {
            std::cout << "something thrown" << std::endl;
        }
    }

    return 0;
}

int main()
{
    return check_matrix_mem_leak();
}

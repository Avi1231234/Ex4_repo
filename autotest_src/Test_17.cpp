//
// Created by idan alperin on 26/08/2022.
//

#include "autotest_utils.h"
#include <sstream>

/***
 * check the argmax of a matrix, print and compare with diff
 */
int check_matrix_read()
{
    Matrix M1(2, 3);

    float data[] = {2.1, 3, 4, 5.5, 6.3, 7};

    std::stringstream s;
    s.write((char *) data, sizeof(data));

    try
    {
        s >> M1;
    }
    catch(...)
    {
        std::cerr << "got an exception" << std::endl;
        return 1;
    }

    M1.plain_print();

    for(int i = 0; i < 6; ++i)
    {
        if(M1[i] != data[i])
        {
            return 2;
        }
    }

    return 0;
}

int main()
{
    return check_matrix_read();
}
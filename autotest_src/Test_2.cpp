//
// Created by User on 7/20/2020.
//
#include "autotest_utils.h"

int check_brackets()
{
    Matrix M = get_ordered_matrix(7, 9);
    // Check const bracket operator
    for(int i = 0; i < M.get_cols() * M.get_rows(); i++)
    {
        if(M[i] != i)
        {
            return 1;
        }
    }
    // Check non-const bracket operator
    for(int j = 0; j < M.get_cols() * M.get_rows(); j++)
    {
        try {
            M[j] = j+1;
        } catch(...){
            return 1;
        }
    }
    return 0;
}

int main()
{
    return check_brackets();
}
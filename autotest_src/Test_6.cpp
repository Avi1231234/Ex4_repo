//
// Created by User on 7/20/2020.
//

#include "autotest_utils.h"

/**
 * check result and invalid indices
 * of parenthesis
 */
int check_parenthesis()
{
    Matrix M = get_ordered_matrix(8, 3);

    // Check correct values
    for(int i = 0; i < M.get_rows(); i++)
    {
        for(int j = 0; j < M.get_cols(); j++)
        {
            if(M(i, j) != (i * M.get_cols()) + j)
            {
                return 1;
            }
        }
    }
    return 0;
}

int main()
{
    return check_parenthesis();

}
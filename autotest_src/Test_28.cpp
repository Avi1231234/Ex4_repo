//
// Created by User on 7/20/2020.
//

#include "autotest_utils.h"

/***
 * check the assignment operator for a Matrix object.
 */
int check_self_assignment()
{
    Matrix m = get_ordered_matrix(4, 5);

    // checking self assignment
    // will cause valgrind to fail if not done properly! (or double delete which is a runtime error)
    m = m;

    // assignment operator CAN receive by value for swap idiom
    /*using Traits = function_traits<decltype(&Matrix::operator=)>;
    if(!std::is_same<const Matrix &, Traits::argument<1>::type>::value)
    {
        std::cerr << "Operator= does not accept by const reference" << std::endl;
        B.~Matrix();
        return 2;
    }*/

    return 0;
}

int main()
{
    return check_self_assignment();
}

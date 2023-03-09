//
// Created by yuval on 13-Oct-21.
//


#include "Dense.h"
#include <iostream>

/**
 * call on const objects to make sure Dense getters are const functions
 * if this compiles and returns true we can pass
 * @return
 */
bool test_dense_constructor()
{
    std::cout << "testing if there isn't a default constructor for Dense" << std::endl;
    Dense d = Dense();
    return true;
}

int main()
{
    test_dense_constructor();
}

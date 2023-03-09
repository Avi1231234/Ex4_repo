//
// Created by User on 12/26/2019.
//

#include "Matrix.h"
#include "Activation.h"
#include <iostream>

void check_activation_const_params()
{
    std::cout << "checking const parameters Activation () operator" << std::endl;
    const Matrix A = Matrix();
    // see if compiles
    activation::relu(A);
    activation::softmax(A);
}

int main()
{
    check_activation_const_params();
}

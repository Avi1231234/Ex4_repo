//
// Created by User on 7/21/2020.
//

#include "autotest_utils.h"

int check_activation_type()
{

    Matrix weights(5, 1), bias(5, 1);

    Dense d1 = Dense(weights, bias, activation::relu);
    Dense d2 = Dense(weights, bias, activation::softmax);

    if(d1.get_activation() != activation::relu || d2.get_activation() != activation::softmax)
    {
        return 1;
    }
    return 0;

}

int main()
{
    return check_activation_type();
}

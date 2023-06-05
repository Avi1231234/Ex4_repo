


#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

namespace activation
{
    Matrix relu(const Matrix &m);

    Matrix softmax(const Matrix &m);

    typedef Matrix (*func_t)(const Matrix &);
}

#endif //ACTIVATION_H

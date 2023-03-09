
#include "Activation.h"

Matrix activation::relu(const Matrix &m)
{
    Matrix output(m);

    for(int i = 0; i < m.get_rows() * m.get_cols(); i++)
    {
        if(m[i] < 0)
        {
            output[i] = 0;
        }
    }

    return output;
}

Matrix activation::softmax(const Matrix &m)
{
    Matrix output(m);

    for(int i = 0; i < m.get_rows() * m.get_cols(); i++)
    {
        output[i] = std::exp(m[i]);
    }

    return (1 / output.sum()) * output;
}

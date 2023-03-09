//
// Created by yuval on 01-Oct-21.
//

#include "Dense.h"

Dense::Dense(const Matrix &w, const Matrix &bias,
             activation::func_t act_type)
    : _weights(w), _bias(bias), _activation(act_type)
{}

const Matrix &Dense::get_weights() const
{
    return _weights;
}

const Matrix &Dense::get_bias() const
{
    return _bias;
}

Matrix &Dense::get_weights()
{
    return _weights;
}

Matrix &Dense::get_bias()
{
    return _bias;
}

activation::func_t Dense::get_activation() const
{
    return _activation;
}

Matrix Dense::operator()(const Matrix &m) const
{
    return _activation((_weights * m) + _bias);
}

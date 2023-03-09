//
// Created by yuval on 01-Oct-21.
//
#include "Activation.h"

#ifndef DENSE_H
#define DENSE_H

class Dense {
 public:
    Dense(const Matrix &w, const Matrix &bias, activation::func_t act_type);
    const Matrix &get_weights() const;
    const Matrix &get_bias() const;
    Matrix &get_weights();
    Matrix &get_bias();
    activation::func_t get_activation() const;
    Matrix operator()(const Matrix &m) const;

 private:
    Matrix _weights;
    Matrix _bias;
    activation::func_t _activation;
};

#endif //DENSE_H

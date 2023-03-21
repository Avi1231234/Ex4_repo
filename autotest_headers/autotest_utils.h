//
// Created by roiko on 21-Mar-21.
//

#ifndef EX5_CPP_AUTOTEST_UTILS_H
#define EX5_CPP_AUTOTEST_UTILS_H

#include "Matrix.h"
#include "Activation.h"
#include "Dense.h"
#include "MlpNetwork.h"
#include <iostream>
#include <fstream>
#include <functional>
#include <type_traits>

template<typename T>
struct function_traits;

template<class F>
struct function_traits;

// function pointer
template<class R, class... Args>
struct function_traits<R(*)(Args...)> : public function_traits<R(Args...)> {
};

template<class R, class... Args>
struct function_traits<R(Args...)> {
    using return_type = R;

    static constexpr std::size_t arity = sizeof...(Args);

    template<std::size_t N>
    struct argument {
        static_assert(N < arity, "error: invalid parameter index.");
        using type = typename std::tuple_element<N, std::tuple<Args...>>::type;
    };
};

// member function pointer
template<class C, class R, class... Args>
struct function_traits<R(C::*)(Args...)> : public function_traits<R(C &, Args...)> {
};

// const member function pointer
template<class C, class R, class... Args>
struct function_traits<R(C::*)(Args...) const> : public function_traits<R(C &, Args...)> {
};

// member object pointer
template<class C, class R>
struct function_traits<R(C::*)> : public function_traits<R(C &)> {
};

bool checkSameAddress(const Matrix &lhs, const Matrix &rhs)
{
    return &lhs == &rhs;
}

Matrix get_ordered_matrix(int rows, int cols)
{
    Matrix A = Matrix(rows, cols);
    for(int i = 0; i < A.get_rows(); ++i)
    {
        for(int j = 0; j < A.get_cols(); ++j)
        {
            A[i * A.get_cols() + j] = i * A.get_cols() + j;
        }
    }
    return A;
}

#endif //EX5_CPP_AUTOTEST_UTILS_H
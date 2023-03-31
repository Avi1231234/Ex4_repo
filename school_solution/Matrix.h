
#include <iostream>
#include <cmath>

#define MEM_ERR "ERROR: No memory available for matrix"
#define DIM_ERR "ERROR: Matrices do not match dimensions"
#define BAD_DIM "ERROR: bad dimensions"
#define INDEX_ERR "ERROR: index out of boundaries"
#define STREAM_ERR "ERROR: Problem with input stream"
#define SIZE_ERR "ERROR: input stream size does not match matrix"

#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
 public:
    /**
     * @struct Dims
     * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
     */
    struct dims {
        int rows, cols;
    };

 private:
    dims _dims;
    //long size;
    float *_matrix;

    friend void swap(Matrix &a, Matrix &b);

 public:
    // constructors and destructor
    Matrix(int rows, int cols);
    Matrix();
    Matrix(const Matrix &m);
    ~Matrix();

    // methods
    int get_rows() const;
    int get_cols() const;
    Matrix &transpose();
    Matrix &vectorize();
    void plain_print() const;
    Matrix dot(const Matrix &m) const;
    float sum() const;
    float norm() const;
    int argmax() const;

    // operators
    Matrix operator+(const Matrix &m) const;
    Matrix &operator=(Matrix m);
    Matrix operator*(const Matrix &m) const;
    Matrix operator*(const float &scalar) const;
    Matrix &operator+=(const Matrix &m);
    const float &operator()(int i, int j) const;
    const float &operator[](int i) const;

    // [] and () overloading
    float &operator()(int i, int j);
    float &operator[](int i);

    // >> and <<
    friend std::ostream &operator<<(std::ostream &os, const Matrix &m);
    friend std::istream &operator>>(std::istream &is, Matrix &m);

    Matrix rref() const;

};

Matrix operator*(const float &scalar, const Matrix &matrix);

#endif //MATRIX_H
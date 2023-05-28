
#include "Matrix.h"

//#define EPSILON 0.1

#define FULL 0.8
#define HEAVY 0.6
#define MEDIUM 0.4
#define LIGHT 0.2

#define SIZE (_dims.rows * _dims.cols)
#define COMP_DIMS if (_dims != m._dims) { throw std::domain_error(DIM_ERR); }

// ----------------------------CONSTRUCTORS----------------------------------

Matrix::Matrix(int rows, int cols) noexcept(false): _dims{rows, cols}
{
    if(rows <= 0 || cols <= 0)
    {
        throw std::domain_error(BAD_DIM);
    }
    _matrix = new float[rows * cols]();
}

Matrix::Matrix() : Matrix(1, 1)
{}

Matrix::Matrix(const Matrix &m) : Matrix(m.get_rows(), m.get_cols())
{
    std::copy(m._matrix, m._matrix + SIZE, _matrix);
}

Matrix::~Matrix()
{
    delete[] _matrix;
}


// ----------------------------METHODS---------------------------------------

bool operator!=(const Matrix::dims &a, const Matrix::dims &b)
{
    return a.rows != b.rows || a.cols != b.cols;
}

int Matrix::get_rows() const
{
    return _dims.rows;
}

int Matrix::get_cols() const
{
    return _dims.cols;
}

Matrix &Matrix::transpose() noexcept(false)
{
    // create a new matrix
    auto *new_matrix = new float[SIZE];

    // transpose the new matrix
    for(int i = 0; i < get_rows(); i++)
    {
        for(int j = 0; j < get_cols(); j++)
        {
            new_matrix[j * get_rows() + i] = _matrix[i * get_cols() + j];
        }
    }

    // replace the old matrix
    delete[] _matrix;
    _matrix = new_matrix;

    // flip dimensions
    _dims = {_dims.cols, _dims.rows};

    return *this;
}

Matrix &Matrix::vectorize()
{
    _dims.rows *= get_cols();
    _dims.cols = 1;

    return *this;
}

void Matrix::plain_print() const
{
    for(int i = 0; i < get_rows(); i++)
    {
        for(int j = 0; j < get_cols(); j++)
        {
            std::cout << _matrix[i * get_cols() + j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix Matrix::dot(const Matrix &m) const
{
    // check dimensions are identical
    COMP_DIMS

    Matrix dot_product(*this);
    for(int i = 0; i < SIZE; i++)
    {
        dot_product[i] *= m[i];
    }

    return dot_product;
}

float Matrix::sum() const
{
    float sum = 0.0;
    for(int i = 0; i < SIZE; i++)
    {
        sum += _matrix[i];
    }
    return sum;
}

float Matrix::norm() const
{
    return std::sqrt(dot(*this).sum());
}

int Matrix::argmax() const
{
    int argmax = 0;
    for(int i = 1; i < SIZE; ++i)
    {
        if((*this)[i] > (*this)[argmax])
        {
            argmax = i;
        }
    }
    return argmax;
}

void row_switcher(Matrix & mat,int row1, int row2) {
    /**
     * Exchanges row1 with row2 in matrix mat
     */
    float tmp;
    for(int i = 0;i<mat.get_cols();i++){
        tmp = mat(row1,i);
        mat(row1,i) = mat(row2,i);
        mat(row2,i) = tmp;
    }
}

void multiply_row_by_scalar(Matrix & mat, int row, float scalar){
    /**
     * Multiplies each element in row in matrix mat by a scalar
     */
    for (int i = 0;i<mat.get_cols();i++){
        mat(row,i)*=scalar;
    }
}

void subtract_rows(Matrix & mat, int row1, int row2,float scalar){
    /**
     * Element-wise subtraction of row2 from row1, and conducts element-wise multiplication of row2 by a scalar
     *  if necessrary
     */
    for (int i = 0;i<mat.get_cols();i++){
        mat(row1,i)-=(mat(row2,i)*scalar);
    }
}

void reduce_col(Matrix & mat, int row,int shift){
    /**
     * Reduces an entire column in matrix mat. We multiply row by a scalar to make the first non-zero element 1,
     *  and then we subtract this row from all the others. Reduces all the other numbers in the column to zeroes.
     */
    multiply_row_by_scalar(mat, row,1/mat(row,row+shift));
    for (int i = 0; i < mat.get_rows(); ++i) {
        if(i!=row){
            subtract_rows(mat,i,row,mat(i,row+shift));
        }
    }
}

Matrix Matrix::rref() const{
    /**
     * Algorithm for finding and returning the RREF matrix. Leaves the original matrix untouched
     */
    Matrix mat_copy(*this);
    bool is_zero_col = true; // A marker for telling whether a column is a zero column
    int shift  = 0; // Takes into account the shift necessary if the matrix has a column of zeroes

    for (int i = 0; i < mat_copy.get_rows() && i+shift < mat_copy.get_cols(); ++i) {

        if((mat_copy)(i, i + shift) == 0){
            for (int j = i+1; j < mat_copy.get_rows(); ++j) {
                if((mat_copy)(j, i + shift) != 0){
                    row_switcher(mat_copy,i,j);
                    reduce_col(mat_copy, i, shift);
                    is_zero_col = false;
                }
            }

            if(is_zero_col){  // This control block handles the shift mechanism
                shift++; i--;
            } else{
                is_zero_col=true;
            }

        } else {
            reduce_col(mat_copy, i, shift);
        }
    }
    return mat_copy;
}

// ----------------------------OPERATORS-------------------------------------

Matrix Matrix::operator+(const Matrix &m) const
{
    // check dimensions are identical
    COMP_DIMS

    Matrix sum(*this);
    return sum += m;
}

void swap(Matrix &a, Matrix &b)
{
    std::swap(a._dims, b._dims);
    std::swap(a._matrix, b._matrix);
}

Matrix &Matrix::operator=(Matrix m)
{
    if(this == &m)
    {
        return *this;
    }

    swap(m, *this);

    return *this;
}

Matrix Matrix::operator*(const Matrix &m) const noexcept(false)
{
    // check dimensions are identical
    if(get_cols() != m.get_rows())
    {
        throw std::domain_error(DIM_ERR);
    }

    Matrix mult(get_rows(), m.get_cols());

    for(int i = 0; i < mult.get_rows(); i++)
    {
        for(int j = 0; j < mult.get_cols(); j++)
        {
            for(int k = 0; k < get_cols(); k++)
            {
                mult(i, j) += (*this)(i, k) * m(k, j);
            }
        }
    }

    return mult;
}

Matrix Matrix::operator*(const float &scalar) const
{
    Matrix mult(*this);
    for(int i = 0; i < SIZE; i++)
    {
        mult._matrix[i] *= scalar;
    }

    return mult;
}

Matrix operator*(const float &scalar, const Matrix &matrix)
{
    return matrix * scalar;
}

Matrix &Matrix::operator+=(const Matrix &m)
{
    // check dimensions are identical
    COMP_DIMS

    for(int i = 0; i < SIZE; i++)
    {
        _matrix[i] += m[i];
    }

    return *this;
}

const float &Matrix::operator()(int i, int j) const noexcept(false)
{
    if(i >= get_rows() || j >= get_cols() || i < 0 || j < 0)
    {
        throw std::out_of_range(INDEX_ERR);
    }
    return _matrix[i * get_cols() + j];
}

float &Matrix::operator()(int i, int j) noexcept(false)
{
    if(i >= get_rows() || j >= get_cols() || i < 0 || j < 0)
    {
        throw std::out_of_range(INDEX_ERR);
    }
    return _matrix[i * get_cols() + j];
}

const float &Matrix::operator[](int i) const noexcept(false)
{
    if(i >= SIZE || i < 0)
    {
        throw std::out_of_range(INDEX_ERR);
    }

    return _matrix[i];
}

float &Matrix::operator[](int i) noexcept(false)
{
    if(i >= SIZE || i < 0)
    {
        throw std::out_of_range(INDEX_ERR);
    }

    return _matrix[i];
}

std::ostream &operator<<(std::ostream &os, const Matrix &m)
{
    for(int i = 0; i < m.get_rows(); ++i)
    {
        for(int j = 0; j < m.get_cols(); ++j)
        {
//      os << ((m (i, j) > EPSILON) ? "**" : "  ");
            if(m(i, j) > FULL)
            {
                os << "██";
            }
            else if(m(i, j) > HEAVY)
            {
                os << "▓▓";
            }
            else if(m(i, j) > MEDIUM)
            {
                os << "▒▒";
            }
            else if(m(i, j) > LIGHT)
            {
                os << "░░";
            }
            else
            {
                os << "  ";
            }
        }
        os << std::endl;
    }
    return os;
}

std::istream &operator>>(std::istream &is, Matrix &m) noexcept(false)
{
    if(!is)
    {
        throw std::runtime_error(STREAM_ERR);
    }
    if(!is.read((char *) m._matrix,
                m.get_cols() * m.get_rows() * ((long) sizeof(float))))
    {
        throw std::runtime_error(SIZE_ERR);
    }
    return is;
}







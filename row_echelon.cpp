//
// Created by Jake Korman on 3/20/23.
//

void row_switcher(Matrix & mat,int row1, int row2) {
    float tmp = 0.0;
    for(int i = 0;i<mat.get_cols();i++){
        tmp = mat(row1,i);
        mat(row1,i) = mat(row2,i);
        mat(row2,i) = tmp;
    }
}
void multiply_row_by_scalar(Matrix & mat, int row, float scalar){
    for (int i = 0;i<mat.get_cols();i++){
        mat(row,i)*=scalar;
    }
}
void subtract_rows(Matrix & mat, int row1, int row2,float scalar){
    // subtract row2 from row1, and multiply by a scalar if needed
    for (int i = 0;i<mat.get_cols();i++){
        mat(row1,i)-=(mat(row2,i)*scalar);
    }
}


void reduce_col(Matrix & mat, int row){
    multiply_row_by_scalar(mat, row,1/mat(row,row));
    for (int i = 0; i < mat.get_rows(); ++i) {
        if(i!=row){
            subtract_rows(mat,i,row,mat(i,row));
        }
    }
}
Matrix Matrix::row_echelon_form() const{

    Matrix mat_copy(*this);
    for (int i = 0; i < mat_copy.get_rows(); ++i) {
        if((mat_copy)(i,i)==0){
            for (int j = i+1; j < mat_copy.get_rows(); ++j) {
                if((mat_copy)(j,i)!=0){
                    row_switcher(mat_copy,i,j);
                    reduce_col(mat_copy,i);
                }
            }
        } else {
            reduce_col(mat_copy,i);
        }
    }
    return mat_copy;
}
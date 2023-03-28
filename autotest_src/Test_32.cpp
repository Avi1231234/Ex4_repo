//
// Created by Jake Korman on 3/27/23.
//

#include "autotest_utils.h"



int counter = 1;



int test_reduced_matrix(float* arr, float* sol, int rows, int cols)
{
    // student's solution
    Matrix M(rows, cols);
    fill_matrix(M, arr);
    M.plain_print();
    Matrix R = M.reduced_row_echelon_form();

    // our solution
    Matrix Jake(rows, cols);
    fill_matrix(Jake, sol);

    return check_equal(Jake, R);
}

int main(){


    int rows, cols;

    //Zero Matrix
    float arr1[20]={0};
    float sol1[20]={0};
    rows = 5; cols = 4;
    test_reduced_matrix(arr1, sol1, rows, cols);



    // Single row ordered ascending
    float arr2[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    float sol2[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    rows = 1; cols = 10;
    test_reduced_matrix(arr2, sol2, rows, cols);



    // Single row ordered descending
    float arr3[10] = {9,8,7,6,5,4,3,2,1,0};
    float sol3[10] = {1,0.8888888,
                      0.7777777,
                      0.6666666,
                      0.5555555,
                      0.4444444,
                      0.3333333,
                      0.2222222,
                      0.1111111,
                      0};
    rows = 1; cols = 10;
    test_reduced_matrix(arr3, sol3, rows, cols);



    // Single row zeroes
    float arr4[10] = {0};
    float sol4[10] = {0};
    rows = 1; cols = 10;
    test_reduced_matrix(arr4, sol4, rows, cols);



    // Single col ordered ascending
    float arr5[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    float sol5[10] = {1,0,0,0,0,0,0,0,0,0};
    rows = 10; cols = 1;
    test_reduced_matrix(arr5, sol5, rows, cols);



    // Single col ordered descending
    float arr6[10] = {9,8,7,6,5,4,3,2,1,0};
    float sol6[10] = {1,0,0,0,0,0,0,0,0,0};
    rows = 10; cols = 1;
    test_reduced_matrix(arr6, sol6, rows, cols);



    // Single col zeroes
    float arr7[10] = {0};
    float sol7[10] = {0};
    rows = 10; cols = 1;
    test_reduced_matrix(arr7, sol7, rows, cols);



    //Square Matrix, linearly independent rows
    float arr8[4] = {4,1,2,4};
    float sol8[4] = {1,0,0,1};
    rows = 2; cols = 2;
    test_reduced_matrix(arr8, sol8, rows, cols);



    //Square Matrix, linearly dependent rows
    float arr9[4] = {4,8,2,4};
    float sol9[4] = {1,2,0,0};
    rows = 2; cols = 2;
    test_reduced_matrix(arr9, sol9, rows, cols);



    //Identity Matrix
    float arr10[9] = {1,0,0,0,1,0,0,0,1};
    float sol10[9] = {1,0,0,0,1,0,0,0,1};
    rows = 3; cols = 3;
    test_reduced_matrix(arr10, sol10, rows, cols);



    //Single Element Non-zero
    float arr11[1] = {81};
    float sol11[1] = {1};
    rows = 1; cols = 1;
    test_reduced_matrix(arr11, sol11, rows, cols);



    //Single Element Zero
    float arr12[1] = {0};
    float sol12[1] = {0};
    rows = 1; cols = 1;
    test_reduced_matrix(arr12, sol12, rows, cols);



    // Jordan Matrix for the hell of it
    float arr13[16] = {2,1,0,0,0,2,1,0,0,0,2,0,0,0,0,2};
    float sol13[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
    rows = 4; cols = 4;
    test_reduced_matrix(arr13, sol13, rows, cols);



    // Complicated Matrix
    float arr14[120] = {0.43043067, 0.98556212, 0.41052902, 0.02060228, 0.69532313,
                        0.58112064, 0.08955321, 0.36070686, 0.98405485, 0.47528062,
                        0.73851902, 0.26787286,
                        0.927157  , 0.7718693 , 0.30257489, 0.20426221, 0.67830904,
                        0.39184645, 0.30479197, 0.79821448, 0.27202544, 0.65419653,
                        0.06802244, 0.52810033,
                        0.68644927, 0.37009835, 0.07489383, 0.79794132, 0.06611287,
                        0.31767006, 0.12780513, 0.42392337, 0.09345321, 0.46243004,
                        0.38659944, 0.87059653,
                        0.23805484, 0.75010214, 0.05071682, 0.27862569, 0.05999373,
                        0.27018408, 0.71517294, 0.96427821, 0.36517332, 0.76295184,
                        0.53017178, 0.42426219,
                        0.58703649, 0.6820975 , 0.79623008, 0.19522473, 0.07485183,
                        0.49360743, 0.76666691, 0.71017115, 0.57539561, 0.34491764,
                        0.04449134, 0.9875201 ,
                        0.1487997 , 0.96117575, 0.00888895, 0.4936796 , 0.26640981,
                        0.17017498, 0.24971791, 0.36341999, 0.89439252, 0.62790187,
                        0.45692038, 0.58384648,
                        0.14822124, 0.06542466, 0.8810753 , 0.93257023, 0.80743868,
                        0.94771972, 0.66353708, 0.45046403, 0.53098679, 0.55849453,
                        0.20517981, 0.77769263,
                        0.01145568, 0.38537123, 0.79763879, 0.77897566, 0.97168038,
                        0.83231823, 0.96261606, 0.20918644, 0.75034137, 0.5013981 ,
                        0.9040011 , 0.30213989,
                        0.69326346, 0.87770436, 0.42662742, 0.42998685, 0.54672699,
                        0.98325954, 0.17270841, 0.43536178, 0.61430951, 0.99895556,
                        0.75806667, 0.85303834,
                        0.95515422, 0.18638944, 0.90318442, 0.20961969, 0.46357448,
                        0.64752084, 0.6489437 , 0.54199912, 0.47448604, 0.25563738,
                        0.88856427, 0.37160456};
    float sol14[120] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0,    1.41404147756252, -0.296909609216937,
                        0, 1, 0, 0, 0, 0, 0, 0, 0, 0,   -1.08888357929624,  0.915460063642015,
                        0, 0, 1, 0, 0, 0, 0, 0, 0, 0,   -4.11245594459195,   2.07171736770467,
                        0, 0, 0, 1, 0, 0, 0, 0, 0, 0,  -0.447364621354182,  0.869403068923564,
                        0, 0, 0, 0, 1, 0, 0, 0, 0, 0, -0.0448473677319255, -0.667324517380702,
                        0, 0, 0, 0, 0, 1, 0, 0, 0, 0,    3.05403044259285, -0.846499963044515,
                        0, 0, 0, 0, 0, 0, 1, 0, 0, 0,    1.97754172589026, -0.906015453397383,
                        0, 0, 0, 0, 0, 0, 0, 1, 0, 0,  -0.323187591983952, 0.0509710315079637,
                        0, 0, 0, 0, 0, 0, 0, 0, 1, 0,    1.92806788962969, -0.741431886912464,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 1,   -1.68508164922566,  0.785436449981956};
    rows = 10; cols = 12;
    test_reduced_matrix(arr14, sol14, rows, cols);


     //Rectangle Matrix, linearly independent rows
     float arr15[6] = {4,1,2,4,7,11};
     float sol15[6] = {1,0,0.125,0,1,1.5};
     rows = 2; cols = 3;
     test_reduced_matrix(arr15, sol15, rows, cols);



     //Rectangle Matrix, linearly dependent rows
     float arr16[6] = {4,2,8,4,16,8};
     float sol16[6] = {1,0.5,0,0,0,0};
     rows = 3; cols = 2;
     test_reduced_matrix(arr16, sol16, rows, cols);



    // One empty column, rows<cols
    float arr_17[12] = {2,0,2,6,1,0,1,7,3,0,2,4};
    float sol_17[12] = {1,0,0,0,0,0,1,0,0,0,0,1};
    rows = 3; cols = 4;
    test_reduced_matrix(arr_17, sol_17, rows, cols);


    // One empty column, rows>cols
    float arr_18[12] = {2,0,2,1,0,1,3,0,2,1,0,3};
    float sol_18[12] = {1,0,0,0,0,1,0,0,0,0,0,0};
    rows = 4; cols = 3;
    test_reduced_matrix(arr_18, sol_18, rows, cols);


    // Two empty columns, rows<cols
    float arr_19[18] = {2,0,2,4,0,4,0,0,1,3,0,5,3,0,2,4,0,5};
    float sol_19[18] = {1,0,0,0,0,1,0,0,1,0,0,-7,0,0,0,1,0,4};
    rows = 3; cols = 6;
    test_reduced_matrix(arr_19, sol_19, rows, cols);


    // Two empty columns, rows>cols
    float arr_20[35] = {0,0,2,4,0,0,0,1,3,0,0,0,7,5,0,0,5,0,0,0,0,6,0,7,0,0,4,0,8,0,0,2,0,9,0};
    float sol_20[35] = {0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    rows = 7; cols = 5;
    test_reduced_matrix(arr_20, sol_20, rows, cols);


    return EXIT_SUCCESS;
}
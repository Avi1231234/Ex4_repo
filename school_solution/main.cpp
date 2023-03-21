#include <fstream>

#include "Matrix.h"
#include "Activation.h"
#include "Dense.h"
#include "MlpNetwork.h"

#define QUIT "q"
#define INSERT_IMAGE_PATH "Please insert image path:"
#define ERROR_INAVLID_PARAMETER "Error: invalid Parameters file for layer: "
#define ERROR_INVALID_INPUT "Error: Failed to retrieve input. Exiting.."
#define ERROR_INVALID_IMG "Error: invalid image path or size: "
#define USAGE_MSG "Usage:\n" \
                  "\t./mlpnetwork w1 w2 w3 w4 b1 b2 b3 b4\n" \
                  "\twi - the i'th layer's weights\n" \
                  "\tbi - the i'th layer's biases"
#define USGAE_ERROR "wrong number of arguments"
#define ARGS_START_IDX 1
#define ARGS_COUNT (ARGS_START_IDX + (MLP_SIZE * 2))
#define WEIGHTS_START_IDX ARGS_START_IDX
#define BIAS_START_IDX (ARGS_START_IDX + MLP_SIZE)
#define EPSILON 0.001
/**
 * Given a binary file path and a matrix,
 * reads the content of the file into the matrix.
 * file must match matrix in size in order to read successfully.
 * @param filePath - path of the binary file to read
 * @param mat -  matrix to read the file into.
 * @return boolean status
 *          true - success
 *          false - failure
 */
bool readFileToMatrix(const std::string &filePath, Matrix &mat)
{
    std::ifstream is(filePath, std::ios::in | std::ios::binary);
    if(!is.is_open())
    {
        return false;
    }

    is >> mat;

    is.close();
    return true;
}

/**
 * Loads MLP parameters from weights & biases paths
 * to Weights[] and Biases[].
 * Throws an exception upon failures.
 * @param paths array of programs arguments, expected to be mlp parameters
 *        path.
 * @param weights array of matrix, weigths[i] is the i'th layer weights matrix
 * @param biases array of matrix, biases[i] is the i'th layer bias matrix
 *          (which is actually a vector)
 *  @throw std::invalid_argument in case of problem with a certain argument
 */
void loadParameters(char *paths[ARGS_COUNT], Matrix weights[MLP_SIZE],
                    Matrix biases[MLP_SIZE]) noexcept(false)
{
    for(int i = 0; i < MLP_SIZE; i++)
    {
        weights[i] = Matrix(weights_dims[i].rows, weights_dims[i].cols);
        biases[i] = Matrix(bias_dims[i].rows, bias_dims[i].cols);

        std::string weightsPath(paths[WEIGHTS_START_IDX + i]);
        std::string biasPath(paths[BIAS_START_IDX + i]);

        if(!(readFileToMatrix(weightsPath, weights[i]) &&
             readFileToMatrix(biasPath, biases[i])))
        {
            auto msg = ERROR_INAVLID_PARAMETER + std::to_string(i + 1);
            throw std::invalid_argument(msg);
        }

    }
}

/**
 * This programs Command line interface for the mlp network.
 * Looping on: {
 *                  Retrieve user input
 *                  Feed input to mlpNetwork
 *                  print image & netowrk prediction
 *             }
 * Throws an exception on fatal errors: unable to read user input path.
 * @param mlp MlpNetwork to use in order to predict img.
 * @throw std::invalid_argument in case of problem with the user input path
 */
void mlpCli(MlpNetwork &mlp) noexcept(false)
{
    Matrix img(img_dims.rows, img_dims.cols);
    std::string imgPath;

    std::cout << INSERT_IMAGE_PATH << std::endl;
    std::cin >> imgPath;
    if(!std::cin.good())
    {
        throw std::invalid_argument(ERROR_INVALID_INPUT);
    }

    while(imgPath != QUIT)
    {
        if(readFileToMatrix(imgPath, img))
        {
            Matrix imgVec = img;
            digit output = mlp(imgVec.vectorize());
            std::cout << "Image processed:" << std::endl
                      << img << std::endl;
            std::cout << "Mlp result: " << output.value <<
                      " at probability: " << output.probability << std::endl;
        }
        else
        {
            throw std::invalid_argument(ERROR_INVALID_IMG + imgPath);
        }

        std::cout << INSERT_IMAGE_PATH << std::endl;
        std::cin >> imgPath;
        if(!std::cin.good())
        {
            throw std::invalid_argument(ERROR_INVALID_INPUT);
        }
    }
}


//TODO delete
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

bool float_compare(float a, float b)
{
    return std::abs(a - b) < EPSILON;
}

int check_equal(const Matrix& A, const Matrix& B)
{
    // checking correct dimensions
    if(A.get_rows() != B.get_rows() || A.get_cols() != B.get_cols())
    {
        std::cerr << "Matrix dimensions are not correct." << std::endl;
        return 1;
    }

    // checking correct new values
    for(int i = 0; i < B.get_cols() * B.get_rows(); i++)
    {
        if(! float_compare(A[i], B[i]))
        {
            std::cerr << "Values are not the same" << std::endl;
            return 1;
        }
    }

    return 0;
}

void fill_matrix(Matrix& M, const float* nums)
{
    for(int i = 0; i < M.get_rows(); ++i)
    {
        for(int j = 0; j < M.get_cols(); ++j)
        {
            M[i * M.get_cols() + j] = nums[i * M.get_cols() + j];
        }
    }
}

int test_reduced_matrix(float* arr, float* sol, int rows, int cols)
{
    // student's solution
    Matrix M(rows, cols);
    fill_matrix(M, arr);
    Matrix R = M.reduced_row_echelon_form();

    // our solution
    Matrix Jake(rows, cols);
    fill_matrix(Jake, sol);

    return check_equal(Jake, R);
}

/**
 * Program's main
 * @param argc count of args
 * @param argv args values
 * @return program exit status code
 */
int main(int argc, char **argv) {
//    if(argc != ARGS_COUNT)
//    {
//        std::cout << USAGE_MSG << std::endl;
//        return EXIT_FAILURE;
//    }
//
//
//    Matrix weights[MLP_SIZE];
//    Matrix biases[MLP_SIZE];
//
//    try
//    {
//        loadParameters(argv, weights, biases);
//
//    }
//    catch(const std::invalid_argument &invalidArgument)
//    {
//        std::cerr << invalidArgument.what() << std::endl;
//        return EXIT_FAILURE;
//    }
//
//    MlpNetwork mlp(weights, biases);
//
//    try
//    {
//        mlpCli(mlp);
//    }
//
//    catch(const std::invalid_argument &invalidArgument)
//    {
//        std::cerr << invalidArgument.what() << std::endl;
//        return EXIT_FAILURE;
//    }
    //Random matrix
    float arr1[] = {2, 4, 4, 0, 3, 0, 1, 2, 4, 0, 5, 1};
    float sol1[] = {1, 0, 0, 0.818182, 0, 1, 0, 0.0454545, 0, 0, 1, -0.454545};
    int rows = 3,cols=4;
    test_reduced_matrix(arr1, sol1, rows, cols);

    //Zero Matrix
    float arr2[20]={0};
    float sol2[20]={0};
    rows = 5; cols = 4;
    test_reduced_matrix(arr2, sol2, rows, cols);

    // Single row ordered ascending
    float arr3[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    float sol3[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    rows = 1; cols = 10;
    test_reduced_matrix(arr3, sol3, rows, cols);

    // Single row ordered descending
    float arr4[10] = {9,8,7,6,54,4,3,2,1,0};
    float sol4[10] = {1,0.8888888,
                  0.7777777,
                  0.6666666,
                  0.5555555,
                  0.4444444,
                  0.3333333,
                  0.2222222,
                  0.1111111,
                  0};
    rows = 1; cols = 10;
    test_reduced_matrix(arr4, sol4, rows, cols);

    // Single row zeroes
    float arr15[10] = {0};
    float sol15[10] = {0};
    rows = 1; cols = 10;
    test_reduced_matrix(arr15, sol15, rows, cols);

    // Single col ordered ascending
    float arr16[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    float sol16[10] = {1,0,0,0,0,0,0,0,0,0};
    rows = 10; cols = 1;
    test_reduced_matrix(arr16, sol16, rows, cols);

    // Single col ordered descending
    float arr17[10] = {9,8,7,6,5,4,3,2,1,0};
    float sol17[10] = {1,0,0,0,0,0,0,0,0,0};
    rows = 10; cols = 1;
    test_reduced_matrix(arr17, sol17, rows, cols);

    // Single col zeroes
    float arr5[10] = {0};
    float sol5[10] = {0};
    rows = 10; cols = 1;
    test_reduced_matrix(arr5, sol5, rows, cols);

    //Square Matrix, linearly independent rows
    float arr6[4] = {4,1,2,4};
    float sol6[4] = {1,0,0,1};
    rows = 2; cols = 2;
    test_reduced_matrix(arr6, sol6, rows, cols);

    //Square Matrix, linearly dependent rows
    float arr7[4] = {4,8,2,4};
    float sol7[4] = {1,2,0,0};
    rows = 2; cols = 2;
    test_reduced_matrix(arr7, sol7, rows, cols);

    //Identity Matrix
    float arr8[9] = {1,0,0,0,1,0,0,0,1};
    float sol8[9] = {1,0,0,0,1,0,0,0,1};
    rows = 3; cols = 3;
    test_reduced_matrix(arr8, sol8, rows, cols);

    //Rectangle Matrix, linearly independent rows
    float arr9[6] = {4,1,2,4,7,11};
    float sol9[6] = {1,0,0.125,0,1,1.5};
    rows = 2; cols = 3;
    test_reduced_matrix(arr9, so9, rows, cols);

    //Rectangle Matrix, linearly dependent rows
    float arr10[6] = {4,2,8,4,16,8};
    float sol10[6] = {1,0.5,0,0,0,0};
    rows = 3; cols = 2;
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

    return EXIT_SUCCESS;
}
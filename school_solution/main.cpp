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
    Matrix R = M.row_echelon_form();

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
    float arr1[12] = {2, 4, 4, 0, 3, 0, 1, 2, 4, 0, 5, 1};
    float sol1[12] = {1, 0, 0, 0.818182, 0, 1, 0, 0.0454545, 0, 0, 1, -0.454545};
    test_reduced_matrix(arr1, sol1, 3, 4);

    return EXIT_SUCCESS;
}
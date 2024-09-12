#include "./matrix.h"
#include <x86intrin.h>
#include <time.h>
#include "Eigen/Eigen/Dense"
void parseArgs(int argc, char *argv[], std::string &testmode);
void init();
void vectorClassTest();
void elementWiseTest();
void assemblyTest();
void eigenTest();
Matrix_t m1Size, m2Size;
float *matrixF1;
float *matrixF2;
float *matrixF3;
int *matrixI1;
int *matrixI2;
int *matrixI3;
std::string formatWithCommas(uint64_t value);

int main(int argc, char *argv[])
{
    srand(time(0));
    // Argument processing
    std::string testmode = "";
    parseArgs(argc, argv, testmode);
    init();

    if (testmode == "vc")
    {
        vectorClassTest();
    }
    else if (testmode == "ed")
    {
        eigenTest();
    }
    else
    {
        elementWiseTest();
    }
    std::cout << "==========Done============" << std::endl;
    free(matrixI1);
    free(matrixI2);
    free(matrixI3);
    free(matrixF1);
    free(matrixF2);
    free(matrixF3);
    return 0;
}

void parseArgs(int argc, char *argv[], std::string &testmode)
{
    bool m1Set = false;
    bool m2Set = false;
    // Iterate over the arguments
    for (int i = 0; i < argc; i++)
    {
        char *value = NULL;
        // Compare the strings to see which argument we are setting
        if ((strcmp(argv[i], "-m1") == 0) && (i + 1 < argc))
        {
            value = argv[i + 1];
            value = strtok(value, "x");
            if (value == NULL)
            {
                printf("Invalid input. Input should be in the (RowsxColumns) format\n");
                exit(-1);
            }
            m1Size.rows = atoi(value);
            m1Size.columns = atoi(strtok(NULL, "x"));
            m1Set = true;
            if (m2Set)
            {
                if (m1Size.columns != m2Size.rows)
                {
                    printf("Invalid matrix size for multiplication. Matrix 1's columns should be equal to Matrix 2's rows.\n");
                    exit(-2);
                }
            }
        }
        else if ((strcmp(argv[i], "-m2") == 0) && (i + 1 < argc))
        {
            value = argv[i + 1];
            value = strtok(value, "x");
            if (value == NULL)
            {
                printf("Invalid input. Input should be in the (RowsxColumns) format\n");
                exit(-1);
            }
            m2Size.rows = atoi(value);
            m2Size.columns = atoi(strtok(NULL, "x"));
            m2Set = true;
            if (m1Set)
            {
                if (m1Size.columns != m2Size.rows)
                {
                    printf("Invalid matrix size for multiplication. Matrix 1's columns should be equal to Matrix 2's rows.\n");
                    exit(-2);
                }
            }
        }
        else if ((strcmp(argv[i], "-tm") == 0) && (i + 1 < argc))
        {
            testmode = argv[i + 1];
        }
    }
    if ((!m1Set && !m2Set))
    {
        printf("Try running the program again with -help for commands\n");
        exit(0);
    }
}
void init()
{
    matrixF1 = makeFloatMatrix(m1Size);
    matrixF2 = makeFloatMatrix(m2Size);
    matrixI1 = makeIntMatrix(m1Size);
    matrixI2 = makeIntMatrix(m2Size);
    randomizeMatrix(matrixF1, m1Size);
    randomizeMatrix(matrixF2, m2Size);
    randomizeMatrix(matrixI1, m1Size);
    randomizeMatrix(matrixI2, m2Size);
}

void vectorClassTest()
{
    uint64_t start, end;
    std::cout << std::endl;
    std::cout << "==========Vector Class Test============" << std::endl;
    std::cout << "==========Float Test============" << std::endl;
    // Time the function
    // Get current cycle count
    start = __rdtsc();
    matrixF3 = multVec(matrixF1, matrixF2, m1Size.rows, m1Size.columns, m2Size.columns);
    end = __rdtsc();
    std::cout << "Finishing Time: " << formatWithCommas(end - start) << " cycles" << std::endl;

    std::cout << "==========Int Test============" << std::endl;
    // Time the function
    // Get current cycle count
    start = __rdtsc();
    matrixI3 = multVec(matrixI1, matrixI2, m1Size.rows, m1Size.columns, m2Size.columns);
    end = __rdtsc();
    std::cout << "Finishing Time: " << formatWithCommas(end - start) << " cycles" << std::endl;
}
void elementWiseTest()
{
    uint64_t start, end;
    std::cout << std::endl;
    std::cout << "==========Element-wise Test============" << std::endl;
    std::cout << "==========Float Test============" << std::endl;
    // Time the function
    // Get current cycle count
    start = __rdtsc();
    matrixF3 = mult(matrixF1, matrixF2, m1Size.rows, m1Size.columns, m2Size.columns);
    end = __rdtsc();
    std::cout << "Finishing Time: " << formatWithCommas(end - start) << " cycles" << std::endl;
    std::cout << "==========Int Test============" << std::endl;

    // Time the function
    // Get current cycle count
    start = __rdtsc();
    matrixI3 = mult(matrixI1, matrixI2, m1Size.rows, m1Size.columns, m2Size.columns);
    end = __rdtsc();
    std::cout << "Finishing Time: " << formatWithCommas(end - start) << " cycles" << std::endl;
}
void eigenTest()
{
    // Declare variables to store the start and end times.
    uint64_t start, end;
    // Print some output to console.
    std::cout << std::endl;
    std::cout << "==========Eigen Class Test============" << std::endl;
    std::cout << "==========Float Test============" << std::endl;
    // Create Eigen float matrices by mapping from existing float arrays (matrixF1 and matrixF2).
    // The Eigen::Map class is a utility which allows you to treat chunks of memory as Eigen objects.
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> mat1f(matrixF1, m1Size.rows, m1Size.columns);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> mat2f(matrixF2, m2Size.rows, m2Size.columns);

    // Record the start time
    start = __rdtsc();
    // Perform matrix multiplication with the two float matrices and store the result in a new matrix.
    Eigen::MatrixXf m3f = mat1f * mat2f;
    // Record the end time
    end = __rdtsc();
    std::cout << "Finishing Time: " << formatWithCommas(end - start) << " cycles" << std::endl;
    std::cout << "==========Int Test============" << std::endl;

    // Do the same as above but for int arrays (matrixI1 and matrixI2)
    Eigen::Map<Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> mat1i(matrixI1, m1Size.rows, m1Size.columns);
    Eigen::Map<Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> mat2i(matrixI2, m2Size.rows, m2Size.columns);

    // Record the start time
    start = __rdtsc();
    // Perform matrix multiplication with the two int matrices and store the result in a new matrix.
    Eigen::MatrixXi m3i = mat1i * mat2i;
    // Record the end time
    end = __rdtsc();
    std::cout << "Finishing Time: " << formatWithCommas(end - start) << " cycles" << std::endl;
}

std::string formatWithCommas(uint64_t value)
{
    std::string output = "";
    std::string number = std::to_string(value);
    int numDigits = number.size();

    // Handle the first segment (less than 3 digits)
    int firstSegmentDigits = numDigits % 3;
    if (firstSegmentDigits > 0)
    {
        output += number.substr(0, firstSegmentDigits);
        if (numDigits > firstSegmentDigits)
        {
            output += ",";
        }
    }

    // Loop through the rest of the digits, adding commas every three digits
    for (int i = firstSegmentDigits; i < numDigits; i += 3)
    {
        if (i > firstSegmentDigits)
        {
            output += ",";
        }
        output += number.substr(i, 3);
    }

    return output;
}
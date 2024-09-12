#include "matrix.h"
float *makeFloatMatrix(Matrix_t dimensions)
{
    return (float *)calloc((dimensions.rows * dimensions.columns), sizeof(float));
}

int *makeIntMatrix(Matrix_t dimensions)
{
    return (int *)calloc((dimensions.rows * dimensions.columns), sizeof(int));
}

void randomizeMatrix(float *matrix, Matrix_t dimensions)
{
    for (int i = 0; i < dimensions.rows; i++)
    {
        for (int j = 0; j < dimensions.columns; j++)
        {
            matrix[j + (i * dimensions.columns)] = 2.0f*(float)2000.0f * ((float)rand() / (float)RAND_MAX) - (float)2000.0f;
        }
    }
}
void randomizeMatrix(int *matrix, Matrix_t dimensions)
{
    for (int i = 0; i < dimensions.rows; i++)
    {
        for (int j = 0; j < dimensions.columns; j++)
        {
            matrix[j + (i * dimensions.columns)] = (int)(2*2000 * ((float)rand() / (float)RAND_MAX)) - 2000;
        }
    }
}
float *mult(float *matrix1, float *matrix2, int row, int innerDimension, int column)
{
    float *output = (float *)calloc((row * column), sizeof(float));
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            float product = 0;
            for (int k = 0; k < innerDimension; k++)
            {
                product += matrix1[(innerDimension * i) + k] * matrix2[(column * k) + j];
            }
            output[(i * column) + j] = product;
        }
    }
    return output;
}
int *mult(int *matrix1, int *matrix2, int row, int innerDimension, int column)
{
    int *output = (int *)calloc((row * column), sizeof(int));
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            float product = 0;
            for (int k = 0; k < innerDimension; k++)
            {
                product += matrix1[(innerDimension * i) + k] * matrix2[(column * k) + j];
            }
            output[(i * column) + j] = product;
        }
    }
    return output;
}

float *multVec(float *matrix1, float *matrix2, int row, int innerDimension, int column)
{
    float *output = (float *)calloc((row * column), sizeof(float));
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            Vec16f rowVec, colVec;
            float product=0;
            for (int k = 0; k < innerDimension; k += 16)
            {
                rowVec.load(matrix1 + (i * innerDimension) + k);
                for (int n = 0; n < 16; n++)
                    colVec.insert(n, matrix2[j + (k * column) + n]);
                product += horizontal_add(rowVec * colVec);
            }
            output[(i * column) + j]=product;
        }
    }
    return output;
}
int *multVec(int *matrix1, int *matrix2, int row, int innerDimension, int column)
{
    int *output = (int *)calloc((row * column), sizeof(int));
    for (int i = 0; i < row; i++)
    {
        Vec16i rowVec, colVec;
        rowVec.load(matrix1 + (i * innerDimension));
        for (int j = 0; j < column; j++)
        {
            int product=0;
            for (int k = 0; k < innerDimension; k += 16)
            {
                rowVec.load(matrix1 + (i * innerDimension) + k);
                for (int n = 0; n < 16; n++)
                    colVec.insert(n, matrix2[j + (k * column) + n]);
                product += horizontal_add(rowVec * colVec);
            }
            output[(i * column) + j]=product;
        }
    }
    return output;
}

void printMatrix(float *matrix, Matrix_t dimensions)
{
    std::string printOutput = "";
    for (int i = 0; i < dimensions.rows; i++)
    {
        for (int j = 0; j < dimensions.columns; j++)
        {
            printOutput += std::to_string(matrix[j + (i * dimensions.columns)]);
            if (j != (dimensions.columns - 1))
                printOutput += ",";
        }
        printOutput += "\n";
    }
    std::cout << printOutput;
}
void printMatrix(int *matrix, Matrix_t dimensions)
{
    std::string printOutput = "";
    for (int i = 0; i < dimensions.rows; i++)
    {
        for (int j = 0; j < dimensions.columns; j++)
        {
            printOutput += std::to_string(matrix[j + (i * dimensions.columns)]);
            if (j != (dimensions.columns - 1))
                printOutput += ",";
        }
        printOutput += "\n";
    }
    std::cout << printOutput;
}
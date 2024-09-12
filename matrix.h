#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>
#include "./vectorclass/vectorclass.h"
typedef struct
{
    int rows;
    int columns;
} Matrix_t;
float *makeFloatMatrix(Matrix_t dimensions);
int *makeIntMatrix(Matrix_t dimensions);

void randomizeMatrix(float *matrix, Matrix_t dimensions);
void randomizeMatrix(int *matrix, Matrix_t dimensions);

float *mult(float *matrix1, float *matrix2, int row, int innerDimension, int column);
int *mult(int *matrix1, int *matrix2, int row, int innerDimension, int column);


float *multVec(float *matrix1, float *matrix2, int row, int innerDimension, int column);
int *multVec(int *matrix1, int *matrix2, int row, int innerDimension, int column);

void printMatrix(float *matrix, Matrix_t dimensions);
void printMatrix(int *matrix, Matrix_t dimensions);
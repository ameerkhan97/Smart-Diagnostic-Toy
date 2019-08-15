#include <stdio.h>
//#include "xc.h"
#include "MatrixOpps.h"
#include "math.h"





/******************************************************************************
 * Matrix - Matrix Operations
 *****************************************************************************/

/**
 * MatrixMultiply performs a matrix-matrix multiplication operation on two 3x3
 * matrices and returns the result in the third argument.
 */
void MatrixMultiply(double matrix_1[3][3], double matrix_2[3][3], double matrix_result[3][3]) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            matrix_result[i][j] = ((matrix_1[i][0] * matrix_2[0][j]) + (matrix_1[i][1] * matrix_2[1][j]) + (matrix_1[i][2] * matrix_2[2][j]));
        }
    }
}

/**
 * MatrixAdd performs a matrix addition operation on two 3x3 matrices and 
 * returns the result in the third argument.
 */
void MatrixAdd(double matrix_1[3][3], double matrix_2[3][3], double matrix_result[3][3]) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            matrix_result [i][j] = matrix_1[i][j] + matrix_2[i][j];
        }
    }
}

/**
 * MatrixEquals checks if the two matrix arguments are equal. The result is
 * 0 if FALSE and 1 if TRUE to follow the standard C conventions of TRUE and
 * FALSE.
 */
int MatrixEquals(double matrix_1[3][3], double matrix_2[3][3]) {
    int i, j;
    double elem_value;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            elem_value = fabs(matrix_1[i][j] - matrix_2[i][j]);
            if (fabs(elem_value) > FP_DELTA) {
                return 0;
            }
        }
    }
    return 1;
}

/******************************************************************************
 * Matrix - Scalar Operations
 *****************************************************************************/

/**
 * MatrixScalarMultiply performs the multiplication of a matrix by a scalar.
 * The result is returned in the third argument.
 */
void MatrixScalarMultiply(double scalar, double matrix[3][3], double matrix_result[3][3]) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            matrix_result[i][j] = scalar * matrix[i][j];
        }
    }
}

/******************************************************************************
 * Unary Matrix Operations
 *****************************************************************************/

/**
 * MatrixTranspose calculates the transpose of a matrix and returns the
 * result through the second argument
 */
void MatrixTranspose(double matrix[3][3], double matrix_result[3][3]) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            matrix_result[j][i] = matrix[i][j];
        }
    }
}

/**
 * MatrixPrint sends a 3x3 array to standard output with clean formatting.
 * The formatting does not need to look like the expected output given to you
 * in MatricMath.c but each element of the matrix must be separated and have
 * distinguishable position (more than a single line of output).
 */
void MatrixPrint(double matrix[3][3]) {
    int i, j;
    printf("\r\n _                 _");
    for (i = 0; i < 3; i++) {
        printf("\r\n|");
        for (j = 0; j < 3; j++) {
            printf(" %.3f ", (double) matrix[i][j]);
        }
        printf("|");
    }
    printf("\r\n -                 -\r\n");

}

/******************************************************************************
 *  Vector operations
 *****************************************************************************/

void VectorScalarMultiply(double scalar, double vector[3][1], double vector_result[3][1]) {
    int i;
    for (i = 0; i < 3; i++) {
        vector_result[i][0] = scalar * vector[i][0];
    }
}

void VectorAdd(double vector_1[3][1], double vector_2[3][1], double vector_result[3][1]) {
    int i;
    for (i = 0; i < 3; i++) {
        vector_result [i][0] = vector_1[i][0] + vector_2[i][0];
    }
}

void MatrixMultiplyVector(double matrix[3][3], double vector[3][1], double vector_result[3][1]) {
    int i;
    for (i = 0; i < 3; i++) {
            vector_result[i][0] = ((matrix[i][0] * vector[0][0]) + (matrix[i][1] * vector[1][0]) + (matrix[i][2] * vector[2][0]));
    }
}
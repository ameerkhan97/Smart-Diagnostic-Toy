#ifndef MATRIX_OPPS_H
#define MATRIX_APPS_H


#define FP_DELTA 0.0001

/******************************************************************************
 * Matrix - Matrix Operations
 *****************************************************************************/

/**
 * MatrixMultiply performs a matrix-matrix multiplication operation on two 3x3
 * matrices and returns the result in the third argument.
 */
void MatrixMultiply(double Matrix_1[3][3], double Matrix_2[3][3], double result[3][3]);

/**
 * MatrixAdd performs a matrix addition operation on two 3x3 matrices and 
 * returns the result in the third argument.
 */
void MatrixAdd(double matrix_1[3][3], double matrix_2[3][3], double matrix_result[3][3]);


/**
 * MatrixEquals checks if the two matrix arguments are equal. The result is
 * 0 if FALSE and 1 if TRUE to follow the standard C conventions of TRUE and
 * FALSE.
 */
int MatrixEquals(double Matrix_1[3][3], double Matrix_2[3][3]);


/******************************************************************************
 * Matrix - Scalar Operations
 *****************************************************************************/

/**
 * MatrixScalarMultiply performs the multiplication of a matrix by a scalar.
 * The result is returned in the third argument.
 */
void MatrixScalarMultiply(double scalar, double matrix[3][3], double matrix_result[3][3]);


/******************************************************************************
 * Unary Matrix Operations
 *****************************************************************************/

/**
 * MatrixTranspose calculates the transpose of a matrix and returns the
 * result through the second argument
 */
void MatrixTranspose(double matris[3][3], double matrix_result[3][3]);

/**
 * MatrixPrint sends a 3x3 array to standard output with clean formatting.
 * The formatting does not need to look like the expected output given to you
 * in MatricMath.c but each element of the matrix must be separated and have
 * distinguishable position (more than a single line of output).
 */
void MatrixPrint(double matrix[3][3]);

/******************************************************************************
 *  Vector operations
 *****************************************************************************/


void VectorScalarMultiply(double scalar, double vector[3][1], double vector_result[3][1]);

void VectorAdd(double vector_1[3][1], double vector_2[3][1], double vector_result[3][1]);

void MatrixMultiplyVector(double matrix[3][3], double vector[3][1], double vector_result[3][1]);


#endif

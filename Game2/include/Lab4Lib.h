#ifndef _Lab4Lib_H_INCLUDE_
#define _Lab4Lib_H_INCLUDE_

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"MatrixOpps.h"

// gyro_vector(_xxx) is 3x1, others are 3x3

void RCross(double gyro_vector[3][1], double skew_symetric[3][3]);

void ColumnNorm(double gyro_vector[3][1], double gyro_vector_norm[3][1]);

void RExp(double gyro_vector[3][1], double rod_exp[3][3]);

double Norm(double vector[3][1]);

void ForwardIntegration(double rot_matrix[3][3], double gyro_vector[3][1], double delta_t);

void ExponentialIntegration(double rot_matrix[3][3], double gyro_vector[3][1], double delta_t);

void IntegrateClosedLoop(double rot_matrix[3][3], double bias_est[3][1], double gyro_read[3][1], double mag_read[3][1], double accel_read[3][1], double mag_nertial[3][1], double accel_inertial[3][1], double delta_t);

void Triad(double rot_matrix[3][3], double mag_read[3][1], double accel_read[3][1], double mag_inertial[3][1], double accel_inertial[3][1]);

#endif









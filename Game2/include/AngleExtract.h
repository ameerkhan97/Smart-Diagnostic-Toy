#ifndef _AngleExtract_H_INCLUDE_
#define _AngleExtract_H_INCLUDE_

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double RadToDeg(double radian); 

double DegToRad(double degree); 

double FindTheta(double dir_cos_mat[3][3]);

double FindPhi(double dir_cos_mat[3][3]);

double FindPsi(double dir_cos_mat[3][3]);

#endif

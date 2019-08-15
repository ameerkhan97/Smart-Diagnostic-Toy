#include"AngleExtract.h"

double RadToDeg(double radian){
	return (180/3.14158)*radian;
			}

double DegToRad(double degree){
	return (3.14158/180)*degree;
}

double FindTheta(double dir_cos_mat[3][3]){    // pitch, rotation about y axis
	return (asin(dir_cos_mat[0][2]/-1));
}

double FindPhi(double dir_cos_mat[3][3]){      // roll, rotation about x axis
	return asin(dir_cos_mat[1][2]/cos(FindTheta(dir_cos_mat)));
}

double FindPsi(double dir_cos_mat[3][3]){      // yaw, rotation about z axis
	return asin(dir_cos_mat[0][1]/cos(FindTheta(dir_cos_mat)));
}



//

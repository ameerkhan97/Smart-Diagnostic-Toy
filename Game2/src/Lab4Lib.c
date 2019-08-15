#include"Lab4Lib.h"


//  <(°^°<)
//// forms the skew symetric from gyro readings
//

void RCross(double gyro_vector[3][1], double skew_symetric[3][3]) {
    skew_symetric[0][0] = 0;
    skew_symetric[0][1] = -gyro_vector[2][0];
    skew_symetric[0][2] = gyro_vector[1][0];
    skew_symetric[1][0] = gyro_vector[2][0];
    skew_symetric[1][1] = 0;
    skew_symetric[1][2] = -gyro_vector[0][0];
    skew_symetric[2][0] = -gyro_vector[1][0];
    skew_symetric[2][1] = gyro_vector[0][0];
    skew_symetric[2][2] = 0;
}


//  <(°^°<)
//// finds normal vector of gryo vector (technically any 3x1 vector)
//

void ColumnNorm(double gyro_vector[3][1], double gyro_vector_norm[3][1]) {
    int i = 0;
    double sum, norm = 0;

    for (i = 0; i < 3; i++) {
        sum += gyro_vector[i][0] * gyro_vector[i][0];
    }

    norm = sqrt(sum);

    for (i = 0; i < 3; i++) {
        gyro_vector_norm[i][0] = gyro_vector[i][0] / norm;
    }

}


//  <(°^°<)
//// finds norm of a 3*1 vector
//

double VectorNorm(double vector[3][1]) {
    int i = 0;
    double sum = 0;
    double norm = 0;

    for (i = 0; i < 3; i++) {
        sum += vector[i][0] * vector[i][0];
    }

    norm = sqrt(sum);

    return norm;
}


//  <(°^°<)
//// exponential Rodrigues parameter
//

void RExp(double gyro_vector[3][1], double rod_exp[3][3]) {
    double skew_symetric[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    double temp_1[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    double temp_2[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    double temp_3[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    double indentity[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    double sinc_1, cos_1, sinc_cos, sinc_sinc = 0;
    double norm, norm_half = 0;

    norm = VectorNorm(gyro_vector);
    norm_half = norm / 2;

    RCross(gyro_vector, skew_symetric);

    if ((-0.01 < norm)&&(norm < 0.01)) {
        sinc_1 = 1 - (norm_half * norm_half) / 6 + (norm_half * norm_half * norm_half * norm_half) / 120;   // taylor expansion
    } else {
        sinc_1 = sin(norm_half) / (norm_half);
    }

    cos_1 = cos(norm_half);

    // sinc * cos * skew_symetric = temp_1
    sinc_cos = sinc_1 * cos_1;
    MatrixScalarMultiply(sinc_cos, skew_symetric, temp_1);

    // skew_symetric * skew_symetric = temp_3
    // sinc * sinc = sinc_sinc
    // sinc_sinc/2 * temp_3 = temp_2
    MatrixMultiply(skew_symetric, skew_symetric, temp_3);
    sinc_sinc = sinc_1 * sinc_1;
    MatrixScalarMultiply(sinc_sinc / 2, temp_3, temp_2);

    // temp_1 + temp_2 = temp_3
    MatrixAdd(temp_1, temp_2, temp_3);

    // identity + temp_3 = rod_exp
    MatrixAdd(indentity, temp_3, rod_exp);

}


//  <(°^°<)
//// performs relativly simple forward integration
//

void ForwardIntegration(double rot_matrix[3][3], double gyro_vector[3][1], double delta_t) {
    double skew_symetric[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    double temp_1[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    double temp_2[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    int i, j = 0;

    // R_prev + R_dot * delta_t = R_next
    // R_prev * R_cross = R_dot
    RCross(gyro_vector, skew_symetric);

    // R_prev * R_corss = temp_1 (this is R_dot)
    MatrixMultiply(rot_matrix, skew_symetric, temp_1);

    // R_dot * delta_t = temp_2
    MatrixScalarMultiply(delta_t, temp_1, temp_2);

    // R_prev + (R_dot * delta_t) = temp_1 (this is R_next)
    MatrixAdd(rot_matrix, temp_2, temp_1);

    // update rot_matrix for new position
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            rot_matrix[i][j] = temp_1[i][j];
        }
    }
}


//  <(°^°<)
//// performs more useful exponential integration
//

void ExponentialIntegration(double rot_matrix[3][3], double gyro_vector[3][1], double delta_t) {
    double temp_V[3][1] = {
        {0},
        {0},
        {0}
    };
    double rod_exp[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    double temp_1[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    int i, j = 0;

    // R_prev * Rexp(gyro_vector * delta_t) = R_next
    // Rexp(gyro_vector * delta_t) = rod_exp
    temp_V[0][0] = gyro_vector[0][0] * delta_t;
    temp_V[1][0] = gyro_vector[1][0] * delta_t;
    temp_V[2][0] = gyro_vector[2][0] * delta_t;
    RExp(temp_V, rod_exp);

    // R_prev * rod_exp = temp_1 (this is R_next)
    MatrixMultiply(rot_matrix, rod_exp, temp_1);

    // update rot_matrix for new position
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            rot_matrix[i][j] = temp_1[i][j];
        }
    }
}


//  <(°^°<)
//// performs closed loop feedback control
//

void IntegrateClosedLoop(double rot_matrix[3][3], double bias_est[3][1], double gyro_read[3][1], double mag_read[3][1], double accel_read[3][1], double mag_inertial[3][1], double accel_inertial[3][1], double delta_t) {
    int i, j = 0;

    double Kp_a = 0.9;
    double Ki_a = Kp_a / 10;
    double Kp_m = 0.9;
    double Ki_m = Kp_m / 10;

    double norm_temp = 0;

    double gyro_no_bias[3][1] = {0};
    double gyro_with_feedback[3][1] = {0};
    double accel_norm[3][1] = {0};
    double mag_norm[3][1] = {0};
    double accel_inertial_norm[3][1] = {0};
    double mag_inertial_norm[3][1] = {0};
    double w_meas_accel[3][1] = {0};
    double w_meas_mag[3][1] = {0};
    double bias_dot[3][1] = {0};
    double vector_temp1[3][1] = {0};
    double vector_temp2[3][1] = {0};
    double vector_temp3[3][1] = {0};

    double matrix_temp1[3][3] = {0};
    double DCM_trans[3][3] = {0};
    double rot_temp[3][3] = {0};

    // get accel_norm
    norm_temp = VectorNorm(accel_read);
    VectorScalarMultiply(1 / norm_temp, accel_read, accel_norm);
    //printf("accel_norm: %0.3f %0.3f %0.3f %0.6f\r\n", accel_norm[0][0], accel_norm[1][0], accel_norm[2][0], norm_temp);

    // get mag_norm
    norm_temp = VectorNorm(mag_read);
    VectorScalarMultiply(1 / norm_temp, mag_read, mag_norm);
    //printf("mag_norm: %0.3f %0.3f %0.3f %0.6f\r\n", mag_norm[0][0], mag_norm[1][0], mag_norm[2][0], 1 / norm_temp);

    // get accel_inertial_norm
    norm_temp = VectorNorm(accel_inertial);
    VectorScalarMultiply(1 / norm_temp, accel_inertial, accel_inertial_norm);
    //printf("accel_inertial_norm: %0.3f %0.3f %0.3f %0.6f\r\n", accel_inertial_norm[0][0], accel_inertial_norm[1][0], accel_inertial_norm[2][0], norm_temp);

    // get mag_inertial_norm
    norm_temp = VectorNorm(mag_inertial);
    VectorScalarMultiply(1 / norm_temp, mag_inertial, mag_inertial_norm);
    //printf("mag_inertial_norm: %0.3f %0.3f %0.3f %0.6f\r\n", mag_inertial_norm[0][0], mag_inertial_norm[1][0], mag_inertial_norm[2][0], norm_temp);

    // get gyro_no_bias
    gyro_no_bias[0][0] = gyro_read[0][0] - bias_est[0][0];
    gyro_no_bias[1][0] = gyro_read[1][0] - bias_est[1][0];
    gyro_no_bias[2][0] = gyro_read[2][0] - bias_est[2][0];
    //printf("bias_dot: %0.3f %0.3f %0.3f\r\n", bias_dot[0][0], bias_dot[1][0], bias_dot[2][0]);

    // get DCM transpose
    MatrixTranspose(rot_matrix, DCM_trans);
    //printf("bias_dot: %0.3f %0.3f %0.3f\r\n", bias_dot[0][0], bias_dot[1][0], bias_dot[2][0]);

    // get w_meas_accel
    RCross(accel_norm, matrix_temp1);
    MatrixMultiplyVector(DCM_trans, accel_inertial_norm, vector_temp1);
    MatrixMultiplyVector(matrix_temp1, vector_temp1, w_meas_accel);
    //printf("bias_dot: %0.3f %0.3f %0.3f\r\n", bias_dot[0][0], bias_dot[1][0], bias_dot[2][0]);

    // get w_meas_mag
    RCross(mag_norm, matrix_temp1);
    MatrixMultiplyVector(DCM_trans, mag_inertial_norm, vector_temp1);
    MatrixMultiplyVector(matrix_temp1, vector_temp1, w_meas_mag);
    //printf("bias_dot: %0.3f %0.3f %0.3f\r\n", bias_dot[0][0], bias_dot[1][0], bias_dot[2][0]);

    // get gyro_with_feedback
    VectorScalarMultiply(Kp_a, w_meas_accel, vector_temp1);
    VectorScalarMultiply(Kp_m, w_meas_mag, vector_temp2);
    VectorAdd(vector_temp1, vector_temp2, vector_temp3);
    VectorAdd(gyro_no_bias, vector_temp3, gyro_with_feedback);
    //printf("bias_dot: %0.3f %0.3f %0.3f\r\n", bias_dot[0][0], bias_dot[1][0], bias_dot[2][0]);

    // get bias_dot
    VectorScalarMultiply(Ki_a, w_meas_accel, vector_temp1);
    VectorScalarMultiply(Ki_m, w_meas_mag, vector_temp2);
    bias_dot[0][0] = 0 - vector_temp1[0][0] - vector_temp2[0][0];
    bias_dot[1][0] = 0 - vector_temp1[1][0] - vector_temp2[1][0];
    bias_dot[2][0] = 0 - vector_temp1[2][0] - vector_temp2[2][0];
    //printf("bias_dot: %0.3f %0.3f %0.3f\r\n", bias_dot[0][0], bias_dot[1][0], bias_dot[2][0]);

    // get next rot_matrix (DCM)
    RExp(gyro_with_feedback, matrix_temp1);
    MatrixMultiply(rot_matrix, matrix_temp1, rot_temp);
    //printf("bias_dot: %0.3f %0.3f %0.3f\r\n", bias_dot[0][0], bias_dot[1][0], bias_dot[2][0]);

    // get next bias_est
    VectorAdd(bias_est, bias_dot, vector_temp1);
    //printf("bias_dot: %0.3f %0.3f %0.3f\r\n", bias_dot[0][0], bias_dot[1][0], bias_dot[2][0]);

    // set next rot_matrix and bias_est
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            rot_matrix[i][j] = rot_temp[i][j];
        }
    }

    for (i = 0; i < 3; i++) {
        bias_est[i][0] = vector_temp1[i][0];
    }
}


//  <(°^°<)
/// Triad method
//

void Triad(double rot_matrix[3][3], double mag_read[3][1], double accel_read[3][1], double mag_inertial[3][1], double accel_inertial[3][1]) {
    int i, j = 0;

    double norm_temp = 0;

    double accel_norm[3][1] = {0};
    double mag_norm[3][1] = {0};
    double accel_inertial_norm[3][1] = {0};
    double mag_inertial_norm[3][1] = {0};
    double m[3][1] = {0};
    double M[3][1] = {0};
    double vector_temp1[3][1] = {0};
    double vector_temp2[3][1] = {0};

    //double matrix_temp1[3][3] = {0};
    double A[3][3] = {0};
    double DCM_trans[3][3] = {0};
    double matrix_temp1[3][3] = {0};
    double matrix_temp2[3][3] = {0};

    // get accel_norm
    norm_temp = VectorNorm(accel_read);
    VectorScalarMultiply(1 / norm_temp, accel_read, accel_norm);
    //printf("accel_norm: %0.3f %0.3f %0.3f %0.6f\r\n", accel_norm[0][0], accel_norm[1][0], accel_norm[2][0], norm_temp);

    // get mag_norm
    norm_temp = VectorNorm(mag_read);
    VectorScalarMultiply(1 / norm_temp, mag_read, mag_norm);
    //printf("mag_norm: %0.3f %0.3f %0.3f %0.6f\r\n", mag_norm[0][0], mag_norm[1][0], mag_norm[2][0], 1 / norm_temp);

    // get accel_inertial_norm
    norm_temp = VectorNorm(accel_inertial);
    VectorScalarMultiply(1 / norm_temp, accel_inertial, accel_inertial_norm);
    //printf("accel_inertial_norm: %0.3f %0.3f %0.3f %0.6f\r\n", accel_inertial_norm[0][0], accel_inertial_norm[1][0], accel_inertial_norm[2][0], norm_temp);

    // get mag_inertial_norm
    norm_temp = VectorNorm(mag_inertial);
    VectorScalarMultiply(1 / norm_temp, mag_inertial, mag_inertial_norm);
    //printf("mag_inertial_norm: %0.3f %0.3f %0.3f %0.6f\r\n", mag_inertial_norm[0][0], mag_inertial_norm[1][0], mag_inertial_norm[2][0], norm_temp);

    // get m
    RCross(mag_norm, matrix_temp1);
    MatrixMultiplyVector(matrix_temp1, accel_norm, vector_temp1);
    norm_temp = VectorNorm(vector_temp1);
    VectorScalarMultiply(1 / norm_temp, vector_temp1, m);

    // get M
    RCross(mag_inertial_norm, matrix_temp1);
    MatrixMultiplyVector(matrix_temp1, accel_inertial_norm, vector_temp1);
    norm_temp = VectorNorm(vector_temp1);
    VectorScalarMultiply(1 / norm_temp, vector_temp1, M);

    // get A (first the last column of each of two matrices-> make matrices-> multiply matrices)
    RCross(mag_inertial_norm, matrix_temp1);
    MatrixMultiplyVector(matrix_temp1, M, vector_temp1);
    
    RCross(mag_norm, matrix_temp1);
    MatrixMultiplyVector(matrix_temp1, m, vector_temp2);
    
    for (i = 0; i < 3; i++) {
        matrix_temp1[i][0] = mag_inertial_norm[i][0];
        matrix_temp2[i][0] = mag_norm[i][0];
    }
    for (i = 0; i < 3; i++) {
        matrix_temp1[i][1] = M[i][0];
        matrix_temp2[i][1] = m[i][0];
    }
    for (i = 0; i < 3; i++) {
        matrix_temp1[i][2] = vector_temp1[i][0];
        matrix_temp2[i][2] = vector_temp2[i][0];
    }

    MatrixMultiply(matrix_temp1, matrix_temp2, A);
    
    MatrixTranspose(A, rot_matrix);

    // set next rot_matrix to A if transpose seems wrong
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            rot_matrix[i][j] = A[i][j];
        }
    }

}

//

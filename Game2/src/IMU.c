

#include <BOARD.h>
#include <IMU.h>
#include <I2C.h>
#include <stdio.h>

#ifdef IMU_TEST
#include <stdio.h>
#endif


/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * @Function IMU_Init(Rate)

 * @return 0 if error, 1 if succeeded
 * @brief  Initializes the IMU for usage. This will set all sensors to approximately ??HZ
 * and Accel: ??g,Gyro:  ??dps and Mag: ??-bit for the sensors
 * @author Jordan (using template from Max Dunne) */
char IMU_Init(void) {
    //    unsigned int intReturn;
    //    unsigned char byteReturn;
    //
    //    intReturn = I2C_Init(I2C_DEFUALT_RATE);
    //    if (intReturn != I2C_DEFUALT_RATE) {
    //        return FALSE; // fail out if I2C does not set a rate that makes sense
    //    }
    //
    //    // we have to configure the MPU first due to idiocy with the I2C setup internally
    //    byteReturn = I2C_ReadRegister(ACCGYR_I2C_ADDRESS, MPU_WHOAMI_REGISTER);
    //    //    printf("\r\n%X", byteReturn);
    //    if (byteReturn != MPU_WHOAMI_VALUE) {
    //        return FALSE; // make sure we are talking to the right device first
    //    }
    //
    //    I2C_WriteReg(ACCGYR_I2C_ADDRESS, MPU_POWER_CTRL1, 0x01); // turn it on and hopefully use pll
    //
    //    I2C_WriteReg(ACCGYR_I2C_ADDRESS, MPU_CONFIG, 0x03); // don't really want a dlp but turning it off is non trivial
    //    // setting it to fastest bandwidth for the gyro
    //    //byteReturn = I2C_ReadRegister(ACCGYR_I2C_ADDRESS,MPU_GYRO_CONFIG);
    //    //printf("\r\ngyro config: %d",byteReturn);
    //    I2C_WriteReg(ACCGYR_I2C_ADDRESS, MPU_GYRO_CONFIG, 0x00); //set scale on gyro to 250 degrees /s
    //    dbprintf("\r\nGYRO CONFIG Set To: 0X%X", I2C_ReadRegister(ACCGYR_I2C_ADDRESS, MPU_GYRO_CONFIG));
    //    I2C_WriteReg(ACCGYR_I2C_ADDRESS, MPU_SMPLRT_DIV, 5); // set the output data rate to 100Hz
    //    dbprintf("\r\nSMART RATE Set To: 0X%X", I2C_ReadRegister(ACCGYR_I2C_ADDRESS, MPU_SMPLRT_DIV));
    //
    //    // we now can configure the accelerometer
    //
    //    I2C_WriteReg(ACCGYR_I2C_ADDRESS, MPU_ACCEL_CONFIG2, 0b1001);
    //    //sets the bandwidth to 184 and internal to 1K, actually output controlled by smart divider
    //    dbprintf("\r\nACCEL CONFIG2 Set To: 0X%X", I2C_ReadRegister(ACCGYR_I2C_ADDRESS, MPU_ACCEL_CONFIG2));
    //
    //    I2C_WriteReg(ACCGYR_I2C_ADDRESS, MPU_ACCEL_CONFIG, 0);
    //    dbprintf("\r\nACCEL CONFIG Set To: 0X%X", I2C_ReadRegister(ACCGYR_I2C_ADDRESS, MPU_ACCEL_CONFIG));
    //
    //    // finally we configure the I2C to allow us to talk to the mag
    //    I2C_WriteReg(ACCGYR_I2C_ADDRESS, MPU_INT_BYPASS_CONFIG, 0x22);
    //    dbprintf("\r\nBypass CONFIG Set To: 0X%X", I2C_ReadRegister(ACCGYR_I2C_ADDRESS, MPU_INT_BYPASS_CONFIG));
    //
    //
    //    byteReturn = I2C_ReadRegister(MAG_I2C_ADDRESS, AK_WHOAMI_REGISTER);
    //    //    printf("\r\n%X", byteReturn);
    //    if (byteReturn != MAG_WHOAMI_VALUE) {
    //        return FALSE; // make sure we are talking to the right device first
    //    }
    //
    //    //configure output rate and scale
    //    //    I2C_WriteReg(MAG_I2C_ADDRESS,AK_CNTL1,0b0);
    //    //    I2C_WriteReg(MAG_I2C_ADDRESS,AK_CNTL1,0b1111);
    //    //    I2C_WriteReg(MAG_I2C_ADDRESS,AK_CNTL1,0b0);
    //    I2C_WriteReg(MAG_I2C_ADDRESS, AK_CNTL1, 0b10110);
    //    dbprintf("\r\nMAG CNTL1 CONFIG Set To: 0X%X", I2C_ReadRegister(MAG_I2C_ADDRESS, AK_CNTL1));
    //    return TRUE;


    I2C_Init(100000);

    //set normal power mode
    I2C_WriteReg(BNO055_I2C_ADDR1, BNO055_PWR_MODE_ADDR, BNO055_POWER_MODE_NORMAL);



    //set NDOF operating mode
    I2C_WriteReg(BNO055_I2C_ADDR1, BNO055_OPR_MODE_ADDR, BNO055_OPERATION_MODE_NDOF);


}

/**
 * @Function IMU_Read*()
 * @param None
 * @return Returns linear acceleration reading
 * @brief reads sensor axis as given by name
 * @author Jordan (using template from Max Dunne)*/
int IMU_ReadAccelX(void) {
    int8_t temp_LSB;
    int8_t temp_MSB;

    temp_LSB = I2C_ReadRegister(BNO055_I2C_ADDR1, BNO055_LINEAR_ACCEL_DATA_X_LSB_ADDR);

    temp_MSB = I2C_ReadRegister(BNO055_I2C_ADDR1, BNO055_LINEAR_ACCEL_DATA_X_MSB_ADDR);

    return (temp_MSB << 8) | (temp_LSB & 0xff);
}

/**
 * @Function IMU_Read*()
 * @param None
 * @return Returns linear acceleration reading
 * @brief reads sensor axis as given by name
 * @author Jordan (using template from Max Dunne)*/
int IMU_ReadAccelY(void) {
    int8_t temp_LSB;
    int8_t temp_MSB;

    temp_LSB = I2C_ReadRegister(BNO055_I2C_ADDR1, BNO055_LINEAR_ACCEL_DATA_Y_LSB_ADDR);

    temp_MSB = I2C_ReadRegister(BNO055_I2C_ADDR1, BNO055_LINEAR_ACCEL_DATA_Y_MSB_ADDR);

    return (temp_MSB << 8) | (temp_LSB & 0xff);
}

/**
 * @Function IMU_Read*()
 * @param None
 * @return Returns linear acceleration reading
 * @brief reads sensor axis as given by name
 * @author Jordan (using template from Max Dunne)*/
int IMU_ReadAccelZ(void) {
    int8_t temp_LSB;
    int8_t temp_MSB;

    temp_LSB = I2C_ReadRegister(BNO055_I2C_ADDR1, BNO055_LINEAR_ACCEL_DATA_Z_LSB_ADDR);

    temp_MSB = I2C_ReadRegister(BNO055_I2C_ADDR1, BNO055_LINEAR_ACCEL_DATA_Z_MSB_ADDR);

    return (temp_MSB << 8) | (temp_LSB & 0xff);
}

/**
 * @Function IMU_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author Jordan (using template from Max Dunne)*/
int IMU_ReadGyroX(void) {
    int8_t temp_LSB;
    int8_t temp_MSB;

    temp_LSB = I2C_ReadRegister(BNO055_I2C_ADDR1, BNO055_GYRO_DATA_X_LSB_ADDR);

    temp_MSB = I2C_ReadRegister(BNO055_I2C_ADDR1, BNO055_GYRO_DATA_X_MSB_ADDR);

    return (temp_MSB << 8) | (temp_LSB & 0xff);
}

/**
 * @Function IMU_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author Jordan (using template from Max Dunne)e*/
int IMU_ReadGyroY(void) {
    int8_t temp_LSB;
    int8_t temp_MSB;

    temp_LSB = I2C_ReadRegister(BNO055_I2C_ADDR1, BNO055_GYRO_DATA_Y_LSB_ADDR);

    temp_MSB = I2C_ReadRegister(BNO055_I2C_ADDR1, BNO055_GYRO_DATA_Y_MSB_ADDR);

    return (temp_MSB << 8) | (temp_LSB & 0xff);
}

/**
 * @Function IMU_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author Jordan (using template from Max Dunne)*/
int IMU_ReadGyroZ(void) {
    int8_t temp_LSB;
    int8_t temp_MSB;

    temp_LSB = I2C_ReadRegister(BNO055_I2C_ADDR1, BNO055_GYRO_DATA_Z_LSB_ADDR);

    temp_MSB = I2C_ReadRegister(BNO055_I2C_ADDR1, BNO055_GYRO_DATA_Z_MSB_ADDR);

    return (temp_MSB << 8) | (temp_LSB & 0xff);
}

/**
 * @Function IMU_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author Max Dunne*/
int IMU_ReadMagX(void) {
    int8_t temp_LSB;
    int8_t temp_MSB;

    temp_LSB = I2C_ReadRegister(BNO055_I2C_ADDR1, BNO055_MAG_DATA_X_LSB_ADDR);

    temp_MSB = I2C_ReadRegister(BNO055_I2C_ADDR1, BNO055_MAG_DATA_X_MSB_ADDR);

    return (temp_MSB << 8) | (temp_LSB & 0xff);
}

/**
 * @Function IMU_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author Max Dunne*/
int IMU_ReadMagY(void) {
    int8_t temp_LSB;
    int8_t temp_MSB;

    temp_LSB = I2C_ReadRegister(BNO055_I2C_ADDR1, BNO055_MAG_DATA_Y_LSB_ADDR);

    temp_MSB = I2C_ReadRegister(BNO055_I2C_ADDR1, BNO055_MAG_DATA_Y_MSB_ADDR);

    return (temp_MSB << 8) | (temp_LSB & 0xff);
}

/**
 * @Function IMU_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author Max Dunne*/
int IMU_ReadMagZ(void) {
    int8_t temp_LSB;
    int8_t temp_MSB;

    temp_LSB = I2C_ReadRegister(BNO055_I2C_ADDR1, BNO055_MAG_DATA_Z_LSB_ADDR);

    temp_MSB = I2C_ReadRegister(BNO055_I2C_ADDR1, BNO055_MAG_DATA_Z_MSB_ADDR);

    return (temp_MSB << 8) | (temp_LSB & 0xff);
}

/**
 * @Function IMU_Read*()
 * @param None
 * @return Returns processed sensor reading
 * @brief reads sensor axis as given by name
 * @author Max Dunne*/
int IMU_ReadEulerR(void) {
    int8_t temp_LSB;
    int8_t temp_MSB;

    temp_LSB = I2C_ReadRegister(BNO055_I2C_ADDR1, BNO055_EULER_R_LSB_ADDR);

    temp_MSB = I2C_ReadRegister(BNO055_I2C_ADDR1, BNO055_EULER_R_MSB_ADDR);

    return (temp_MSB << 8) | (temp_LSB & 0xff);
}

/**
 * @Function IMU_Read*()
 * @param None
 * @return Returns processed sensor reading
 * @brief reads sensor axis as given by name
 * @author Max Dunne*/
int IMU_ReadEulerP(void) {
    int8_t temp_LSB;
    int8_t temp_MSB;

    temp_LSB = I2C_ReadRegister(BNO055_I2C_ADDR1, BNO055_EULER_P_LSB_ADDR);

    temp_MSB = I2C_ReadRegister(BNO055_I2C_ADDR1, BNO055_EULER_P_MSB_ADDR);

    return (temp_MSB << 8) | (temp_LSB & 0xff);
}

/**
 * @Function IMU_Read*()
 * @param None
 * @return Returns processed sensor reading
 * @brief reads sensor axis as given by name
 * @author Max Dunne*/
int IMU_ReadEulerH(void) {
    int8_t temp_LSB;
    int8_t temp_MSB;

    temp_LSB = I2C_ReadRegister(BNO055_I2C_ADDR1, BNO055_EULER_H_LSB_ADDR);

    temp_MSB = I2C_ReadRegister(BNO055_I2C_ADDR1, BNO055_EULER_H_MSB_ADDR);

    return (temp_MSB << 8) | (temp_LSB & 0xff);
}

//#ifdef IMU_TEST
//
//#include <stdio.h>
//
//#include "serial.h"
//#include <math.h>
//
//int main(void) {
//    BOARD_Init();
//
//    int aX, aY, aZ, gX, gY, gZ, mX, mY, mZ;
//    printf("\r\nWelcome to mpu9250 test, system will be inited and configured and then data printed");
//    if (!IMU_Init()) {
//        printf("\r\nSensor failed to come up");
//        while (1);
//    }
//    printf("\r\nSensor is up");
//    //    while(1);
//    while (1) {
//        if (IsTransmitEmpty()) {
//            aX = IMU_ReadAccelX();
//            aY = IMU_ReadAccelY();
//            aZ = IMU_ReadAccelZ();
//            gX = IMU_ReadGyroX();
//            gY = IMU_ReadGyroY();
//            gZ = IMU_ReadGyroZ();
//            mX = IMU_ReadMagX();
//            mY = IMU_ReadMagY();
//            mZ = IMU_ReadMagZ();
//            printf("\r\n(X,Y,Z)Accel : (%d,%d,%d)Gyro : (%d,%d,%d)Mag: (%d,%d,%d)", aX, aY, aZ, gX, gY, gZ, mX, mY, mZ);
//            mX = 0;
//        }
//    }
//
//    while (1);
//    return 1;
//}
//
//#endif
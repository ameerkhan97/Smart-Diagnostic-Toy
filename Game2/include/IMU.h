/* 
 * File:   IMU.h
 * Author: Jordan (using template from Max Dunne; CMPE167 -> IMU.h/IMU.c)
 *
 * Created on Apr 24, 2019
 */

#ifndef IMU_H
#define	IMU_H

/* bno055 I2C Address */
#define BNO055_I2C_ADDR1                (0x28)
#define BNO055_I2C_ADDR2                (0x29)


/* Linear acceleration data registers*/
#define BNO055_LINEAR_ACCEL_DATA_X_LSB_ADDR			(0X28)
#define BNO055_LINEAR_ACCEL_DATA_X_MSB_ADDR			(0X29)
#define BNO055_LINEAR_ACCEL_DATA_Y_LSB_ADDR			(0X2A)
#define BNO055_LINEAR_ACCEL_DATA_Y_MSB_ADDR			(0X2B)
#define BNO055_LINEAR_ACCEL_DATA_Z_LSB_ADDR			(0X2C)
#define BNO055_LINEAR_ACCEL_DATA_Z_MSB_ADDR			(0X2D)

/*Gravity data registers*/
#define BNO055_GRAVITY_DATA_X_LSB_ADDR			(0X2E)
#define BNO055_GRAVITY_DATA_X_MSB_ADDR			(0X2F)
#define BNO055_GRAVITY_DATA_Y_LSB_ADDR			(0X30)
#define BNO055_GRAVITY_DATA_Y_MSB_ADDR			(0X31)
#define BNO055_GRAVITY_DATA_Z_LSB_ADDR			(0X32)
#define BNO055_GRAVITY_DATA_Z_MSB_ADDR			(0X33)

/*Gyro data registers*/
#define BNO055_GYRO_DATA_X_LSB_ADDR			(0X14)
#define BNO055_GYRO_DATA_X_MSB_ADDR			(0X15)
#define BNO055_GYRO_DATA_Y_LSB_ADDR			(0X16)
#define BNO055_GYRO_DATA_Y_MSB_ADDR			(0X17)
#define BNO055_GYRO_DATA_Z_LSB_ADDR			(0X18)
#define BNO055_GYRO_DATA_Z_MSB_ADDR			(0X19)

/*Mag data register*/
#define BNO055_MAG_DATA_X_LSB_ADDR			(0X0E)
#define BNO055_MAG_DATA_X_MSB_ADDR			(0X0F)
#define BNO055_MAG_DATA_Y_LSB_ADDR			(0X10)
#define BNO055_MAG_DATA_Y_MSB_ADDR			(0X11)
#define BNO055_MAG_DATA_Z_LSB_ADDR			(0X12)
#define BNO055_MAG_DATA_Z_MSB_ADDR			(0X13)

/*Euler data registers*/
#define BNO055_EULER_H_LSB_ADDR			(0X1A)  // Heading (Yaw), Z
#define BNO055_EULER_H_MSB_ADDR			(0X1B)

#define BNO055_EULER_R_LSB_ADDR			(0X1C)  // Roll, X
#define BNO055_EULER_R_MSB_ADDR			(0X1D)

#define BNO055_EULER_P_LSB_ADDR			(0X1E)  // Pitch Y
#define BNO055_EULER_P_MSB_ADDR			(0X1F)

/* Mode registers*/
#define BNO055_OPR_MODE_ADDR				(0X3D)
#define BNO055_PWR_MODE_ADDR				(0X3E)


/* Power mode*/
#define BNO055_POWER_MODE_NORMAL	(0X00)
#define BNO055_POWER_MODE_LOWPOWER	(0X01)
#define BNO055_POWER_MODE_SUSPEND	(0X02)


/* Configuration registers*/
#define BNO055_ACCEL_CONFIG_ADDR				(0X08)
#define BNO055_MAG_CONFIG_ADDR					(0X09)
#define BNO055_GYRO_CONFIG_ADDR					(0X0A)
#define BNO055_GYRO_MODE_CONFIG_ADDR			(0X0B)
#define BNO055_ACCEL_SLEEP_CONFIG_ADDR			(0X0C)
#define BNO055_GYRO_SLEEP_CONFIG_ADDR			(0X0D)
#define BNO055_MAG_SLEEP_CONFIG_ADDR			(0x0E)


/* Operation mode settings*/
#define BNO055_OPERATION_MODE_CONFIG			(0X00)
#define BNO055_OPERATION_MODE_ACCONLY			(0X01)
#define BNO055_OPERATION_MODE_MAGONLY			(0X02)
#define BNO055_OPERATION_MODE_GYRONLY			(0X03)
#define BNO055_OPERATION_MODE_ACCMAG			(0X04)
#define BNO055_OPERATION_MODE_ACCGYRO			(0X05)
#define BNO055_OPERATION_MODE_MAGGYRO			(0X06)
#define BNO055_OPERATION_MODE_AMG				(0X07)
#define BNO055_OPERATION_MODE_IMUPLUS			(0X08)
#define BNO055_OPERATION_MODE_COMPASS			(0X09)
#define BNO055_OPERATION_MODE_M4G				(0X0A)
#define BNO055_OPERATION_MODE_NDOF_FMC_OFF		(0X0B)
#define BNO055_OPERATION_MODE_NDOF				(0X0C)

/**
 * @Function IMU_Init(Rate)

 * @return 0 if error, 1 if succeeded
 * @brief  Initializes the MPU 9250 for usage. This will set all sensors to approximately 100HZ
 * and Accel: XX, Gyro:  XXXdps and Mag: XX-bit for the sensors
 * @author Max Dunne */
char IMU_Init(void);

/**
 * @Function IMU_Read*()
 * @param None
 * @return Returns linear acceleration reading
 * @brief reads sensor axis as given by name
 * @author Max Dunne*/
int IMU_ReadAccelX(void);

/**
 * @Function IMU_Read*()
 * @param None
 * @return Returns linear acceleration reading
 * @brief reads sensor axis as given by name
 * @author Max Dunne*/
int IMU_ReadAccelY(void);

/**
 * @Function IMU_Read*()
 * @param None
 * @return Returns linear acceleration reading
 * @brief reads sensor axis as given by name
 * @author Max Dunne*/
int IMU_ReadAccelZ(void);

/**
 * @Function IMU_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author Max Dunne*/
int IMU_ReadGyroX(void);

/**
 * @Function IMU_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author Max Dunne*/
int IMU_ReadGyroY(void);


/**
 * @Function IMU_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author Max Dunne*/
int IMU_ReadGyroZ(void);

/**
 * @Function IMU_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author Max Dunne*/
int IMU_ReadMagX(void);

/**
 * @Function IMU_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author Max Dunne*/
int IMU_ReadMagY(void);

/**
 * @Function IMU_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author Max Dunne*/
int IMU_ReadMagZ(void);

/**
 * @Function IMU_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author Max Dunne*/
int IMU_ReadEulerR(void);

/**
 * @Function IMU_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author Max Dunne*/
int IMU_ReadEulerP(void);


/**
 * @Function IMU_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author Max Dunne*/
int IMU_ReadEulerH(void);



#endif	/* IMU_H */


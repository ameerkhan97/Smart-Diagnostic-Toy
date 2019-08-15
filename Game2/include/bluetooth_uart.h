/* 
 * File:   bluetooth_uart.h
 * Author: Jacques
 *
 * Created on March 2, 2019, 3:58 PM
 */

#ifndef BLUETOOTH_UART_H
#define	BLUETOOTH_UART_H

#ifdef	__cplusplus
extern "C" {
#endif

//initialize the header file
void SERIAL2_Init(void);
//transmits a char through uart 2
void PutChar2(char ch);
//receives a char through uart 2
char GetChar2(void);
//transmits a string through uart2
void BluetoothWriteString(const char * string);
#ifdef	__cplusplus
}
#endif

#endif	/* BLUETOOTH_UART_H */


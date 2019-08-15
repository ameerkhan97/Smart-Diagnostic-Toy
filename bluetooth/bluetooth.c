

#include <xc.h>
#include <serial.h>
#include <BOARD.h>
#include <peripheral/uart.h>
#include <stdint.h>
#include <plib.h>


#define F_PB (BOARD_GetPBClock())
#define QUEUESIZE 512

/* UART port 1 = Pin 0 (RX), Pin 1 (TX)
 * UART port 2 = Pin 39 (RX), Pin 40 (TX)
 */
typedef struct CircBuffer {
    unsigned char buffer[QUEUESIZE];
    int head;
    int tail;
    unsigned int size;
    unsigned char overflowCount;
} CircBuffer;

typedef struct CircBuffer *CBRef;

void newCircBuffer(CBRef cB);
void freeCircBuffer(CBRef* B);
unsigned int getLength(CBRef cB);
int readHead(CBRef cB);
int readTail(CBRef cB);
unsigned char peak(CBRef cB);
unsigned char readFront(CBRef cB);
unsigned char writeBack(CBRef cB, unsigned char data);




//uart 2
struct CircBuffer outgoingUart2;
CBRef transmitBuffer2;
struct CircBuffer incomingUart2;
CBRef receiveBuffer2;
static uint8_t AddingToTransmit2 = FALSE;
static uint8_t GettingFromReceive2 = FALSE;
static uint8_t TransmitCollisionOccured2 = FALSE;
static uint8_t ReceiveCollisonOccured2 = FALSE;


//uart 2

void SERIAL2_Init(void)
{
    transmitBuffer2 = (struct CircBuffer*) &outgoingUart2;
    newCircBuffer(transmitBuffer2);

    receiveBuffer2 = (struct CircBuffer*) & incomingUart2;
    newCircBuffer(receiveBuffer2);
    // If RTS is enabled, it is asserted (driven low) when the receive buffer
    // is not full (i.e., the UART is ready to receive data).  This is also known
    // as "RTS Flow-Control Mode".
    UARTConfigure(UART2, 0x00);

    UARTSetDataRate(UART2, F_PB, 9600); //change baudarate according to hc-06 settings
    UARTSetFifoMode(UART2, UART_INTERRUPT_ON_RX_NOT_EMPTY | UART_INTERRUPT_ON_RX_NOT_EMPTY);

    INTSetVectorPriority(INT_UART_2_VECTOR, INT_PRIORITY_LEVEL_4);

    UARTEnable(UART2, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_TX | UART_RX));
    INTEnable(INT_U2RX, INT_ENABLED);
    INTEnable(INT_U2TX, INT_ENABLED);
}

//uart 2
void PutChar2(char ch)
{
    if(getLength(transmitBuffer2)!= QUEUESIZE){
        AddingToTransmit2 = TRUE;
        writeBack(transmitBuffer2, ch);
        AddingToTransmit2  = FALSE;
        if(U2STAbits.TRMT){
            INTSetFlag(INT_U2TX);
        }
        
        if(TransmitCollisionOccured2){
            INTSetFlag(INT_U2TX);
            TransmitCollisionOccured2 = FALSE;
        }       
    }  
 }


void BluetoothWriteString(const char * string)
{
    if (string == NULL) {
        return;
    }
    int i = 0;
    while (string[i] != '\0') {
        PutChar2(string[i]);
        i++;
    }

}

//uart 2

char GetChar2(void)
{
    char ch;
    if (getLength(receiveBuffer2) == 0) {
        ch = 0;
    } else {
        GettingFromReceive2 = TRUE;
        ch = readFront(receiveBuffer2);
        GettingFromReceive2 = FALSE;
    }

    if (ReceiveCollisonOccured2) {
        INTSetFlag(INT_U2RX);
        ReceiveCollisonOccured2 = FALSE;
    }

    return ch;
}



//uart2
char IsReceiveEmpty2(void)
{
    if (getLength(receiveBuffer2) == 0)
        return TRUE;
    return FALSE;
}


char IsTransmitEmpty2(void)
{
    if (getLength(transmitBuffer2) == 0)
        return TRUE;
    return FALSE;
}

//uart2
void __ISR(_UART2_VECTOR, ipl4auto) IntUart2Handler(void)
{
    if (INTGetFlag(INT_U2RX)) {
        INTClearFlag(INT_U2RX);
        if (!GettingFromReceive2) {
            writeBack(receiveBuffer2, (unsigned char) U2RXREG);
        } else {
            //acknowledge we have a collision and return
            ReceiveCollisonOccured2 = TRUE;
        }
    }
    if (INTGetFlag(INT_U2TX)) {
        INTClearFlag(INT_U2TX);
        if (!(getLength(transmitBuffer2) == 0)) {
            if (!AddingToTransmit2) {
                U2TXREG = readFront(transmitBuffer2);
            } else {
                //acknowledge we have a collision and return
                TransmitCollisionOccured2 = TRUE;
            }
        }
    }

}


 /*===============================

    I2C_MODUAL

    this C module is part of sensor interfacing.
    It provides functions that allow you to communicate with sensors.

    Written by some TI people, modified by Tim Yue andd Dianiel Walnut

    Requirements for use:

    port 3.0(SDA) & port 3.1（SCL)
    power pins 5V and GND


===============================*/


#ifndef I2C_modual_H_
#define I2C_modual_H_

#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>

/*===================
 * sensor I2C address
 ===================*/
#define SLAVE_ADDR  0x3E


/*=====================
 * definitions
 ======================*/
#define CMD_TYPE_0_SLAVE      0
#define CMD_TYPE_1_SLAVE      1
#define CMD_TYPE_2_SLAVE      2

#define CMD_TYPE_0_MASTER      3
#define CMD_TYPE_1_MASTER      4
#define CMD_TYPE_2_MASTER      5

#define TYPE_0_LENGTH   1
#define TYPE_1_LENGTH   2
#define TYPE_2_LENGTH   6
#define MAX_BUFFER_SIZE     20

/* MasterTypeX are example buffers initialized in the master, they will be
 * sent by the master to the slave.
 * SlaveTypeX are example buffers initialized in the slave, they will be
 * sent by the slave to the master.
 * */


//******************************************************************************
// General I2C State Machine ***************************************************
//******************************************************************************

typedef enum I2C_ModeEnum{
    IDLE_MODE,
    NACK_MODE,
    TX_REG_ADDRESS_MODE,
    RX_REG_ADDRESS_MODE,
    TX_DATA_MODE,
    RX_DATA_MODE,
    SWITCH_TO_RX_MODE,
    SWITHC_TO_TX_MODE,
    TIMEOUT_MODE
} I2C_Mode;

/* Used to track the state of the software state machine*/
I2C_Mode MasterMode;

/* The Register Address/Command to use*/
uint8_t TransmitRegAddr;

/* ReceiveBuffer: Buffer used to receive data in the ISR
 * RXByteCtr: Number of bytes left to receive
 * ReceiveIndex: The index of the next byte to be received in ReceiveBuffer
 * TransmitBuffer: Buffer used to transmit data in the ISR
 * TXByteCtr: Number of bytes left to transfer
 * TransmitIndex: The index of the next byte to be transmitted in TransmitBuffer
 * */
uint8_t ReceiveBuffer[MAX_BUFFER_SIZE];
uint8_t RXByteCtr;
uint8_t ReceiveIndex;
uint8_t TransmitBuffer[MAX_BUFFER_SIZE];
uint8_t TXByteCtr;
uint8_t TransmitIndex;

/*================
 * globals
 ================*/
uint8_t MasterType2 [TYPE_2_LENGTH];
uint8_t MasterType1 [TYPE_1_LENGTH];
uint8_t MasterType0 [TYPE_0_LENGTH];


uint8_t SlaveType2 [TYPE_2_LENGTH];
uint8_t SlaveType1 [TYPE_1_LENGTH];
uint8_t SlaveType0 [TYPE_0_LENGTH];

/*====================
 * function definition
 =====================*/
/* I2C Write and Read Functions */

/* For slave device with dev_addr, writes the data specified in *reg_data
 *
 * dev_addr: The slave device address.
 *           Example: SLAVE_ADDR
 * reg_addr: The register or command to send to the slave.
 *           Example: CMD_TYPE_0_MASTER
 * *reg_data: The buffer to write
 *           Example: MasterType0
 * count: The length of *reg_data
 *           Example: TYPE_0_LENGTH
 *  */

I2C_Mode I2C_Master_WriteReg(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint8_t count);

/*=========================
 * LineSensorinit
 *
 * this function is for initializing the line sensor array
 * intput:N/A
 * output:N/A
 *
 * globals affected:N/A
 *
 =========================*/
void LineSensorinit();
/* For slave device with dev_addr, read the data specified in slaves reg_addr.
 * The received data is available in ReceiveBuffer
 *
 * dev_addr: The slave device address.
 *           Example: SLAVE_ADDR
 * reg_addr: The register or command to send to the slave.
 *           Example: CMD_TYPE_0_SLAVE
 * count: The length of data to read
 *           Example: TYPE_0_LENGTH
 *  */
I2C_Mode I2C_Master_ReadReg(uint8_t dev_addr, uint8_t reg_addr, uint8_t count);
/*=================================
 * CopyArray
 *
 * written by TI people
 * copies whats in receive buffer to another array
 *
 * input:   Pointer to source array(receive buffer)
 *          Pointer to array you want
 *          how many data you want
 * output:  data from source to dest
===================================*/
void CopyArray(uint8_t *source, uint8_t *dest, uint8_t count);

#endif

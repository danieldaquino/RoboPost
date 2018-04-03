/*===============================

    I2C Module

    this C module is part of sensor interfacing.
    It provides functions that allow you to communicate with sensors.

    forked from: Nima Eskandari(some TI people), modified by Tim Yue and Daniel Walnut

    Resources used:
    
    1. port 3.0(SDA) & port 3.1（SCL)
    2. power pins 5V and GND
    3. UCSI(B0)
    
    Requirements:
    
    1. ArrayUtils module

===============================*/
#ifndef I2C_module_H
#define I2C_module_H

/*=====================
 * Includes
 ======================*/
#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>

/*=====================
 * Macros
 ======================*/
#define TYPE_0_LENGTH   1
#define TYPE_1_LENGTH   2
#define TYPE_2_LENGTH   6
#define MAX_BUFFER_SIZE 20

/*=====================
Data Types
======================*/
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

/*====================
 * Function Prototypes
 =====================*/

/*==============================

	~~I2CInit~~

	Initializes the I2C module.
	
	inputs: none 
	outputs: none
	Globals Affected: P3.1, P3.0, UCB0
	
==============================*/
void I2CInit();

/*==============================

	~~I2CWrite~~

 For slave device with dev_addr, writes the data specified in *reg_data
 *
 * dev_addr: The slave device address.
 *           Example: SLAVE_ADDR
 * reg_addr: The register or command to send to the slave.
 *           Example: CMD_TYPE_0_MASTER
 * *reg_data: The buffer to write
 *           Example: MasterType0
 * count: The length of *reg_data
 *           Example: TYPE_0_LENGTH
 ==============================*/
I2C_Mode I2CWrite(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint8_t count);

/*==============================

	~~I2CRead~~
	
	For slave device with dev_addr, read the data specified in slaves reg_addr.
 * The received data is available in ReceiveBuffer
 *
 * dev_addr: The slave device address.
 *           Example: SLAVE_ADDR
 * reg_addr: The register or command to send to the slave.
 *           Example: CMD_TYPE_0_SLAVE
 * count: The length of data to read
 *           Example: TYPE_0_LENGTH
 * destination: Pointer to the receiving array.
===============================*/
I2C_Mode I2CRead(uint8_t dev_addr, uint8_t reg_addr, uint8_t count, uint8_t * destination);

/*=================================
 * USCI_B0_ISR
 *
 * Efficiently handles the low level I2C communications
 *
 * inputs: none
 * outputs: none
===================================*/
void USCI_B0_ISR(void);

#endif
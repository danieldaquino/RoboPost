/*===============================

    I2C Module

	This module creates a higher level i2c interface, to be used with sensors.
	
	For more information, please refer to I2CModule.h
    
===============================*/

/*========
Includes
=========*/
#include <msp430.h> 
#include <stdint.h>
#include <stdbool.h>
#include "I2CModule.h"
#include "../ArrayUtils/ArrayUtils.h"

/*========
Static variables
=========*/

static char txDone = 0;								// Used to check whether the information was transmitted properly
static char rxDone = 0;								// Used to check whether the information was transmitted properly
static I2C_Mode MasterMode; 						// Used to track the state of the software state machine
static uint8_t TransmitRegAddr; 					// The Register Address/Command to use
static uint8_t ReceiveBuffer[MAX_BUFFER_SIZE]; 		// ReceiveBuffer: Buffer used to receive data in the ISR
static uint8_t RXByteCtr; 							// RXByteCtr: Number of bytes left to receive
static uint8_t ReceiveIndex; 						// ReceiveIndex: The index of the next byte to be received in ReceiveBuffer
static uint8_t TransmitBuffer[MAX_BUFFER_SIZE]; 	// TransmitBuffer: Buffer used to transmit data in the ISR
static uint8_t TXByteCtr; 							// TXByteCtr: Number of bytes left to transfer
static uint8_t TransmitIndex; 						// TransmitIndex: The index of the next byte to be transmitted in TransmitBuffer

/*========================
Static function Declarations
==========================*/

/*========
Function definitions
=========*/

//******************************************************************************
// High level Global functions *************************************************
//******************************************************************************

I2C_Mode I2CRead(uint8_t dev_addr, uint8_t reg_addr, uint8_t count, uint8_t * destination) {
    /* Initialize state machine */
    MasterMode = TX_REG_ADDRESS_MODE;
    TransmitRegAddr = reg_addr;
    RXByteCtr = count;
    TXByteCtr = 0;
    ReceiveIndex = 0;
    TransmitIndex = 0;

    /* Initialize slave address and interrupts */
    UCB0I2CSA = dev_addr;
    UCB0IFG &= ~(UCTXIFG + UCRXIFG);       // Clear any pending interrupts
    UCB0IE &= ~UCRXIE;                       // Disable RX interrupt
    UCB0IE |= UCTXIE;                        // Enable TX interrupt

    UCB0CTL1 |= UCTR + UCTXSTT;             // I2C TX, start condition
    // __bis_SR_register(LPM0_bits + GIE);              // Enter interrupts enable and turn off CPU
    rxDone = 0; // We are not done this operation
    __bis_SR_register(GIE);              // Enter interrupts enable and turn off CPU
	
	while(!rxDone) {
		// Wait
	}
	// rx is Done! let's get out
	CopyArray(ReceiveBuffer, destination, count);
    return MasterMode;
}

I2C_Mode I2CWrite(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint8_t count) {
    /* Initialize state machine */
    MasterMode = TX_REG_ADDRESS_MODE;
    TransmitRegAddr = reg_addr;

    //Copy register data to TransmitBuffer
    CopyArray(reg_data, TransmitBuffer, count);

    TXByteCtr = count;
    RXByteCtr = 0;
    ReceiveIndex = 0;
    TransmitIndex = 0;

    /* Initialize slave address and interrupts */
    UCB0I2CSA = dev_addr;
    UCB0IFG &= ~(UCTXIFG + UCRXIFG);       // Clear any pending interrupts
    UCB0IE &= ~UCRXIE;                       // Disable RX interrupt
    UCB0IE |= UCTXIE;                        // Enable TX interrupt

    UCB0CTL1 |= UCTR + UCTXSTT;             // I2C TX, start condition
    txDone = 0;
    __bis_SR_register(GIE);              // Enable interrupts
	// __bis_SR_register(LPM0_bits + GIE);              // Enter interrupts enable and turn off CPU


    while(!txDone) {
		// Keep waiting
	}
	
    return MasterMode;
}

//******************************************************************************
// Device Initialization *******************************************************
//******************************************************************************

void I2CInit() {
	//Initialize variables to their initial values...
	MasterMode = IDLE_MODE;
	TransmitRegAddr = 0;
	ReceiveBuffer[0] = 0;
	RXByteCtr = 0;
	ReceiveIndex = 0;
	TransmitBuffer[0] = 0;
	TXByteCtr = 0;
	TransmitIndex = 0;
	
	//Initialize the Serial communication module
    UCB0CTL1 |= UCSWRST;                      // Enable SW reset
    UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
    UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
    UCB0BR0 = 160;                            // fSCL = SMCLK/160 = ~100kHz <-- SMCLK AT 16MHZ
    // UCB0BR0 = 10;                            // fSCL = SMCLK/10 = ~100kHz    <--  SMCLK AT 1MHZ
    UCB0BR1 = 0;
    UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
    UCB0IE |= UCNACKIE;
    
    //Initialize necessary GPIO for I2C
    //I2C Pins
    P3REN |= BIT0 | BIT1; // use internal pullup resistors
    P3OUT |= BIT0 | BIT1;
    P3SEL |= BIT0 | BIT1; // P3.0, P3.1 option select
}

//******************************************************************************
// I2C Interrupt ***************************************************************
//******************************************************************************

#pragma vector=USCI_B0_VECTOR
__interrupt void USCI_B0_ISR(void) {
  //Must read from UCB0RXBUF
  uint8_t rx_val = 0;

  switch(__even_in_range(UCB0IV,0xC))
  {
    case USCI_NONE:break;                             // Vector 0 - no interrupt
    case USCI_I2C_UCALIFG:break;                      // Interrupt Vector: I2C Mode: UCALIFG
    case USCI_I2C_UCNACKIFG:break;                    // Interrupt Vector: I2C Mode: UCNACKIFG
    case USCI_I2C_UCSTTIFG:break;                     // Interrupt Vector: I2C Mode: UCSTTIFG
    case USCI_I2C_UCSTPIFG:break;                     // Interrupt Vector: I2C Mode: UCSTPIFG
    case USCI_I2C_UCRXIFG:
        rx_val = UCB0RXBUF;
        if (RXByteCtr)
        {
          ReceiveBuffer[ReceiveIndex++] = rx_val;
          RXByteCtr--;
        }

        if (RXByteCtr == 1)
        {
          UCB0CTL1 |= UCTXSTP;
        }
        else if (RXByteCtr == 0)
        {
          UCB0IE &= ~UCRXIE;
          MasterMode = IDLE_MODE;
          rxDone = 1;
          // __bic_SR_register_on_exit(CPUOFF);      // Exit LPM0
        }
        break;                      // Interrupt Vector: I2C Mode: UCRXIFG
    case USCI_I2C_UCTXIFG:
        switch (MasterMode)
        {
          case TX_REG_ADDRESS_MODE:
              UCB0TXBUF = TransmitRegAddr;
              if (RXByteCtr)
                  MasterMode = SWITCH_TO_RX_MODE;   // Need to start receiving now
              else
                  MasterMode = TX_DATA_MODE;        // Continue to transmission with the data in Transmit Buffer
              break;

          case SWITCH_TO_RX_MODE:
              UCB0IE |= UCRXIE;              // Enable RX interrupt
              UCB0IE &= ~UCTXIE;             // Disable TX interrupt
              UCB0CTL1 &= ~UCTR;            // Switch to receiver
              MasterMode = RX_DATA_MODE;    // State state is to receive data
              UCB0CTL1 |= UCTXSTT;          // Send repeated start
              if (RXByteCtr == 1)
              {
                  //Must send stop since this is the N-1 byte
                  while((UCB0CTL1 & UCTXSTT));
                  UCB0CTL1 |= UCTXSTP;      // Send stop condition
              }
              break;

          case TX_DATA_MODE:
              if (TXByteCtr)
              {
                  UCB0TXBUF = TransmitBuffer[TransmitIndex++];
                  TXByteCtr--;
              }
              else
              {
                  //Done with transmission
                  UCB0CTL1 |= UCTXSTP;     // Send stop condition
                  MasterMode = IDLE_MODE;
                  UCB0IE &= ~UCTXIE;                       // disable TX interrupt
                  txDone = 1;
                  // __bic_SR_register_on_exit(CPUOFF);      // Exit LPM0
              }
              break;

          default:
              __no_operation();
              break;
        }
        break;                      // Interrupt Vector: I2C Mode: UCTXIFG
    default: break;
  }
}


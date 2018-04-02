// SPI-Slave.ino
// By Jeremy Ellis
// MODIFIED BY: Tim Yue
// MIT license
// Use at your own risk!?

    // MSP430F5529 to Photon SPI Setup
    // GND to GND
    // P6.5 to A2   SS
    // P4.3 to A3   SCK
    // P4.2 to A4   MISO
    // P4.1 to A5   MOSI

void slaveSelect(uint8_t state);
void slaveCallback();

const int SS_PIN = A2;
bool gotValue = false;
#define NUM_PARAM  10
uint32_t sendValues[NUM_VALUES];
uint32_t rcvdValues[NUM_VALUES];
unsigned char command[10];
void setup() {
      /*  sendValues[0] = 'A';
        sendValues[1] = 'B';
        sendValues[2] = 'C';
        sendValues[3] = 0x83;
        sendValues[4] = 0x3A3B3CAA;
        sendValues[5] = 'X';
        sendValues[6] = 'Y';
        sendValues[7] = 'Z';
        command[0]=0x01;
        command[1]=0x02;
        command[2]=0x03;
        command[3]=0x04;
        command[4]=0x05;
    */
    SPI.onSelect(slaveSelect);
    SPI.setBitOrder(MSBFIRST);
    SPI.begin(SPI_MODE_SLAVE, SS_PIN);
}

void loop() {
    //do work

    if (gotValue) {
 //transfer complete flag set do something if you need to

        gotValue = false;
        }
    }


void slaveSelect(uint8_t state) {
    if (state) {

        SPI.transfer(sendValues, rcvdValues, sizeof(uint32_t)*NUM_PARAM, slaveCallback);

    }
}

void slaveCallback() {
    gotValue = true;
}

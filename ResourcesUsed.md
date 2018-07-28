# Used Resources

This document describes used resources in various components used, to avoid conflicts during development.

Here is a comprehensive list of all utilized resources. Each module header also contains a list of their own utilized resources.

## In the MSP

### StartStop

1. P1.1
2. PORT1 ISR
3. TA0CCR1
4. TA0CCR2
5. TA2CCR1
6. TA2CCR2
7. P1.0

### UARTIO module

1. UCSI_A1
2. P4.4
3. P4.5

### DualMotorDriver module

1. Timer A0
1. Timer A2
2. P1.2 - Motor 1 Forward FPWM
3. P1.3 - Motor 1 Reverse FPWM
4. P2.4 - Motor 2 Forward FPWM
5. P2.5 - Motor 2 Reverse FPWM

### DualVelocityGauge module

1. P2.0 - Encoder of Motor 1, channel A
2. P2.2 - Encoder of Motor 2, channel A
3. PORT2 ISR
4. Timer A1

### I2CModule

1. UCB0 module
2. P3.0 – SDA
3. P3.1 - SCL

### Scheduler

1. Timer A1
2. P4.7 GREEN LED
3. P6.2 Computing Function Indicator.

### ucsiSpi

1. P4.1 MOSI
2. P4.2 MISO
3. P4.3 SCLK
4. P6.5 SS
5. UCSI B1

## In the Photon

### SPI

1. MOSI --> A5
2. MISO --> A4
3. SCLK --> A3
4. SS --> A2

### TCPServer

1. Port 23

## In the Node Server

1. Port 3000
![RoboPostLogo](logo.png)
### By Daniel Walnut and Tim Yue
An autonomous delivery system — BCIT Robotics Capstone

# Components

1. MSP4305529LP Evaluation Board
2. Particle Photon
3. TI DRV8871 Adafruit Breakout Board
4. DC Motor with an encoder

# Used Resources

## In the MSP

### UARTIO module

1. UCSI_A1
2. P4.4
3. P4.5

### DualMotorDriver module

1. Timer A0
2. P1.2 - Motor 1 Forward PWM
3. P1.3 - Motor 1 Reverse PWM
4. P1.4 - Motor 2 Forward PWM
5. P1.5 - Motor 2 Reverse PWM

### DualVelocityGauge module

1. P2.0 - Encoder of Motor 1, channel A
2. P2.2 - Encoder of Motor 2, channel A
3. PORT2 ISR
4. Timer A1
/*
 * I2CPhotonDriver
 * this file does the following:
 * -connect with photon
 * -receive from photon to usable data
 * must have I2C_modual.c and .h in project
 * for resources used and guides refer to I2C_modual.h
 *
 */
#ifndef photonDriver_H_
#define photonDriver_H_

/*
 * initialize photon,
 * return 1 if successfully communicated with photon
 * else
 * return 0
 */

//defines
#define PHOTON_ADDR     0x10

unsigned char photoninit();

char photon_read(char addr,char length);








#endif

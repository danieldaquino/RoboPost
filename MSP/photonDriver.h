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

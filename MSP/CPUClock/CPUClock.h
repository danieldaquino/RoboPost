/*===============================

	# CPUClock
	
	This module allows you to increase the CPU rate to 16MHz, automatically increase Vcore.
	
	Module code forked from a Texas Instruments code example.
	
	## Resources used:	
	
	1. Power Management Module
	2. Supply Voltage Supervisor
	3. MCLK
	4. Unified Clock System
	5. SMCLK
			
===============================*/

#ifndef CPU_CLOCK_H
#define CPU_CLOCK_H

/*=======
Function Prototypes
========*/

/*======
~~boostClockTo16MHz~~

Safely boosts the CPU clock rate to 16MHz.

inputs: none
outputs: none
Globals affected: Power Management Module, Supply Voltage Supervisor, MCLK, Unified Clock System, SMCLK

======*/
void boostClockTo16MHz();

#endif
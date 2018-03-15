/*===============================

    Array Utils

    this C module provides useful functions for manipulating arrays.
    
    For more information, please visit Array Utils.
	
===============================*/
/*========
Includes
=========*/
#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>
#include "ArrayUtils.h"

void CopyArray(uint8_t *source, uint8_t *dest, uint8_t count) {
    uint8_t copyIndex = 0;
    for (copyIndex = 0; copyIndex < count; copyIndex++)
    {
        dest[copyIndex] = source[copyIndex];
    }
}


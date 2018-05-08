/*===============================

    Array Utils

    this C module provides useful functions for manipulating arrays.

    Forked from Tim Yue. Modified by Daniel Walnut

    Resources used:
	
	none
	
===============================*/
#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

/*=========
Includes
=========*/
#include <stdint.h>

/*=========
Function prototypes
=========*/

/*=================================
 * CopyArray
 *
 * copies whats in receive buffer to another array
 *
 * input:   Pointer to source array(receive buffer)
 *          Pointer to array you want
 *          how many data you want
 * output:  data from source to dest
===================================*/
void CopyArray(uint8_t *source, uint8_t *dest, uint8_t count);

#endif

#!/bin/bash

echo "Removing bin file"
rm pwmled.bin
echo "Cleaning compiled files"
make clean
echo "Compiling..."
make
echo "Making flashable file..."
binmake pwmled.out pwmled.bin

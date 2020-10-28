#!/bin/bash
./genInput > input
cat input 
time ./bg_1 < input > output
cat output

#rm input

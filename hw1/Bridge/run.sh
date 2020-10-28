#!/bin/bash

./genInput > input
cat input
time ./bridge_1 < input > output
cat output
#rm input

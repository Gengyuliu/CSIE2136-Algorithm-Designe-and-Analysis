./genInput > input
cat input 
time ./td_0 < input > output
cat output
time ./td_2 < input >output
cat output
rm input output

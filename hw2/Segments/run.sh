./genInput > input
cat input 
time ./seg_1 < input > output
cat output
rm input output

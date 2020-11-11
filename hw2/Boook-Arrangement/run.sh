./genInput > input
cat input
time ./bka < input > output 
head -2 output
#time ./bka_test < input
#cat output
rm input output

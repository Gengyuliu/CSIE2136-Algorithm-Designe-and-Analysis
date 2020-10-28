./genInput > input
cat input
#echo "ada_0 brute force"
#time ./ada_0 < input
echo "ada_1 DC"
time ./ada_1 < input


rm input

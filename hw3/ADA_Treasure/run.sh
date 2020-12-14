./genInput > input
cat input
time ./ada_treasure < input > output
cat output
time ./p1 < input > output
cat output

rm input output

#!/bin/sh
cd ../q2
make
./TreeSearch ../tests/t1/num1.txt ../tests/t1/query1.txt > out1.txt
o=$(head -1 out1.txt | grep "^A2a:5,")
if [ -z $o ]
then
    echo "Test1 failed"
else
    echo "Test1 passed"
fi

./TreeSearch ../tests/t2/num2.txt ../tests/t2/query2.txt > out2.txt
o=$(head -1 out2.txt | grep "^A2a:68," )
if [ -z $o ]
then
    echo "Test2 failed"
else
    echo "Test2 passed"
fi

./TreeSearch ../tests/t3/num3.txt ../tests/t3/query3.txt > out3.txt
o=$(head -1 out3.txt | grep "^A2a:277,")
if [ -z $o ]
then
    echo "Test3 failed"
else
    echo "Test3 passed"
fi

rm out1.txt out2.txt out3.txt
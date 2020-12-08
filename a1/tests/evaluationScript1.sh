#!/bin/sh
cd ../q1
make
cat ../tests/t1/expr1.txt | ./ExprTree > out1.txt

d1=$(diff ../tests/t1/q1o1.txt out1.txt -qZB)
if [ -z "$d1" ]
then 
    echo "Test1 passed"
else
    echo "Test1 failed"
fi

cat ../tests/t2/expr2.txt | ./ExprTree > out2.txt
d1=$(diff ../tests/t2/q1o2.txt out2.txt -qZB)
if [ -z "$d1" ]
then 
    echo "Test2 passed"
else
    echo "Test2 failed"
fi

cat ../tests/t3/expr3.txt | ./ExprTree > out3.txt
d1=$(diff ../tests/t3/q1o3.txt out3.txt -qZB)
if [ -z "$d1" ]
then 
    echo "Test3 passed"
else
    echo "Test3 failed"
fi

rm out1.txt out2.txt out3.txt
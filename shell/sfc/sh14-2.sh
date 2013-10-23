#!/bin/bash
# Program:
#	Calculate the result of "1+2+3+...+100"
# History:
# 2013/10/23	tom	First release

i=0
s=0

while [ $i -lt 100 ]
do
	i=$((i+1))
	s=$((s+i))
done

echo "The result of '1+2+3+...+100' is ==> $s"

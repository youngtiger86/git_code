#!/bin/bash
# Program:
#	Try do calculate 1+2+..+${yourinput}
# History:
# 2013/10/23	tom	First release

read -p "Please input a number, I will count for 1+2+...+your_input: " nu

s=0
for ((i=1; i<=$nu; i=i+1))
do
	s=$(($s+$i))
done
echo "The result of '1+2+3+...+$nu' is ==> $s"

#!/bin/bash
# Program:
#	Use loop to calculate "1+2+3+...+100" result.
# History:
# 2013/10/23	tom	First release

i=0
s=0

while [ "$i" != "100" ]
do
	i=$((i+1))
	s=$((i+s))
done

echo "The result of '1+2+3+...+100' is ==> $s"

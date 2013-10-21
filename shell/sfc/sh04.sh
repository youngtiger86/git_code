#!/bin/bash
# Program:
#	User input 2 integer numbers. Program will cross these two numbers.
# History:
# 2013/10/21	tom	First release

echo -e "You SHOULD input 2 numbers, I will cross them!\n"
read -p "first number: " firstnum
read -p "second number: " secondnum
total=$(($firstnum * $secondnum))
echo -e "\nThe result of $firstnum * $secondnum is ==> $total"

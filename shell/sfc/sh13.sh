#!/bin/bash
# Program:
#	Repeat question until user input correct answer.
# History:
# 2013/10/22	tom	First release

while [ "$yn" != "yes" -a "$yn" != "YES" ]
do
	read -p "Please input yes/YES to stop this program: " yn
done

echo "OK! You input the correct answer."

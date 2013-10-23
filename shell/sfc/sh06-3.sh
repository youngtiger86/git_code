#!/bin/bash
# Program:
#	This program shows the user's choice.
# History:
# 2013/10/21	tom	First release

read -p "Please input (Y/N):" yn
if [ "$yn" == "y" ] || [ "$yn" == "Y" ];then
	echo "OK, continue"
	exit 0
elif [ "$yn" == "n" ] || [ "$yn" == "N" ];then
	echo "Oh, interrupt!"
	exit 0
else
	echo "I don't know what your choice is."
fi

#!/bin/bash
# Program:
#	This program shows the user's choice.
# History:
# 2013/10/21	tom	First release

read -p "Please input (Y/N):" yn
if [ "$yn" == "y" ] || [ "$yn" == "Y" ];then
	echo "OK, continue."
	exit 0
fi
if [ "$yn" == "n" ] || [ "$yn" == "N" ];then
	echo "Oh, interrupt!."
	exit 0
fi

echo "I don't know what your choice is." && exit 0

#!/bin/bash
# Program:
#	This program shows the user's choice.
# History:
# 2013/10/21	tom	First release

read -p "Please input (Y/N):" yn
[ "$yn" == "y" ] || [ "$yn" == "Y" ] && echo "OK, continue" && exit 0
[ "$yn" == "n" ] || [ "$yn" == "N" ] && echo "Oh, interrupt!" && exit 0
echo "I don't know what your choice is" && exit 0


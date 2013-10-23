#!/bin/bash
# Program:
#	This script only accepts the following parameter: one two or three.
# History:
# 2013/10/22	tom	First release

echo "This program will print your selection!"
case $1 in
	"one")
		echo "Your choice is ONE."
		;;
	"two")
		echo "Your choice is TWO."
		;;
	"three")
		echo "Your choice is THREE."
		;;
	*)
		echo "Usage: $0 {one|two|three}"
		;;
esac

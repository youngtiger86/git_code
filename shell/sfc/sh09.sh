#!/bin/bash
# Program:
#	Check $1 is equal to "hello"
# History:
# 2013/10/21	tom	First release

if [ "$1" == "hello" ];then
	echo "Hello, how are you?"
	exit 0
elif [ "$1" == "" ];then
	echo "You MUST input parameter, ex> ($0 someword)"
else
	echo "The only parameter is "hello", ex> ($0 hello)"
fi

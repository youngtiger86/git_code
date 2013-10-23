#!/bin/bash
# Program:
#	Show "Hello" from $1... by using case ... case.
# History:
# 2013/10/22	tom	First release

case $1 in
	"hello")
		echo "Hello, how are you?"
		;;
	"")
		echo "You MUST input parameters, ex> ($0 someword)"
		;;
	*)
		echo "Usage: $0 {hello}"
		;;
esac

#!/bin/bash
# Program:
#	Create a shell script with unified head.
# History:
# 2013/10/20	Tom	First release

function print_usage()
{
	echo "Usage:"
	echo "    ./init.sh filename [filename2 ...]"
}

if [ $# -lt 1 ];then
	echo "Name(s) of file should be specified."
	print_usage
	exit 1
elif [ $# -gt 5 ];then
	echo "At most 5 files can be create by one shot."
	exit 1
fi

filenum=$#
filenames=$@
echo "filenum: $filenum, file names: $filenames"



#!/bin/bash

mk_opt=
target_list="common client server webserver"

function make_main
{
	cd ${CODE_HOME}
	src_full_path=`pwd`/src

	for target in ${target_list}
	do
		target_src_path=${src_full_path}/${target}
		echo "Enter directory ${target_src_path}..."
		cd ${target_src_path}
		make ${mk_opt}
		echo "Leaving directory ${target_src_path}" 
	done
}

if [ $# -eq 1 ];then
	mk_opt=$1
elif [ $# -gt 1 ];then
	echo "Parameter number is wrong."
	exit 1
fi

make_main 

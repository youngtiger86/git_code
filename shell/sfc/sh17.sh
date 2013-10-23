#!/bin/bash
# Program:
#	Use ping command to check the network's PC state.
# History:
# 2013/10/23	tom	First release

network="192.168.1"

for sitenu in $(seq 1 100)
do
	ping -c 1 -w 1 ${network}.${sitenu} &> /dev/null && return=0 || return=1
	if [ "$result" == 0 ];then
		echo "Server ${network}.${sitenu} is UP."
	else
		echo "Server ${network}.${sitenu} is DOWN."
	fi
done

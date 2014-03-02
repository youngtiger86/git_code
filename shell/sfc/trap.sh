#!/bin/bash
# Program:
#	Show how to catch and handle a signal.
# History:
# 2013/10/27	tom	First release

function handler()
{
		echo "Before I was killed, I want to say 'Hello, world!'"
}

echo My process id is $$

trap 'handler' SIGINT

while true;
do
	sleep 1
	echo "Kill me!"
done

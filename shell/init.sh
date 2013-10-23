#!/bin/bash
# Program:
#	Create a shell script with unified head.
# History:
# 2013/10/20	Tom	First release

function print_usage()
{
	echo "Usage:"
	echo -e "\t./init.sh filename [filename2 ...]"
}

function create_file()
{
	if [ $# -ne 1 ];then
		echo "Parameter number is wrong."
		return 1
	fi

	filename=$1
	echo "Creating file ${filename}..."
	echo "#!/bin/bash" > ${filename}
	echo "# Program:" >> ${filename}
	echo "#" >> ${filename}
	echo "# History:" >> ${filename}
	echo "# `date +%Y/%m/%d`	`whoami`	First release" >> ${filename}
	echo "File ${filename} created successfully."
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

for file in $filenames
do
	# Check if the file exists already.
	if [ -f ${file} ];then
		echo "Warning: file ${file} has already exist. Replacing it?(y/n)"
		read replace
		if [ "X$replace" == "Xy" -o "X$replace" == "XY" ];then
			echo "Files ${file} is replaced."
		else
			echo "Info: file ${file} is not created for file with the same name exists."
			continue
		fi
	fi

	create_file ${file}
	chmod u+x ${file}
done



#!/bin/bash

if [ $# -eq 2 ];then
	OS="${2}"
elif [ $# -eq 1 ];then
	OS=" "	
else
	echo "Too many arguments!"
	exit 1
fi	

#Check if the first parameter is matching this regex 
grep -qE '^[-+]?[0-9]+$' <(echo "${1}")
#This if checks the exit status from the privous command if 0 then numb is int

if [ ! $? -eq 0 ];then
	echo "Not an integer number!"
	exit 2 
fi

NUMBER=$(echo "${1}" | grep -o '.' )
SIGN=$(echo "${NUMBER}" | head -1)

FLAG=0

#checks if there is sign 
egrep -q [-+] <(echo "${SIGN}")

if [ $? -eq 0 ]; then # we have to take the number from the second symbol 
	NUMBER=$(echo "${NUMBER}" | tail -n +2)
	FLAG=1
fi

#check for the sign 
[ "${FLAG}" -eq 1 ] && echo -n "${SIGN}" 
#this means that the sign will be printed on the same line with the next command 

echo "${NUMBER}" | tac | xargs -n3 | tr -d " "| tr "\n" "${OS}" | grep -o '.' | tac | tail -n +2 | tr -d "\n";echo

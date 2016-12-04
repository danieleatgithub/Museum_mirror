#!/bin/bash

case "$1" in
    0b*)		ibase=2;;	# binary
    0x*|[a-f]*|[A-F]*)	ibase=16;;	# hexadecimal
    0*)			ibase=8;;	# octal
    [1-9]*)		ibase=10;;	# decimal
    *)
	echo "illegal port $i"
	exit 1;;
esac
port=$(echo $1 | sed -e 's:^0[bBxX]::' | tr '[a-f]' '[A-F]')
decport=`echo "ibase=$ibase; $port" | bc`  
case "$decport" in
    [0-9]*)	;;			 # number ok
    *)		
	echo "illegal port $i"
	exit 1;;		 # error: ignore
esac


#val=$(dd if=/dev/port status=noxfer bs=1 count=1 skip=$decport  2> /dev/null | od -tx1 -An | sed -e 's/ //')
val=$(dd if=/dev/port status=noxfer bs=1 count=1 skip=$decport  2> /dev/null | od -td1 -An | sed -e 's/ //')

echo -n "$1 "
echo `bc <<!
    obase=16; "0x"; $val
    obase=10; " 0d"; $val
    obase=2;  " "; $val
!`


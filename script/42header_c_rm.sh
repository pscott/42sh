#!/bin/sh

while test ${#} -gt 0
do
	line="$(head -n 1 $1)"
	short=${line:0:4}
	if [ "$short" = "/* *" ]; then
		sed -i".bak" '1,12d' $1
		echo deleted header in $1
		rm $1.bak
		shift 1
	else
		echo no header found in $1
		shift 1
fi
done

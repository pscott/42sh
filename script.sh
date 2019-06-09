#!/bin/sh

while [ $? != 11 ]
do
	cat /dev/random | head -c 1000 > tmp ; cat tmp | ./42sh
done

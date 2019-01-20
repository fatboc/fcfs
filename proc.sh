#!/bin/bash

if [ ! -e proc.txt ] ; then
	touch proc.txt
fi

if [ ! -r proc.txt ] ; then
	(>&2 echo "Brak prawa do odczytu pliku 'proc.txt'")
	exit -1
fi


ps -eo pid,uid,time,s,ppid,comm,etimes | grep -v 00:00:00 > proc.txt

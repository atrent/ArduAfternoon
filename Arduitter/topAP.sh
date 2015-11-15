#!/bin/bash

WIFI="ArduinoAfternoon"
LIMIT="10"

muovi(){
 # direzione random (rotate gradi)
 # forward 1
 # $RANDOM
}

scan()
{
 sudo iwlist wlan0 scanning 2>/dev/null|egrep 'Address|ESSID|level|Frequency|Encryp'|tr -s ' '|tr -d '\n'|sed 's/Cell/\nCell/g'|sed 's/level=//g'|sort -t ' ' -k 12 -rn|grep -v '^$' | sed '1d' | grep -i $1
}

#echo wlan0:
previous="100" 
echo prev: $previous

while true
do
	if [ $previous -le $LIMIT ]
	then
		echo girotondo
		echo $previous
		echo $LIMIT
		sleep 1
	else
		echo not yet
		echo $previous
		echo $LIMIT
		curr="0$(scan $WIFI | head -n 1 | cut -d " " -f 12 | tr -d '-')"
		if [ $curr -gt $previous ]
		then
			# ci stiamo allontanando ergo back
			echo backward 1
		else
			# ci stiamo avvicinando
			echo muovi
		fi
		previous=$curr
	fi
done

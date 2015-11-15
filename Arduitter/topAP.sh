#!/bin/bash

WIFI="ArduinoAfternoon"
LIMIT="40"

muovi(){
 echo in muovi
 # direzione random (rotate gradi)
 # forward 1
 let RND=$RANDOM%2
 echo random: $RND
	if [ $RND -eq 1 ]
	then
		curl http://localhost/arduino/rotateleft/1
	else
		curl http://localhost/arduino/rotateright/1
	fi
	sleep 1
	curl http://localhost/arduino/backward/1
}

scan()
{
 iwlist wlan0 scanning 2>/dev/null|egrep 'Address|ESSID|level|Frequency|Encryp'|tr -s ' '|tr -d '\n'|sed 's/Cell/\nCell/g'|sed 's/level=//g'|sort -t ' ' -k 12 -rn|grep -v '^$' | sed '1d' | grep -i $1
}

#echo wlan0:
previous="100" 
#echo prev: $previous

while true
do
	curr="0$(scan $WIFI | head -n 1 | cut -d " " -f 12 | tr -d '-')"
		
	if [ $previous -le $LIMIT ]
	then
		echo girotondo
		curl http://localhost/arduino/rotateleft/4
		curl http://localhost/arduino/rotateright/4
		echo previous: $previous
		#echo $LIMIT
		sleep 1
	else
		echo not yet
		echo previous: $previous
		#echo $LIMIT
		
		if [ $curr -eq 0 ]
		then
		 continue
		fi
		
		if [ $curr -gt $previous ]
		then
			# ci stiamo allontanando ergo back
			echo backward 1
			curl http://localhost/arduino/forward/1
		else
			# ci stiamo avvicinando
			echo muovi
			
			muovi
		fi
	fi
	previous=$curr
done

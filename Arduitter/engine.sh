#!/bin/sh

cd $(dirname $0)

# da lanciare ogni poco piu' di un minuto (causa API twitter)

#TODOFILE=todo.tweets
DONEFILE=done.tweets
HOST=localhost

touch $DONEFILE  # ne assicuro l'esistenza, attenzione che deve essere NON vuoto altrimenti grep fallisce!

# TODO: ripulire meglio grep in caso di < > etc.

echo '/search #arduittercommand' | ./ttytter -script | while
 read raw_tweet
do
 tweet=$(echo $raw_tweet|tr "<" "@"|tr ">" "@")
 #echo ===
 #echo searching $tweet
  
 if
    grep "$tweet" $DONEFILE  # se e' gia' stato fatto non farlo (pero' urge ogni tanto svuotare DONEFILE)
 then
	echo NOT doing... $tweet
 else
	# TODO: check validita' comando
		echo doing... $tweet
		
		echo $(date +%Y%m%d%H%M%S) $tweet >> $DONEFILE
		
		COMMAND=$(echo $tweet| sed -n -e 's/^.*#arduittercommand //p'|tr [:upper:] [:lower:] | tr -s " " "/")
	if
		grep -q $(echo $COMMAND|cut -f1 -d/) << HERE
		forward
		backward
		leftwheelforward
		leftwheelbackward
		rightwheelforward
		rightwheelbackward
HERE
	then
		curl http://$HOST/arduino/$COMMAND/EOC
		# TODO: feedback su twitter (ho eseguito i comandi di ....)
	else
		echo COMANDO NON PERMESSO
	fi
 fi
done

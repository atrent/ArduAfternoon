#!/bin/sh

cd $(dirname $0)

# da lanciare ogni poco piu' di un minuto (causa API twitter)

#TODOFILE=todo.tweets
DONEFILE=done.tweets
HOST=localhost

touch $DONEFILE  # ne assicuro l'esistenza, attenzione che deve essere NON vuoto altrimenti grep fallisce!

echo '/search #arduittercommand' | ./ttytter -script | while
 read tweet
do
 if
        ! grep -qe "$tweet" $DONEFILE  # se e' gia' stato fatto non farlo (pero' urge ogni tanto svuotare DONEFILE)
 then
	# TODO: check validita' comando
		echo doing... $tweet
		echo $tweet >> $DONEFILE
		COMMAND=$(echo $tweet| sed -n -e 's/^.*#arduittercommand //p'|tr [:upper:] [:lower:] | tr -d " ")
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
	else
		echo COMANDO NON PERMESSO
	fi
 else
	echo NOT doing... $tweet
 fi
done

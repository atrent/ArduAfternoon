#!/bin/sh

# da lanciare ogni poco piu' di un minuto (causa API twitter)

#TODOFILE=todo.tweets
DONEFILE=done.tweets
HOST=localhost

touch $DONEFILE  # ne assicuro l'esistenza, attenzione che deve essere NON vuoto altrimenti grep fallisce!

echo '/search #arduittercommand' | ./ttytter -script | while
 read tweet
do
 if
        grep -qv "$tweet" $DONEFILE  # se e' gia' stato fatto non farlo (pero' urge ogni tanto svuotare DONEFILE)
 then
	# TODO: check validita' comando
        echo doing... $tweet
        echo $tweet >> $DONEFILE
        COMMAND=$(echo $tweet| sed -n -e 's/^.*#arduittercommand //p'|tr [:upper:] [:lower:])
        echo curl http://$HOST/arduino/$COMMAND
 else
        echo NOT doing... $tweet
 fi
done

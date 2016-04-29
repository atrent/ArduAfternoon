#!/bin/bash

set -o verbose  # solo per debug

# "source" di un file config (parametri di avvio)
CFG=$(hostname).cfg
if
 test -f $CFG
then
 . $(pwd)/$CFG
 echo $CFG config used
else
 . $(pwd)/mesh.cfg
 echo Default mesh.cfg used
fi


#### modprobe IF moduli kernel non vengono caricati al boot
#### Controllare con "sudo batctl -v"
#### modprobe batman-adv


# Selezione Wlan (o usiamo CFG?)
#if
# [ $(ip a | grep -wc 'wlan[0-9]:') -eq 1 ]
#then 
#	WLAN=$(ip a | grep -w 'wlan[0-9]:' | tr -s ' ' ' ' | cut -d' ' -f 2 | cut -d':' -f 1)
#	echo $WLAN
#else
	## Aggiungere codice scelta
#fi


##################################################################################
if
 ip a | grep -iq '$BAT'
then
	ip link set $BAT down
	ip link set $WLAN down
	batctl if del $WLAN
fi

sleep $SLEEP
ip link set $WLAN mtu 1528

#### iwconfig wlan0 mode ad-hoc #####
 iw $WLAN set type ibss


####iwconfig $WLAN channel 1
#### iwconfig $WLAN enc off
#### iwconfig $WLAN essid $MESH_NAME #####
#### iw $WLAN connect $MESH_NAME
#### No encryption
 iw dev $WLAN set channel 1
 iw dev $WLAN connect $MESH_NAME
##################################################################################

##################################################################################
 batctl if add $WLAN
 batctl if
##################################################################################

#### TODO provare a modificare le sleep

##################################################################################
#####ifconfig $WLAN up
ip link set $WLAN up

sleep $SLEEP

####ifconfig bat0 up
ip link set $WLAN up

sleep $SLEEP

batctl o
batctl gw_mode client
######dhclient -v $BAT &	DA MODIFICARE
batctl o
##################################################################################

#!/bin/bash

#set -o verbose  # solo per debug


echo CFG file
# "source" di un file config (parametri di avvio)
CFG=$(hostname).cfg
if
 test -f $CFG
then
 . $(dirname $0)/$CFG
 echo $CFG config used
else
 . $(dirname $0)/mesh.cfg
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

echo GREP bat
ip link set $WLAN down
if
 ip a | grep -iq "$BAT:"
then
	# se c'e' lo cancella
	ip link set $BAT down
	batctl if del $WLAN
fi

sleep $SLEEP
echo LINK SET
ip link set $WLAN mtu 1528

echo SET TYPE
#### iwconfig wlan0 mode ad-hoc #####

iw $WLAN set type ibss
ip link set $WLAN up

####iwconfig $WLAN channel 1
#### iwconfig $WLAN enc off
#### iwconfig $WLAN essid $MESH_NAME #####
#### iw $WLAN connect $MESH_NAME
#### No encryption
iw dev $WLAN set channel 1
iw dev $WLAN connect $MESH_NAME
ip link set $WLAN up

echo LINK CHANNEL
##################################################################################

##################################################################################
batctl if add $WLAN
batctl if
##################################################################################

#### TODO provare a modificare le sleep

##################################################################################
#####ifconfig $WLAN up
#ip link set $WLAN up

sleep $SLEEP

####ifconfig bat0 up
ip link set $BAT up

sleep $SLEEP

#batctl o
batctl gw_mode client
#avahi-autoipd --no-drop-root bat0 &
#dhclient -v $BAT &	#DA MODIFICARE
batctl o
##################################################################################

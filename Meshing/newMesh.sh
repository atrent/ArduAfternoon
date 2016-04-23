#!/bin/bash

#set -o verbose  # solo per debug

# "source" di un file config (parametri di avvio)
CFG=$(hostname).cfg
if
 test -f $CFG
then
 . $CFG
 echo $CFG config used
else
 . mesh.cfg
 echo Default mesh.cfg used
fi


#if [ $# -lt 1 ]
#then
#	echo "Inserire l'ultimo ottetto dell'indirizzo IP"
#	exit 1
#fi

#### modprobe IF moduli kernel non vengono caricati al boot
#### Controllare con "sudo batctl -v"
#### modprobe batman-adv

#### ifconfig sarebbe obsoleto... TODO: aggiornare a ip

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
#if
# ip a | grep -iq '$BAT'
#then
#	ip link set $BAT down
#	ip link set $WLAN down
#	batctl if del $WLAN
#fi
##################################################################################

#### iwconfig sarebbe obsoleto... TODO: aggiornare a iw

##################################################################################
#sleep $SLEEP
#ip link set $WLAN mtu 1528

##### iwconfig wlan0 mode ad-hoc #####
#iw $WLAN set type ibss

#iwconfig $WLAN channel 1
#iwconfig $WLAN enc off

##### iwconfig $WLAN essid $MESH_NAME #####
#iw $WLAN connect $MESH_NAME
##################################################################################

#ip link set up dev $WLAN
#ip link set mtu 1532 dev $WLAN

#iwconfig $WLAN mode ad-hoc essid $MESH_NAME ap $MAC channel 1
#iwconfig $WLAN mode ad-hoc essid $MESH_NAME ap  $MAC channel 1
#iwconfig $WLAN mode ad-hoc essid $MESH_NAME any channel 1

##################################################################################
#batctl if add $WLAN
#batctl if
##################################################################################

#### TODO provare a modificare le sleep

##################################################################################
#ifconfig $WLAN up
#sleep $SLEEP
#ifconfig bat0 up
#sleep $SLEEP
##################################################################################

# Al posto di <IP> aggiungere l'indirizzo
#ifconfig bat0 $IP_WLAN.$IP netmask 255.255.255.0 up

#ip link set up dev $WLAN
#ip link set up dev $BAT

#avahi-autoipd --no-drop-root $BAT &
##avahi-autoipd --debug $BAT &

##################################################################################
#batctl o
#batctl gw_mode client
#######dhclient -v $BAT &
#batctl o
##################################################################################

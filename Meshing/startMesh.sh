#!/bin/bash
set -o verbose

#### Inserire l'interfaccia corretta
#### TODO
#### Si potrebbe fare uno script dove si inserisce l'interfaccia
#### quando si esegue lo script (controllando la correttezza)

WLAN=wlan0		## Interfaccia WLAN
NOME_RETE=super_mesh	## Nome Rete
IP_WLAN=192.168.2.

if [ $# -lt 1 ]
then
	echo "Inserire l'ultimo ottetto dell'indirizzo IP"
	exit 1
fi

IP=$1

#### modprobe IF moduli kernel non vengono caricati al boot
#### Controllare con "sudo batctl -v"
#### modprobe batman-adv

#### ifconfig sarebbe obsoleto... TODO: aggiornare a ip
ifconfig bat0 down
ifconfig $WLAN down
batctl if del $WLAN

sleep 3

ifconfig $WLAN mtu 1528

#### iwconfig sarebbe obsoleto... TODO: aggiornare a iw
iwconfig $WLAN mode ad-hoc
iwconfig $WLAN channel 1
iwconfig $WLAN enc off
iwconfig $WLAN essid $NOME_RETE

#ip link set up dev $WLAN
#ip link set mtu 1532 dev $WLAN

#iwconfig $WLAN mode ad-hoc essid my-mesh-network ap 84:c9:b2:72:f1:08 channel 1
#iwconfig $WLAN mode ad-hoc essid my-mesh-network ap  02:12:34:56:78:9A channel 1
#iwconfig $WLAN mode ad-hoc essid my-mesh-network any channel 1

batctl if add $WLAN
batctl if

#### TODO provare a modificare le sleep

ifconfig $WLAN up
sleep 3
ifconfig bat0 up
sleep 3

# Al posto di <IP> aggiungere l'indirizzo
#ifconfig bat0 192.168.2.$IP netmask 255.255.255.0 up

#ip link set up dev $WLAN
#ip link set up dev bat0

#avahi-autoipd --no-drop-root bat0 &
##avahi-autoipd --debug bat0 &

batctl o
batctl gw_mode client
#dhclient -v bat0 &
batctl o

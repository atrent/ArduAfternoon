#!/bin/bash
set -o verbose

#### Inserire l'interfaccia corretta
#### TODO
#### Si potrebbe fare uno script dove si inserisce l'interfaccia
#### quando si esegue lo script (controllando la correttezza)

WLAN=wlan1

#### modprobe IF moduli kernel non vengono caricati al boot
#### Controllare con "sudo batctl -v"
#### modprobe batman-adv

#### ifconfig sarebbe obsoleto... TODO: aggiornare a ip
ifconfig bat0 down
ifconfig $WLAN down

ifconfig $WLAN mtu 1528

#### iwconfig sarebbe obsoleto... TODO: aggiornare a iw
iwconfig $WLAN mode ad-hoc
iwconfig $WLAN channel 1
iwconfig $WLAN enc off
iwconfig $WLAN essid prova_mesh

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
ifconfig bat0 192.168.2."<IP>" netmask 255.255.255.0 up

#ip link set up dev $WLAN

#ip link set up dev bat0

#avahi-autoipd bat0

batctl o

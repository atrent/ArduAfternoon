#!/bin/bash
set -o verbose

WLAN=wlp0s29u1u3

modprobe batman-adv

ifdown bat0
ifdown $WLAN

ifconfig $WLAN mtu 1528

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

ifconfig $WLAN up 
ifconfig bat0 up 
ifconfig bat0 192.168.2.41 netmask 255.255.255.0 up

#ip link set up dev $WLAN

#ip link set up dev bat0

#sudo avahi-autoipd bat0

batctl o

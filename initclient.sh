sudo ifconfig tun0 10.4.2.99/24 up
sudo route add -net 192.168.60.0/24 tun0

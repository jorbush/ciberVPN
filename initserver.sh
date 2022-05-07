sudo ifconfig tun0 10.4.2.5/24 up
sudo sysctl net.ipv4.ip_forward=1
sudo route del -net 10.4.2.0/24 tun0
sudo route add -net 10.4.2.0/24 tun0

close_all(){
    byobu send-keys -t l25gc:$1 C-c
    byobu send-keys -t l25gc:$1 C-c
    byobu send-keys -t l25gc:$1 C-c
}

pidof smf | xargs sudo kill -9

close_all 1.0
close_all 1.0
close_all 1.0

close_all 1.1
close_all 1.1
close_all 1.2
close_all 1.2
close_all 1.3
close_all 1.3

close_all 0.0
close_all 0.1
close_all 0.2
close_all 0.3
close_all 0.4
close_all 0.5
close_all 0.6
close_all 0.7

mongo --eval "db.dropDatabase()" free5gc
mongo --eval "db.dropDatabase()" free5gc
mongo --eval "db.dropDatabase()" free5gc

byobu send-keys -t l25gc:1.0 "cd /root/PANDA_5G/HOME/onvm-upf/onvm" C-m
#byobu send-keys -t l25gc:1.0  "./go.sh -k 0 -n 0xF0 -m 1,2,3 -a 0x7f000000000 -s stdout" C-m
byobu send-keys -t l25gc:1.0  "./go.sh -k 0 -n 0xFF0 -m 1,2,3 -a 0x7f000000000 -s stdout" C-m

sleep 10

byobu send-keys -t l25gc:1.3 "cd /root/PANDA_5G/HOME/onvm-upf/5gc/upf_u_complete" C-m
byobu send-keys -t l25gc:1.3 "make" C-m
byobu send-keys -t l25gc:1.3 "./go.sh 1" C-m

sleep 2


byobu send-keys -t l25gc:1.2 "cd /root/PANDA_5G/HOME/onvm-upf/5gc/upf_c_complete" C-m
byobu send-keys -t l25gc:1.2 "make" C-m
byobu send-keys -t l25gc:1.2 "./go.sh 2" C-m

sleep 1


byobu send-keys -t l25gc:0.0 "cd /root/PANDA_5G/HOME/onvm-free5gc3.0.5/bin" C-m
byobu send-keys -t l25gc:0.1 "cd /root/PANDA_5G/HOME/onvm-free5gc3.0.5/bin" C-m
byobu send-keys -t l25gc:0.2 "cd /root/PANDA_5G/HOME/onvm-free5gc3.0.5/bin" C-m
byobu send-keys -t l25gc:0.3 "cd /root/PANDA_5G/HOME/onvm-free5gc3.0.5/bin" C-m
byobu send-keys -t l25gc:0.4 "cd /root/PANDA_5G/HOME/onvm-free5gc3.0.5/bin" C-m
byobu send-keys -t l25gc:0.5 "cd /root/PANDA_5G/HOME/onvm-free5gc3.0.5/bin" C-m
byobu send-keys -t l25gc:0.6 "cd /root/PANDA_5G/HOME/onvm-free5gc3.0.5/bin" C-m
byobu send-keys -t l25gc:0.7 "cd /root/PANDA_5G/HOME/onvm-free5gc3.0.5/bin" C-m



byobu send-keys -t l25gc:0.0 "./nrf --nrfcfg ../config/nrfcfg.yaml" C-m
byobu send-keys -t l25gc:0.1 "./amf --amfcfg ../config/amfcfg.yaml" C-m
byobu send-keys -t l25gc:0.2 "./udm --udmcfg ../config/udmcfg.yaml" C-m
byobu send-keys -t l25gc:0.3 "./udr --udrcfg ../config/udrcfg.yaml" C-m
byobu send-keys -t l25gc:0.4 "./ausf --ausfcfg ../config/ausfcfg.yaml" C-m
byobu send-keys -t l25gc:0.5 "./smf" C-m
byobu send-keys -t l25gc:0.6 "./pcf --pcfcfg ../config/pcfcfg.yaml" C-m
byobu send-keys -t l25gc:0.7 "./nssf --nssfcfg ../config/nssfcfg.yaml" C-m


sleep 1
byobu send-keys -t l25gc:1.1 "cd /root/PANDA_5G/HOME/onvm-upf/examples/arp_response" C-m
byobu send-keys -t l25gc:1.1 "make" C-m
byobu send-keys -t l25gc:1.1 "./go.sh 11 -s 192.168.0.2,10.100.200.1 -d 1 -p" C-m




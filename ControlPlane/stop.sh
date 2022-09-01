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

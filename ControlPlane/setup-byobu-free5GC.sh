byobu new-session -d -s l25gc
  
byobu rename-window -t l25gc:0 'cp_functions'
byobu split-window -t l25gc:0.0 -v
byobu split-window -t l25gc:0.0 -h
byobu split-window -t l25gc:0.0 -h
byobu split-window -t l25gc:0.2 -h
byobu split-window -t l25gc:0.4 -h
byobu split-window -t l25gc:0.4 -h
byobu split-window -t l25gc:0.6 -h

byobu new-window -t l25gc:1 -n 'up_functions'
byobu split-window -t l25gc:1.0 -v
byobu split-window -t l25gc:1.0 -h
byobu split-window -t l25gc:1.2 -h


byobu attach-session -t l25gc

#include "headers.p4"
#include "parser.p4"
#include "gtp.p4"


#define UPF_IP 2130706433 // 127.0.0.1

/*** ACTIONS ***/

action _nop() {
	// no operation
}
action _drop() {
	drop();
}
action forward(port) {
	modify_field(standard_metadata.egress_spec, port);
}

action lookup_state_action(){ 
	lookup_state();
}

action do_bufferPkt() {
    bufferPkt();
}

/*** TABLES ***/

table fwd {
    reads {
        standard_metadata.ingress_port: exact;
    }
    actions {forward; _drop;}
    // size : 8
}


// GTP Tables
table gtpu_decap_table {
	reads {
		gtpu.teid          : exact;
		gtpu_ipv4.diffserv : exact;	
		gtpu_ipv4.srcAddr  : exact;
		gtpu_ipv4.dstAddr  : exact;
	}
	actions {
		gtpu_decap_v4;
		_drop;
		_nop;
	}
}

table gtpu_encap_table {
        reads {
                ipv4.srcAddr  : exact;
                ipv4.dstAddr  : exact;
        }
        actions {
                gtpu_encap_v4;
                _drop;
                _nop;
        }
}




///// CONTROL /////////////////////////////////////////////
control ingress{
    apply(fwd);
    
    // If IP address is that of the UDP
    if( ipv4.dstAddr == UPF_IP){
      apply(gtpu_decap_table);
    }else{
      apply(gtpu_encap_table);
    }
    apply(lookup_state_action);
    apply(do_bufferPkt);
}

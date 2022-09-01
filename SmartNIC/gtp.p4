header_type gtpu_t {
    fields { // 8bytes
		flags   : 8;
		type_   : 8;
		length_ : 16;
		teid    : 32;
	}
}
header gtpu_t gtpu;

///// PARSER //////////////////////////////////////////////

parser parse_gtpu {
    extract(gtpu);
    return parse_gtpu_ipv4;
}

parser parse_gtpu_ipv4 {
	extract(gtpu_ipv4);
	return ingress;
}

///// ACTIONS /////////////////////////////////////////////
action gtpu_encap_v4(srcAddr, dstAddr, srcPort, dstPort, type_, teid, port) {
    // ethernet|ipv6 => ethernet|ipv6(new)|udp|gtpu|gtpu_ipv6(original)
    add_header(udp);
    add_header(gtpu);
    add_header(gtpu_ipv4);
    copy_header(gtpu_ipv4, ipv4);
    // set ipv6 fields which needs to be modified from the original packet
    //add_to_field(ipv4.payloadLen, 20+8+8); // IPv6(20)+UDP(8)+GTPU(8)
    modify_field(ipv4.protocol, IP_PROTOCOLS_UDP);
    modify_field(ipv4.srcAddr, srcAddr);
    modify_field(ipv4.dstAddr, dstAddr);
    // set udp
    modify_field(udp.srcPort, srcPort); // TODO: generate from flow label, or random??
    modify_field(udp.dstPort, dstPort); // default 2123
    //modify_field(udp.length_, ipv4.payloadLen-20); // Substract IPv6(20)
    // TODO: calculate checksum after updating gtpu??
    // set gtpu
    // Flags: ver:001,type_:1(GTP) | 00,0(Seq),0
    modify_field(gtpu.flags, 0x30); 
    modify_field(gtpu.type_, type_);
    modify_field(gtpu.length_, udp.length_-16); // Substract UDP, GTPU header length
    modify_field(gtpu.teid, teid);
    modify_field(standard_metadata.egress_spec, port);
}

action gtpu_decap_v4() {
	copy_header(ipv4, gtpu_ipv4);
	remove_header(udp);
	remove_header(gtpu);
	remove_header(gtpu_ipv4);
}

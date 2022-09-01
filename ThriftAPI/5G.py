import datetime
import argparse
import struct
import sys
import pprint
import collections
import time
import random
import subprocess
import select

import time
sys.path.append('gen-py')

from urlparse import urlparse
from thrift.transport import TTransport
from thrift.transport import TZlibTransport
from thrift.transport import TSocket
#from thrift.transport import TSSLSocket
from thrift.transport import THttpClient
from thrift.protocol import TBinaryProtocol

from sdk6_rte import RunTimeEnvironment
from sdk6_rte.ttypes import *

parser = argparse.ArgumentParser()

parser.add_argument('-s','--server',
                    dest='rpc_server', default='localhost',
                    type=str,
                    help="Thrift RPC host (DEFAULT: localhost)")

parser.add_argument('-p','--port',
                    dest='rpc_port', default='20206',
                    type=str,
                    help="Thrift RPC port (DEFAULT: 20206)")



def construct_name_to_table_id_map():
	FORWARDING_TABLE_NAME = 'fwd'
	table_list = client.table_list_all()
	forwarding_table  =  [ x for x in list(table_list) if FORWARDING_TABLE_NAME in str(x)][0]
	forwarding_table_id = int(str(forwarding_table).split("tbl_id=")[1].split(",")[0])
	
	GTP_ENCAP_TABLE_NAME   = 'gtpu_encap_table'
	gtpu_encap_table    =  [ x for x in list(table_list) if GTP_ENCAP_TABLE_NAME in str(x)][0]
	gtpu_encap_table_id = int(str(gtpu_encap_table).split("tbl_id=")[1].split(",")[0])
	
	GTP_DECAP_TABLE_NAME   = 'gtpu_decap_table'
	gtpu_decap_table    =  [ x for x in list(table_list) if GTP_DECAP_TABLE_NAME in str(x)][0]
	gtpu_decap_table_id = int(str(gtpu_decap_table).split("tbl_id=")[1].split(",")[0])

	return {
		'fwd' : forwarding_table_id, 
		'gtpu_encap_table' : gtpu_encap_table_id,
		'gtpu_decap_table' : gtpu_decap_table_id,
	}


def printRules(tblid):
	pp      = pprint.PrettyPrinter(depth=6)
	te_list =  client.table_retrieve(tblid)
	for te in te_list:
		pp.pprint( te )
		print "\n" 



def flush_prev_rules(tblid):
    for te in client.table_retrieve(tblid) :
        if "default" not in str(te.rule_name):
            tbl_entry = TableEntry()
            tbl_entry.rule_name = te.rule_name
            tbl_entry.default_rule = False
            tbl_entry.match = '{ }'
            tbl_entry.actions = '{ }'

            ret = client.table_entry_delete(tblid, tbl_entry)
            if ret.value != RteReturnValue.SUCCESS:
                    print 'Unable to flush rule.'


def flush_rule_by_name(tblid, rule_name):
    for te in client.table_retrieve(tblid) :
        if "default" not in str(te.rule_name) and str(te.rule_name) == rule_name:
            tbl_entry = TableEntry()
            tbl_entry.rule_name = te.rule_name
            tbl_entry.default_rule = False
            tbl_entry.match = '{ }'
            tbl_entry.actions = '{ }'

            ret = client.table_entry_delete(tblid, tbl_entry)
            if ret.value != RteReturnValue.SUCCESS:
                    print 'Unable to flush rule.'

parser.set_defaults()

args = parser.parse_args()

use_zlib = 0

host = args.rpc_server
port = int(args.rpc_port)

socket = TSocket.TSocket(host, port)
transport = TTransport.TBufferedTransport(socket)
if use_zlib:
    transport = TZlibTransport.TZlibTransport(transport)

protocol = TBinaryProtocol.TBinaryProtocol(transport)
client = RunTimeEnvironment.Client(protocol)
transport.open()

TBL_NAME_TO_ID_MAP = construct_name_to_table_id_map()

print("Forwarding table")
printRules(TBL_NAME_TO_ID_MAP["fwd"])
print("GTP Encap Table")
printRules(TBL_NAME_TO_ID_MAP["gtpu_encap_table"])
print("GTP Decap Table")
printRules(TBL_NAME_TO_ID_MAP["gtpu_decap_table"])


flush_prev_rules(TBL_NAME_TO_ID_MAP["fwd"])
flush_prev_rules(TBL_NAME_TO_ID_MAP["gtpu_encap_table"])
flush_prev_rules(TBL_NAME_TO_ID_MAP["gtpu_decap_table"])


def addDecapRule(rule_name = 'REMOVE_GTP_HDR', priority = 0, match_srcAddr = None, match_dstAddr = None, match_teid = None ):
	rule_name_for_decap = [str(x.rule_name) for x in client.table_retrieve(TBL_NAME_TO_ID_MAP["gtpu_decap_table"])]
	if rule_name not in rule_name_for_decap:
	# Insert the rule.
		tbl_entry = TableEntry()
		tbl_entry.rule_name = rule_name
		tbl_entry.priority  = priority
		tbl_entry.default_rule = False	
		
		tbl_entry.match = '{'
		tbl_entry.match+= '"gtpu_ipv4.srcAddr" : { "value" : "%d"}' % match_srcAddr if match_srcAddr != None else ''
		tbl_entry.match+= '"gtpu_ipv4.dstAddr" : { "value" : "%d"}' % match_dstAddr if match_dstAddr != None else ''
		tbl_entry.match+= '"gtpu.teid" : { "value" : "%d"}' % match_teid if match_teid != None else ''
		tbl_entry.match+= '}'

		tbl_entry.actions= '{"type" : "gtpu_decap_v4" }'

		a = datetime.datetime.now()
		ret = client.table_entry_add(TBL_NAME_TO_ID_MAP["gtpu_decap_table"], tbl_entry )
		b = datetime.datetime.now()
		delta = b - a
		print("Elapsed Time (ms) ", delta.total_seconds() * 1000) # milliseconds
    		if ret.value != RteReturnValue.SUCCESS:
        		print 'Could not insert Decap Rule'
	else:
		print("Change Rule Name")

def addEncapRule(rule_name = 'ADD_GTP_HDR', priority = 0, srcAddr = 12, dstAddr = 10, srcPort = 11, dstPort = 2152, type_ = 0, teid = 2, match_dstAddr = 3232235540, port = "v0.0"):
	rule_name_for_decap = [str(x.rule_name) for x in client.table_retrieve(TBL_NAME_TO_ID_MAP["gtpu_encap_table"])]
	if rule_name not in rule_name_for_decap:
	# Insert the rule.
		tbl_entry = TableEntry()
		tbl_entry.rule_name = rule_name
		tbl_entry.priority  = priority
		tbl_entry.default_rule = False	
		
		tbl_entry.match = '{'
		tbl_entry.match+= '"ipv4.dstAddr" : { "value" : "%d"}' % match_dstAddr if match_dstAddr != None else ''
		tbl_entry.match+= '}'

		tbl_entry.actions = '{"type" : "gtpu_encap_v4",'
		tbl_entry.actions+= '"data" : {'		
		tbl_entry.actions+= '"srcAddr" : {"value" : "%s"},' % srcAddr
		tbl_entry.actions+= '"dstAddr" : {"value" : "%s"},' % dstAddr
		tbl_entry.actions+= '"srcPort" : {"value" : "%s"},' % srcPort
		tbl_entry.actions+= '"dstPort" : {"value" : "%s"},' % dstPort
		tbl_entry.actions+= '"type_"   : {"value" : "%s"},' % type_
		tbl_entry.actions+= '"teid"    : {"value" : "%s"},'  % teid
		tbl_entry.actions+= '"port"    : {"value" : "%s"}'  % port
		tbl_entry.actions+= '}}'
		a = datetime.datetime.now()
		ret = client.table_entry_add(TBL_NAME_TO_ID_MAP["gtpu_encap_table"], tbl_entry )
		b = datetime.datetime.now()
		delta = b - a
		print("Elapsed Time (ms) ", delta.total_seconds() * 1000) # milliseconds
    		if ret.value != RteReturnValue.SUCCESS:
        		print 'Could not insert Encap Rule'
	else:
		print("Change Rule Name")


def handle_request_raw(req):
	# Any command with function_name in the hash map is a raw command.
        # Read more here: https://docs.google.com/document/d/1v1VfEu6k5MN2GHv7xGhLbC6JCkvWLSg-wMUA_3AVPow/edit#heading=h.sa1ecxsq93q6   
        if req['function_name'] == 'printRules':
                printRules(TBL_NAME_TO_ID_MAP[req['table']])
        if req['function_name'] == 'flush_prev_rules':
                flush_prev_rules(TBL_NAME_TO_ID_MAP[req['table']])
        if req['function_name'] == 'addEncapRule':
                addEncapRule(rule_name = req['rule_name'],
                                priority = req['priority'],
                                srcAddr = req['srcAddr'],
                                dstAddr = req['dstAddr'],
                                srcPort = req['srcPort'],
                                dstPort = req['dstPort'],
                                type_ = req['type_'],
                                teid = req['teid'],
                                match_srcAddr = req['match_srcAddr'],
                                match_dstAddr = req['match_dstAddr'])
        if req['function_name'] == 'addDecapRule':
                addDecapRule(rule_name = req['rule_name'],
                                priority = req['priority'],
                                match_srcAddr = req['match_srcAddr'],
                                match_dstAddr =  req['match_dstAddr'])

far_set = set()
pending_pdr = {} # map far_id to pending pdr.
downlink_tbl_entries = {} # map (far id, teid) to attrs.
def handle_request_C(req):
	if req['msgtype'] == 'farcreate':
		far_set.add(req['farId'])
      		pending_pdr[req['farId']] = None
    	if req['msgtype'] == 'pdrcreate':
      		if req['direction'] == 'uplink':
        	# Push to sNIC immediately.
			addDecapRule(rule_name = "far_{}".format(req['farId']),
                                                priority = 0,
                                                match_teid = req['teid'])
      		if req['direction'] == 'downlink':
       		 # Push to sNIC after modification request.
        		if req['farId'] in pending_pdr:
				pending_pdr[req['farId']] = req
  	if req['msgtype'] == 'farupdate' and req['farId'] in pending_pdr and pending_pdr[req['farId']] != None:
		if (req['farId'], req['teid']) not in downlink_tbl_entries:
			addEncapRule(rule_name = 'far_{}_teid_{}'.format(req['farId'], req['teid']),
				priority = 0, srcAddr = int(2130706433), dstAddr = req['ipv4'],
				srcPort = 2152, dstPort = req['port'], type_ = 0, teid = req['teid'],
				match_dstAddr = pending_pdr[req['farId']]['ueip'])
			downlink_tbl_entries[(req['farId'], req['teid'])] = \
				{
				'ipv4' : req['ipv4'],
				'port' : req['port'],
				'teid' : req['teid'],
				'ueip' : pending_pdr[req['farId']]['ueip'],
				}
	if req['msgtype'] == 'active_to_idle':
		for far_id, teid in downlink_tbl_entries.keys():
			if far_id == req['farId']:
				attr = downlink_tbl_entries[(far_id, teid)]
				# remove prev rule.
				rule_name = 'far_{}_teid_{}'.format(req['farId'], attr['teid'])
				flush_rule_by_name(TBL_NAME_TO_ID_MAP["gtpu_encap_table"], rule_name)
				addEncapRule(rule_name = rule_name,
                                	priority = 0, srcAddr = int(2130706433), dstAddr = attr['ipv4'],
                                	srcPort = 2152, dstPort = attr['port'], type_ = 0, teid = attr['teid'],
                                	match_dstAddr = attr['ueip'], port = "v0.1")
	if req['msgtype'] == 'idle_to_active':
                for far_id, teid in downlink_tbl_entries.keys():
                        if far_id == req['farId']:
                                attr = downlink_tbl_entries[(far_id, teid)]
                                # remove prev rule.
                                rule_name = 'far_{}_teid_{}'.format(req['farId'], attr['teid'])
                                flush_rule_by_name(TBL_NAME_TO_ID_MAP["gtpu_encap_table"], rule_name)
                                addEncapRule(rule_name = rule_name,
                                        priority = 0, srcAddr = int(2130706433), dstAddr = attr['ipv4'],
                                        srcPort = 2152, dstPort = attr['port'], type_ = 0, teid = attr['teid'],
                                        match_dstAddr = attr['ueip'], port = "v0.0")


filename = '/tmp/thrift'

f = subprocess.Popen(['tail','-F',filename],\
        stdout=subprocess.PIPE,stderr=subprocess.PIPE)
p = select.poll()
p.register(f.stdout)

while True:
    if p.poll(1):
        req = f.stdout.readline()
        req = req.strip()
        req =  eval(req)
	print("Req ", req)

	if 'function_name' in req:
		handle_request_raw(req)
	if 'msgtype' in req:
		handle_request_C(req)
    time.sleep(1)


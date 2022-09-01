package onvmNet

// #cgo CFLAGS: -m64 -pthread -O3 -march=native
// #cgo CFLAGS: -I/root/PANDA_5G/HOME/onvm-upf/onvm/onvm_nflib
// #cgo CFLAGS: -I/root/PANDA_5G/HOME/onvm-upf/onvm/lib
// #cgo CFLAGS: -I/root/PANDA_5G/HOME/onvm-upf/dpdk/x86_64-native-linuxapp-gcc/include
// #cgo LDFLAGS: /root/PANDA_5G/HOME/onvm-upf/onvm/onvm_nflib/x86_64-native-linuxapp-gcc/libonvm.a
// #cgo LDFLAGS: /root/PANDA_5G/HOME/onvm-upf/onvm/lib/x86_64-native-linuxapp-gcc/lib/libonvmhelper.a -lm
// #cgo LDFLAGS: -L/root/PANDA_5G/HOME/onvm-upf/dpdk/x86_64-native-linuxapp-gcc/lib
// #cgo LDFLAGS: -lrte_flow_classify -Wl,--whole-archive -lrte_pipeline -Wl,--no-whole-archive -Wl,--whole-archive -lrte_table -Wl,--no-whole-archive -Wl,--whole-archive -lrte_port -Wl,--no-whole-archive -lrte_pdump -lrte_distributor -lrte_ip_frag -lrte_meter -lrte_fib -lrte_rib -lrte_lpm -lrte_acl -lrte_jobstats -Wl,--whole-archive -lrte_metrics -Wl,--no-whole-archive -lrte_bitratestats -lrte_latencystats -lrte_power -lrte_efd -lrte_bpf -lrte_ipsec -Wl,--whole-archive -lrte_cfgfile -lrte_gro -lrte_gso -lrte_hash -lrte_member -lrte_vhost -lrte_kvargs -lrte_telemetry -lrte_mbuf -lrte_net -lrte_ethdev -lrte_bbdev -lrte_cryptodev -lrte_security -lrte_compressdev -lrte_eventdev -lrte_rawdev -lrte_timer -lrte_mempool -lrte_stack -lrte_mempool_ring -lrte_mempool_octeontx2 -lrte_ring -lrte_pci -lrte_eal -lrte_cmdline -lrte_reorder -lrte_sched -lrte_rcu -lrte_graph -lrte_node -lrte_kni -lrte_common_cpt -lrte_common_octeontx -lrte_common_octeontx2 -lrte_common_dpaax -lrte_bus_pci -lrte_bus_vdev -lrte_bus_dpaa -lrte_bus_fslmc -lrte_mempool_bucket -lrte_mempool_stack -lrte_mempool_dpaa -lrte_mempool_dpaa2 -lrte_pmd_af_packet -lrte_pmd_ark -lrte_pmd_atlantic -lrte_pmd_avp -lrte_pmd_axgbe -lrte_pmd_bnxt -lrte_pmd_bond -lrte_pmd_cxgbe -lrte_pmd_dpaa -lrte_pmd_dpaa2 -lrte_pmd_e1000 -lrte_pmd_ena -lrte_pmd_enetc -lrte_pmd_enic -lrte_pmd_fm10k -lrte_pmd_failsafe -lrte_pmd_hinic -lrte_pmd_hns3 -lrte_pmd_i40e -lrte_pmd_iavf -lrte_pmd_ice -lrte_common_iavf -lrte_pmd_igc -lrte_pmd_ionic -lrte_pmd_ixgbe -lrte_pmd_kni -lrte_pmd_lio -lrte_pmd_memif -lrte_pmd_nfp -lrte_pmd_null -lrte_pmd_octeontx2 -lrte_pmd_qede -lrte_pmd_ring -lrte_pmd_softnic -lrte_pmd_sfc_efx -lrte_pmd_tap -lrte_pmd_thunderx_nicvf -lrte_pmd_vdev_netvsc -lrte_pmd_virtio -lrte_pmd_vhost -lrte_pmd_ifc -lrte_pmd_vmxnet3_uio -lrte_bus_vmbus -lrte_pmd_netvsc -lrte_pmd_bbdev_null -lrte_pmd_bbdev_fpga_lte_fec -lrte_pmd_bbdev_fpga_5gnr_fec -lrte_pmd_bbdev_turbo_sw -lrte_pmd_null_crypto -lrte_pmd_nitrox -lrte_pmd_octeontx_crypto -lrte_pmd_octeontx2_crypto -lrte_pmd_crypto_scheduler -lrte_pmd_dpaa2_sec -lrte_pmd_dpaa_sec -lrte_pmd_caam_jr -lrte_pmd_virtio_crypto -lrte_pmd_octeontx_zip -lrte_pmd_qat -lrte_pmd_skeleton_event -lrte_pmd_sw_event -lrte_pmd_dsw_event -lrte_pmd_octeontx_ssovf -lrte_pmd_dpaa_event -lrte_pmd_dpaa2_event -lrte_mempool_octeontx -lrte_pmd_octeontx -lrte_pmd_octeontx2_event -lrte_pmd_opdl_event -lrte_rawdev_skeleton -lrte_rawdev_dpaa2_cmdif -lrte_rawdev_dpaa2_qdma -lrte_bus_ifpga -lrte_rawdev_ioat -lrte_rawdev_ntb -lrte_rawdev_octeontx2_dma -lrte_rawdev_octeontx2_ep -Wl,--no-whole-archive -lrt -lm -lnuma -ldl
/*
#include <stdlib.h>
#include <rte_lcore.h>
#include <rte_common.h>
#include <rte_ip.h>
#include <rte_udp.h>
#include <rte_mbuf.h>
#include <onvm_nflib.h>
#include <onvm_pkt_helper.h>

static inline struct udp_hdr*
get_pkt_udp_hdr(struct rte_mbuf* pkt) {
    uint8_t* pkt_data = rte_pktmbuf_mtod(pkt, uint8_t*) + sizeof(struct rte_ether_hdr) + sizeof(struct rte_ipv4_hdr);
    return (struct udp_hdr*)pkt_data;
}
//wrapper for c macro
static inline int pktmbuf_data_len_wrapper(struct rte_mbuf* pkt){
	return rte_pktmbuf_data_len(pkt);
}

static inline uint8_t* pktmbuf_mtod_wrapper(struct rte_mbuf* pkt){
	return rte_pktmbuf_mtod(pkt,uint8_t*);
}
extern int onvm_init(struct onvm_nf_local_ctx **);
extern void onvm_send_pkt(char *, int, struct onvm_nf_local_ctx *,int);
*/
import "C"

import (
	"fmt"
	"github.com/google/gopacket"
	"github.com/google/gopacket/layers"
	"gopkg.in/yaml.v2"
	"io/ioutil"
	"net"
	"os"
	"reflect"
	"strconv"
	"time"
	"unsafe"
)

var pktmbuf_pool *C.struct_rte_mempool
var pktCount int
var config = &Config{} //move config to global
var nf_ctx *C.struct_onvm_nf_local_ctx
var channelMap = make(map[ConnMeta]chan PktMeta) //map to hanndle each channel of connection

//for each connection
type ConnMeta struct {
	ip       string
	port     int
	protocol int
}

type PktMeta struct {
	srcIp      net.IP
	srcPort    int
	payloadLen int     //packet length just include payload after tcpudp
	payloadPtr *[]byte //the pointer to byte slice of payload
}

type Config struct {
	//ServiceID int `yaml:"serviceID"`
	IPIDMap []struct {
		IP *string `yaml:"IP"`
		ID *int32  `yaml:"ID"`
	} `yaml:"IPIDMap"`
}

func init() {
	C.onvm_init(&nf_ctx)
}

//export Handler
func Handler(pkt *C.struct_rte_mbuf, meta *C.struct_onvm_pkt_meta,
	nf_local_ctx *C.struct_onvm_nf_local_ctx) int32 {
	pktCount++
	recvLen := int(C.pktmbuf_data_len_wrapper(pkt))                               //length include header??//int(C.rte_pktmbuf_data_len(pkt))
	buf := C.GoBytes(unsafe.Pointer(C.pktmbuf_mtod_wrapper(pkt)), C.int(recvLen)) //turn c memory to go memory
	umsBuf, raddr, destAddr := unMarshalUDP(buf)
	udpMeta := ConnMeta{
		destAddr.IP.String(),
		destAddr.Port,
		17,
	}
	pktMeta := PktMeta{
		raddr.IP,
		raddr.Port,
		len(umsBuf),
		&umsBuf,
	}

	channel, ok := channelMap[udpMeta]
	if ok {
		channel <- pktMeta
	} else {
		//drop packet(?)
	}

	meta.action = C.ONVM_NF_ACTION_DROP

	return 0
}

func ipToID(ip net.IP) (Id int, err error) {
	Id = -1
	for i := range config.IPIDMap {
		if *config.IPIDMap[i].IP == ip.String() {
			Id = int(*config.IPIDMap[i].ID)
			break
		}
	}
	if Id == -1 {
		err = fmt.Errorf("no match id")
	}
	return
}

//func marshalUDP(b []byte, raddr *net.UDPAddr, laddr *net.UDPAddr) []byte {
func marshalUDP(b []byte, raddr *ONVMAddr, laddr *ONVMAddr) []byte {
	//interfacebyname may need to modify,not en0
	/*
		ifi ,err :=net.InterfaceByName("en0")
		if err!=nil {
			panic(err)
		}
	*/
	buffer := gopacket.NewSerializeBuffer()
	options := gopacket.SerializeOptions{
		ComputeChecksums: true,
		FixLengths:       true,
	}

	ethlayer := &layers.Ethernet{
		SrcMAC:       net.HardwareAddr{0, 0, 0, 0, 0, 0},
		DstMAC:       net.HardwareAddr{0, 0, 0, 0, 0, 0},
		EthernetType: layers.EthernetTypeIPv4,
	}

	iplayer := &layers.IPv4{
		Version:  uint8(4),
		SrcIP:    laddr.IP,
		DstIP:    raddr.IP,
		TTL:      64,
		Protocol: layers.IPProtocolUDP,
	}

	udplayer := &layers.UDP{
		SrcPort: layers.UDPPort(laddr.Port),
		DstPort: layers.UDPPort(raddr.Port),
	}
	udplayer.SetNetworkLayerForChecksum(iplayer)
	err := gopacket.SerializeLayers(buffer, options,
		ethlayer,
		iplayer,
		udplayer,
		gopacket.Payload(b),
	)
	if err != nil {
		panic(err)
	}
	outgoingpacket := buffer.Bytes()
	return outgoingpacket

}

func getCPtrOfByteData(b []byte) *C.char {
	shdr := (*reflect.SliceHeader)(unsafe.Pointer(&b))
	ptr := (*C.char)(unsafe.Pointer(shdr.Data))
	//runtime alive?
	return ptr
}

//func unMarshalUDP(input []byte) (payLoad []byte, rAddr *net.UDPAddr) {
func unMarshalUDP(input []byte) (payLoad []byte, rAddr *ONVMAddr, destAddr *ONVMAddr) {
	//Unmarshaludp header and get the information(ip port) from header
	var rPort int
	var rIp net.IP
	var destIp net.IP
	var destPort int
	ethPacket := gopacket.NewPacket(
		input,
		layers.LayerTypeEthernet,
		gopacket.NoCopy) //this may be type zero copy

	ipLayer := ethPacket.Layer(layers.LayerTypeIPv4)

	if ipLayer != nil {
		ip, _ := ipLayer.(*layers.IPv4)
		rIp = ip.SrcIP
		destIp = ip.DstIP
	}
	udpLayer := ethPacket.Layer(layers.LayerTypeUDP)
	if udpLayer != nil {
		udp, _ := udpLayer.(*layers.UDP)
		rPort = int(udp.SrcPort)
		destPort = int(udp.DstPort)
		payLoad = udp.Payload
	}

	rAddr = &ONVMAddr{
		IP:   rIp,
		Port: rPort,
	}

	destAddr = &ONVMAddr{
		IP:   destIp,
		Port: destPort,
	}

	return
}

/*****************************************************************
ONVMConn to implement the interface of net.PacketConn and  net.Conn
*****************************************************************/
type ONVMConn struct {
	ludpaddr  *net.UDPAddr
	lonvmaddr *ONVMAddr
	udpChan   chan PktMeta
}

type ONVMAddr struct {
	IP        net.IP
	Port      int
	ServiceID int
}

func (a *ONVMAddr) Network() string {
	return "onvm"
}

func (a *ONVMAddr) String() string {
	if a == nil {
		return "<nil>"
	}
	ip := ""
	if len(a.IP) != 0 {
		ip = a.IP.String()
	}
	retString := net.JoinHostPort(ip, strconv.Itoa(a.Port)) + "-" + strconv.Itoa(a.ServiceID)
	//retString := net.JoinHostPort(ip, strconv.Itoa(a.Port))
	return retString
}

func (a *ONVMAddr) ToUDPAddr() *net.UDPAddr {
	udpAddr := &net.UDPAddr{
		IP:   a.IP,
		Port: a.Port,
	}
	return udpAddr
}

func UDPToONVMAddr(addr *net.UDPAddr) *ONVMAddr {
	onvmAddr := &ONVMAddr{
		IP:   addr.IP,
		Port: addr.Port,
	}
	return onvmAddr
}

func onvmRegisterChannel(lonvmaddr *ONVMAddr, channel chan PktMeta) {
	udpTuple := ConnMeta{
		lonvmaddr.IP.String(),
		lonvmaddr.Port,
		17,
	}
	channelMap[udpTuple] = channel
}

/*********************************
ListenONVM acts like ListenUDP
*********************************/
//func ListenONVM(network string, laddr *net.UDPAddr) (*ONVMConn, error) {
func ListenONVM(network string, laddr *ONVMAddr) (*ONVMConn, error) {
	// Read Config
	var ipIdConfig string
	if dir, err := os.Getwd(); err != nil {
		ipIdConfig = "./ipid.yaml"
	} else {
		ipIdConfig = dir + "/ipid.yaml"
	}
	if os.Getenv("IPIDConfig") != "" {
		ipIdConfig = os.Getenv("IPIDConfig")
	}
	fmt.Printf("Read config from %s\n", ipIdConfig)
	if yamlFile, err := ioutil.ReadFile(ipIdConfig); err != nil {
		panic(err)
	} else {
		if unMarshalErr := yaml.Unmarshal(yamlFile, config); unMarshalErr != nil {
			panic(unMarshalErr)
		}
	}

	conn := &ONVMConn{}
	//store local addr
	conn.lonvmaddr = laddr
	conn.ludpaddr = laddr.ToUDPAddr()
	//make channel and register to map
	conn.udpChan = make(chan PktMeta, 1)
	onvmRegisterChannel(laddr, conn.udpChan)
	go C.onvm_nflib_run(nf_ctx)

	return conn, nil
}

/**********************************
ReadFromOVNM acts like ReadFrom but return UDPAddr
**********************************/
//func (conn *ONVMConn) ReadFromONVM(b []byte) (int, *net.UDPAddr, error) {
func (conn *ONVMConn) ReadFromONVM(b []byte) (int, *ONVMAddr, error) {
	var pktMeta PktMeta
	pktMeta = <-conn.udpChan
	recvLength := pktMeta.payloadLen
	copy(b, *(pktMeta.payloadPtr))
	ronvmaddr := &ONVMAddr{
		IP:   pktMeta.srcIp,
		Port: pktMeta.srcPort,
		//ServiceID: ?,
	}
	return recvLength, ronvmaddr, nil
}

/**********************************
ReadFrom implements the PacketConn ReadFrom method
**********************************/
func (conn *ONVMConn) ReadFrom(b []byte) (int, net.Addr, error) {
	var pktMeta PktMeta
	pktMeta = <-conn.udpChan
	recvLength := pktMeta.payloadLen
	copy(b, *(pktMeta.payloadPtr))
	ronvmaddr := &ONVMAddr{
		IP:   pktMeta.srcIp,
		Port: pktMeta.srcPort,
	}
	return recvLength, ronvmaddr, nil
}

/********************************
WriteToONVM acts like WriteTo but take UDPAddr
********************************/
//func (conn *ONVMConn) WriteToONVM(b []byte, addr *net.UDPAddr) (int, error) {
func (conn *ONVMConn) WriteToONVM(b []byte, addr *ONVMAddr) (int, error) {
	var success_send_len int
	var buffer_ptr *C.char //point to the head of byte data

	//look up table to get id
	ID, err := ipToID(addr.IP)
	if err != nil {
		return 0, err
	}
	success_send_len = len(b) //???ONVM has functon to get it?-->right now onvm_send_pkt return void
	tempBuffer := marshalUDP(b, addr, conn.lonvmaddr)
	buffer_ptr = getCPtrOfByteData(tempBuffer)
	C.onvm_send_pkt(buffer_ptr, C.int(ID), nf_ctx, C.int(len(tempBuffer))) //C.onvm_send_pkt havn't write?

	return success_send_len, nil
}

/*******************************
WriteTo implement the PacketConn WriteTo method
********************************/
func (conn *ONVMConn) WriteTo(b []byte, addr net.Addr) (int, error) {
	var success_send_len int
	var buffer_ptr *C.char //point to the head of byte data

	tempAddr, ok := addr.(*ONVMAddr)
	if !ok {
		err := fmt.Errorf("WriteTo:can't convert to ONVMAddr")
		return 0, err
	}
	//look up table to get id
	ID, err := ipToID(tempAddr.IP)
	if err != nil {
		return 0, err
	}
	success_send_len = len(b) //???ONVM has functon to get it?-->right now onvm_send_pkt return void
	tempBuffer := marshalUDP(b, tempAddr, conn.lonvmaddr)
	buffer_ptr = getCPtrOfByteData(tempBuffer)
	C.onvm_send_pkt(buffer_ptr, C.int(ID), nf_ctx, C.int(len(tempBuffer))) //C.onvm_send_pkt havn't write?

	return success_send_len, err
}

/*********************************
Close close the connection and deregister the connect information
*********************************/
func (conn *ONVMConn) Close() error {
	//deregister channel
	udpMeta := &ConnMeta{
		conn.lonvmaddr.IP.String(),
		conn.lonvmaddr.Port,
		17,
	}
	delete(channelMap, *udpMeta) //delete from map
	C.onvm_nflib_stop(nf_ctx)
	return nil
}

/*********************************
LocalAddr returns the local network
*********************************/
func (conn *ONVMConn) LocalAddr() net.Addr {
	return conn.lonvmaddr
}

/*********************************
Following functions are to implement the interface of net.PacketConn and net.Conn,
but not use in ONVMConn project,just a empty shell
*********************************/
//In PacketConn and Conn interface
func (conn *ONVMConn) SetDeadline(t time.Time) error {
	return nil
}
func (conn *ONVMConn) SetReadDeadline(t time.Time) error {
	return nil
}
func (conn *ONVMConn) SetWriteDeadline(t time.Time) error {
	return nil
}

//In Conn interface
func (conn *ONVMConn) Read(b []byte) (n int, err error) {
	return 0, nil
}
func (conn *ONVMConn) Write(b []byte) (n int, err error) {
	return 0, nil
}
func (conn *ONVMConn) RemoteAddr() net.Addr {
	return nil
}

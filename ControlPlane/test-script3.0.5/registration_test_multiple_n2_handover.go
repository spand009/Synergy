package test_test

import (
//	"bytes"

	"encoding/binary"
	"encoding/hex"
	"fmt"
//	"net"

//	"os/exec"
	"strconv"
	"test"
	"testing"
	"time"

	"github.com/mohae/deepcopy"
	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
//	"golang.org/x/net/icmp"
//	"golang.org/x/net/ipv4"

	// ausf_context "github.com/free5gc/ausf/context"
	"github.com/free5gc/CommonConsumerTestData/UDM/TestGenAuthData"
//	"github.com/free5gc/milenage"
	"github.com/free5gc/nas"
	"github.com/free5gc/nas/nasMessage"
	"github.com/free5gc/nas/nasTestpacket"
	"github.com/free5gc/nas/nasType"
	"github.com/free5gc/nas/security"
	"github.com/free5gc/ngap"
	"github.com/free5gc/ngap/ngapType"
	"github.com/free5gc/openapi/models"
	//"github.com/ishidawataru/sctp"
	"git.cs.nctu.edu.tw/calee/sctp"
	"strings"
	"sync"
)

const ranN2Ipv4Addr string = "127.0.0.1"
const amfN2Ipv4Addr string = "127.0.0.1"
const ranN3Ipv4Addr string = "10.100.200.1"
const upfN3Ipv4Addr string = "10.100.200.3"

const GTPTEIDHEAD = 25//13
const GTPTEIDTAIL = 28//16
const NUM_UE = 2

var EXIT_FLAG = true
var ranUeTeidNode1Map = make(map[int64]int64)
var teidRanUeNode2Map = make(map[int64]int64)

//var channelMap = make(map[int64]chan PktMeta)
var channelMap = make(map[int64]chan DecodeResult)

type DecodeResult struct{
	amfUeNgapId int64
	ranUeNgapId int64
}

/*
type PktMeta struct{
	payloadLen int
	payload []byte
}
*/

func SHIFT(b byte) byte {
	return b<<4 + b>>4
}

func SHIFTArray(array []byte) []byte {
	buffer := make([]byte, len(array))
	for i, v := range array {
		buffer[i] = SHIFT(v)
	}
	return buffer
}

func parseMCC(mcc string) ([]byte, error) {

	mcc = mcc + "0"
	b0, err := hex.DecodeString(mcc[:2])
	if err != nil {
		return nil, err
	}
	b1, err := hex.DecodeString(mcc[2:])
	if err != nil {
		return nil, err
	}

	return append(SHIFTArray(b0), SHIFTArray(b1)...), nil
}

func parseMNC(mnc string) ([]byte, error) {

	var b0 []byte
	var b1 []byte
	var err error

	if mnc[0] == '0' {
		mnc = "0" + mnc
		b1, err = hex.DecodeString(mnc[:2])
		if err != nil {
			return nil, err
		}
		b0, err = hex.DecodeString(mnc[2:])
		if err != nil {
			return nil, err
		}
		b1[0] = b1[0] + 0b1111
	} else {
		mnc = mnc + "0"
		b0, err = hex.DecodeString(mnc[:2])
		if err != nil {
			return nil, err
		}
		b1, err = hex.DecodeString(mnc[2:])
		if err != nil {
			return nil, err
		}

	}

	return append(SHIFTArray(b0), SHIFTArray(b1)...), nil
}

func formatSupi(supi string) string {
	var s string
	if len(supi)%2 != 0 {
		s = supi[:3] + "0" + supi[3:6] + supi[6:]
	} else {
		s = supi
	}
	return s
}

func parseIdentifier(identifier string) ([]byte, error) {

	b, err := hex.DecodeString(identifier)
	if err != nil {
		return nil, err
	}
	return SHIFTArray(b), nil

}

func supiToSuci(supi string) ([]byte, error) {
	// 	Buffer: []uint8{0x01, 0x02, 0xf8, 0x39, 0xf0, 0xff, 0x00, 0x00, 0x01, 0x00, 0x47, 0x78},
	var buffer = []uint8{0x01, 0x02, 0xf8, 0x39, 0xf0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x47, 0x78}
	s := strings.Trim(supi, "imsi-")
	s = formatSupi(s)
	mcc := s[:3]
	mnc := s[3:6]

	mccB, err := parseMCC(mcc)
	if err != nil {
		return nil, err
	}
	mncB, err := parseMNC(mnc)
	if err != nil {
		return nil, err
	}

	buffer[1] = mccB[0]
	buffer[2] = mccB[1] + mncB[1]
	buffer[3] = mncB[0]

	identifier := s[6:]
	identifierB, err := parseIdentifier(identifier)
	if err != nil {
		return nil, err
	}

	buffer[8] = identifierB[0]
	buffer[9] = identifierB[1]
	buffer[10] = identifierB[2]
	buffer[11] = identifierB[3]
	return buffer, nil
}

//this function is to get teid from handover request and ranueid/amfueid from other message which is sent from amf
func getTeidNgapID(message *ngapType.NGAPPDU) (int64,int64,int64){
	var amfUeNgapID int64
	var ranUeNgapId int64
	var GTPTEID int64
	amfUeNgapID = -1
	ranUeNgapId = -1
	GTPTEID = -1

	if message.Present == ngapType.NGAPPDUPresentInitiatingMessage {
		initiatingMessage := message.InitiatingMessage
		if initiatingMessage == nil {
			fmt.Println("Initiating Message is nil")
			return -1,-1,-1
		}
		switch initiatingMessage.ProcedureCode.Value {
		case ngapType.ProcedureCodeInitialContextSetup:
			initialContextSetup := initiatingMessage.Value.InitialContextSetupRequest
			if initialContextSetup == nil {
				fmt.Println("initialContextSetup is nil")
			}
			for i:=0 ; i < len(initialContextSetup.ProtocolIEs.List); i++{
				ie := initialContextSetup.ProtocolIEs.List[i]
				switch ie.Id.Value {
				case ngapType.ProtocolIEIDAMFUENGAPID:
					amfUeNgapID = ie.Value.AMFUENGAPID.Value
					if ie.Value.AMFUENGAPID == nil {
						fmt.Println("AmfUeNgapID is nil")
						return -1,-1,-1
					}
				case ngapType.ProtocolIEIDRANUENGAPID:
					ranUeNgapId = ie.Value.RANUENGAPID.Value
					if ie.Value.RANUENGAPID == nil {
						fmt.Println("ranUeNgapID is nil")
						return -1,-1,-1
					}
				}
			}
		case ngapType.ProcedureCodeHandoverResourceAllocation:
			handoverRequest := initiatingMessage.Value.HandoverRequest
			if handoverRequest == nil {
				fmt.Println("handoverRequest is nil")
				return -1,-1,-1
			}
			for i := 0; i < len(handoverRequest.ProtocolIEs.List); i++ {
				ie := handoverRequest.ProtocolIEs.List[i]
				switch ie.Id.Value {
				case ngapType.ProtocolIEIDAMFUENGAPID:
					amfUeNgapID = ie.Value.AMFUENGAPID.Value
					if ie.Value.AMFUENGAPID == nil {
						fmt.Println("AmfUeNgapID is nil")
						return -1,-1,-1
					}
				case ngapType.ProtocolIEIDPDUSessionResourceSetupListHOReq:
					pduSessionResourceSetupItemHoReq := ie.Value.PDUSessionResourceSetupListHOReq.List[0].HandoverRequestTransfer
					teidString := pduSessionResourceSetupItemHoReq[GTPTEIDHEAD:GTPTEIDTAIL+1]
					GTPTEID = int64(binary.BigEndian.Uint32(teidString))
				}
			}
		}
	}

	return GTPTEID,amfUeNgapID,ranUeNgapId
}


func getPduSessionResourceSetupRequestTEID(message *ngapType.NGAPPDU) int64{
	var GTPTEID int64
	GTPTEID = -1
	initiatingMessage := message.InitiatingMessage
	pduSessionResourceSetupRequest := initiatingMessage.Value.PDUSessionResourceSetupRequest
	if pduSessionResourceSetupRequest == nil {
		fmt.Println("pduSessionResourceSetupRequest is nil")
		return -1
	}

	for i := 0; i < len(pduSessionResourceSetupRequest.ProtocolIEs.List); i++ {
		ie := pduSessionResourceSetupRequest.ProtocolIEs.List[i]
		//fmt.Println("ie.id",ie.Id.Value)
		switch ie.Id.Value {
		case ngapType.ProtocolIEIDPDUSessionResourceSetupListSUReq:
			pduSessionResourceSetupItemSuReq := ie.Value.PDUSessionResourceSetupListSUReq.List[0].PDUSessionResourceSetupRequestTransfer
			teidString := pduSessionResourceSetupItemSuReq[GTPTEIDHEAD:GTPTEIDTAIL+1]
			GTPTEID = int64(binary.BigEndian.Uint32(teidString))
			fmt.Println("Print GTP-TEID int(from pduSessionResourceSetupRequest): ",GTPTEID)

		}
	}
	return GTPTEID
}

func getHandoverTEID(message *ngapType.NGAPPDU) int64 {
	var GTPTEID int64
	initiatingMessage := message.InitiatingMessage
	handoverRequest := initiatingMessage.Value.HandoverRequest
	if handoverRequest == nil {
		fmt.Println("handoverRequest is nil")
		return -1
	}
	for i := 0; i < len(handoverRequest.ProtocolIEs.List); i++ {
		ieAmfUe := handoverRequest.ProtocolIEs.List[i]
		switch ieAmfUe.Id.Value {
		case ngapType.ProtocolIEIDPDUSessionResourceSetupListHOReq:
			pduSessionResourceSetupItemHoReq := ieAmfUe.Value.PDUSessionResourceSetupListHOReq.List[0].HandoverRequestTransfer
			teidString := pduSessionResourceSetupItemHoReq[GTPTEIDHEAD:GTPTEIDTAIL+1]
			GTPTEID = int64(binary.BigEndian.Uint32(teidString))
			fmt.Println("Print GTP-TEID int: ",GTPTEID)
		}
	}
	return GTPTEID
}
// Registration -> PDU Session Establishment -> Source RAN Send Handover Required -> N2 Handover (Preparation Phase -> Execution Phase)
func TestN2Handover(t *testing.T) {
	var n int
	var sendMsg []byte
	var recvMsg = make([]byte, 2048)
	var err error
	numUE := NUM_UE
	connQ := make([]*sctp.SCTPConn, numUE) 

	//ran1 create multiple sctp connection to amf
	for i := 0; i < numUE; i++{
		// RAN1 connect to AMF
		connQ[i], err = test.ConnectToAmf("127.0.0.1", "127.0.0.1", 38412, 9487 + i)
		assert.Nil(t, err)

		// RAN1 send NGSetupRequest Msg
		sendMsg, err = test.GetNGSetupRequest([]byte("\x00\x01\x01"), 24, "free5gc")
		assert.Nil(t, err)
		_, err = connQ[i].Write(sendMsg)
		assert.Nil(t, err)

		// RAN1 receive NGSetupResponse Msg
		n, err = connQ[i].Read(recvMsg)
		assert.Nil(t, err)
		_, err = ngap.Decoder(recvMsg[:n])
		assert.Nil(t, err)

		time.Sleep(10 * time.Millisecond)
	}

	//ran2 create single sctp connection
	conn2Q := make([]*sctp.SCTPConn, numUE) 
	// RAN2 connect to AMF
	conn2 , err := test.ConnectToAmf("127.0.0.1", "127.0.0.1", 38412, 9587 )
	assert.Nil(t, err)

	// RAN2 send Second NGSetupRequest Msg
	sendMsg, err = test.GetNGSetupRequest([]byte("\x00\x01\x02"), 24, "nctu")
	assert.Nil(t, err)
	_, err = conn2.Write(sendMsg)
	assert.Nil(t, err)

	// RAN2 receive Second NGSetupResponse Msg
	n, err = conn2.Read(recvMsg)
	assert.Nil(t, err)
	_, err = ngap.Decoder(recvMsg[:n])
	assert.Nil(t, err)

	for i := 0; i < numUE; i++ {
		conn2Q[i] = conn2
		//sctpChannel := make(chan PktMeta,1)
		sctpChannel := make(chan DecodeResult,1)
		channelMap[int64(i+1)] = sctpChannel
		time.Sleep(10 * time.Millisecond)
	}

	pdu := make([][]byte,numUE)
	ueQ := make([]*test.RanUeContext, numUE)
	servingPlmnId := "20893"

	for i := 0 ; i < numUE ; i++{
		idx := i
		// New UE
		ueID := "imsi-" + strconv.Itoa(2089300000000 + idx+1)

		ueQ[idx] = test.NewRanUeContext(ueID, int64(idx+1), security.AlgCiphering128NEA0, security.AlgIntegrity128NIA2)
		ueQ[idx].AmfUeNgapId = int64(idx+1)
		ueQ[idx].AuthenticationSubs = test.GetAuthSubscription(TestGenAuthData.MilenageTestSet19.K,
			TestGenAuthData.MilenageTestSet19.OPC,
			TestGenAuthData.MilenageTestSet19.OP)
		// insert UE data to MongoDB

		test.InsertAuthSubscriptionToMongoDB(ueQ[idx].Supi, ueQ[idx].AuthenticationSubs)
		getData := test.GetAuthSubscriptionFromMongoDB(ueQ[idx].Supi)
		assert.NotNil(t, getData)
		{
			amData := test.GetAccessAndMobilitySubscriptionData()
			test.InsertAccessAndMobilitySubscriptionDataToMongoDB(ueQ[idx].Supi, amData, servingPlmnId)
			getData := test.GetAccessAndMobilitySubscriptionDataFromMongoDB(ueQ[idx].Supi, servingPlmnId)
			assert.NotNil(t, getData)
		}
		{
			smfSelData := test.GetSmfSelectionSubscriptionData()
			test.InsertSmfSelectionSubscriptionDataToMongoDB(ueQ[idx].Supi, smfSelData, servingPlmnId)
			getData := test.GetSmfSelectionSubscriptionDataFromMongoDB(ueQ[idx].Supi, servingPlmnId)
			assert.NotNil(t, getData)
		}
		{
			smSelData := test.GetSessionManagementSubscriptionData()
			test.InsertSessionManagementSubscriptionDataToMongoDB(ueQ[idx].Supi, servingPlmnId, smSelData)
			getData := test.GetSessionManagementDataFromMongoDB(ueQ[idx].Supi, servingPlmnId)
			assert.NotNil(t, getData)
		}
		{
			amPolicyData := test.GetAmPolicyData()
			test.InsertAmPolicyDataToMongoDB(ueQ[idx].Supi, amPolicyData)
			getData := test.GetAmPolicyDataFromMongoDB(ueQ[idx].Supi)
			assert.NotNil(t, getData)
		}
		{
			smPolicyData := test.GetSmPolicyData()
			test.InsertSmPolicyDataToMongoDB(ueQ[idx].Supi, smPolicyData)
			getData := test.GetSmPolicyDataFromMongoDB(ueQ[idx].Supi)
			assert.NotNil(t, getData)
		}

		//turn supi to suci
		suci, err := supiToSuci(ueID)
		assert.Nil(t, err)

		// send InitialUeMessage(Registration Request)(imsi-2089300007487)
		mobileIdentity5GS := nasType.MobileIdentity5GS{
			Len:    12, // suci
			Buffer: suci,//4778
		}

		ueSecurityCapability := ueQ[idx].GetUESecurityCapability()
		registrationRequest := nasTestpacket.GetRegistrationRequest(
			nasMessage.RegistrationType5GSInitialRegistration, mobileIdentity5GS, nil, ueSecurityCapability, nil, nil, nil)
		sendMsg, err = test.GetInitialUEMessage(ueQ[idx].RanUeNgapId, registrationRequest, "")
		assert.Nil(t, err)

		fmt.Println("Send Initial UE Message","(UE ",idx+1,")" )
		t1 := time.Now()
		_, err = connQ[idx].Write(sendMsg)
		assert.Nil(t, err)

		// receive NAS Authentication Request Msg
		n, err = connQ[idx].Read(recvMsg)
		assert.Nil(t, err)
		ngapMsg, err := ngap.Decoder(recvMsg[:n])
		assert.Nil(t, err)

		// Calculate for RES*
		nasPdu := test.GetNasPdu(ueQ[idx], ngapMsg.InitiatingMessage.Value.DownlinkNASTransport)
		require.NotNil(t, nasPdu)
		require.NotNil(t, nasPdu.GmmMessage, "GMM message is nil")
		require.Equal(t, nasPdu.GmmHeader.GetMessageType(), nas.MsgTypeAuthenticationRequest,
			"Received wrong GMM message. Expected Authentication Request.")
		rand := nasPdu.AuthenticationRequest.GetRANDValue()
		resStat := ueQ[idx].DeriveRESstarAndSetKey(ueQ[idx].AuthenticationSubs, rand[:], "5G:mnc093.mcc208.3gppnetwork.org")

		// send NAS Authentication Response
		pdu[idx] = nasTestpacket.GetAuthenticationResponse(resStat, "")
		sendMsg, err = test.GetUplinkNASTransport(ueQ[idx].AmfUeNgapId, ueQ[idx].RanUeNgapId, pdu[idx])
		assert.Nil(t, err)
		_, err = connQ[idx].Write(sendMsg)
		assert.Nil(t, err)

		// receive NAS Security Mode Command Msg
		n, err = connQ[idx].Read(recvMsg)
		assert.Nil(t, err)
		ngapPdu, err := ngap.Decoder(recvMsg[:n])
		require.Nil(t, err)
		require.NotNil(t, ngapPdu)
		nasPdu = test.GetNasPdu(ueQ[idx], ngapPdu.InitiatingMessage.Value.DownlinkNASTransport)
		require.NotNil(t, nasPdu)
		require.NotNil(t, nasPdu.GmmMessage, "GMM message is nil")
		require.Equal(t, nasPdu.GmmHeader.GetMessageType(), nas.MsgTypeSecurityModeCommand,
			"Received wrong GMM message. Expected Security Mode Command.")

		// send NAS Security Mode Complete Msg
		registrationRequestWith5GMM := nasTestpacket.GetRegistrationRequest(nasMessage.RegistrationType5GSInitialRegistration,
			mobileIdentity5GS, nil, ueSecurityCapability, ueQ[idx].Get5GMMCapability(), nil, nil)
		pdu[idx] = nasTestpacket.GetSecurityModeComplete(registrationRequestWith5GMM)
		pdu[idx], err = test.EncodeNasPduWithSecurity(ueQ[idx], pdu[idx], nas.SecurityHeaderTypeIntegrityProtectedAndCipheredWithNew5gNasSecurityContext, true, true)
		assert.Nil(t, err)
		sendMsg, err = test.GetUplinkNASTransport(ueQ[idx].AmfUeNgapId, ueQ[idx].RanUeNgapId, pdu[idx])
		assert.Nil(t, err)
		_, err = connQ[idx].Write(sendMsg)
		assert.Nil(t, err)

		// receive ngap Initial Context Setup Request Msg
		n, err = connQ[idx].Read(recvMsg)
		assert.Nil(t, err)
		_, err = ngap.Decoder(recvMsg[:n])
		assert.Nil(t, err)

		// send ngap Initial Context Setup Response Msg
		sendMsg, err = test.GetInitialContextSetupResponse(ueQ[idx].AmfUeNgapId, ueQ[idx].RanUeNgapId)
		assert.Nil(t, err)
		_, err = connQ[idx].Write(sendMsg)
		assert.Nil(t, err)

		// send NAS Registration Complete Msg
		pdu[idx] = nasTestpacket.GetRegistrationComplete(nil)
		pdu[idx], err = test.EncodeNasPduWithSecurity(ueQ[idx], pdu[idx], nas.SecurityHeaderTypeIntegrityProtectedAndCiphered, true, false)
		assert.Nil(t, err)
		sendMsg, err = test.GetUplinkNASTransport(ueQ[idx].AmfUeNgapId, ueQ[idx].RanUeNgapId, pdu[idx])
		assert.Nil(t, err)
		_, err = connQ[idx].Write(sendMsg)
		assert.Nil(t, err)

		t2 := time.Now()
		fmt.Println("Finish Registration : ",t2.Sub(t1).Seconds(),"(UE ",idx+1,")" )

		time.Sleep(100 * time.Millisecond)
	}



	var wg sync.WaitGroup
	for i := 0; i < numUE; i++ {
		tmp := i
		wg.Add(1)
		go func(idx int){
			defer wg.Done()

			var _sendMsg []byte
			var _recvMsg = make([]byte, 2048)

			fmt.Printf("Send PDU session req (UE %d)\n",idx+1)
			t3 := time.Now()

			// send PduSessionEstablishmentRequest Msg
			sNssai := models.Snssai{
				Sst: 1,
				Sd:  "010203",
			}
			pdu[idx] = nasTestpacket.GetUlNasTransport_PduSessionEstablishmentRequest(10, nasMessage.ULNASTransportRequestTypeInitialRequest, "internet", &sNssai)
			pdu[idx], err = test.EncodeNasPduWithSecurity(ueQ[idx], pdu[idx], nas.SecurityHeaderTypeIntegrityProtectedAndCiphered, true, false)
			assert.Nil(t, err)
			_sendMsg, err = test.GetUplinkNASTransport(ueQ[idx].AmfUeNgapId, ueQ[idx].RanUeNgapId, pdu[idx])
			assert.Nil(t, err)
			_, err = connQ[idx].Write(_sendMsg)
			assert.Nil(t, err)


			// receive 12. NGAP-PDU Session Resource Setup Request(DL nas transport((NAS msg-PDU session setup Accept)))
			n, err = connQ[idx].Read(_recvMsg)
			assert.Nil(t, err)
			ngapPdu, err := ngap.Decoder(_recvMsg[:n])
			//get teid and map to ranuengapid
			teid := getPduSessionResourceSetupRequestTEID(ngapPdu)

			ranUeTeidNode1Map[int64(idx+1)] = teid
			teidRanUeNode2Map[teid] = int64(idx+1)
			assert.Nil(t, err)

			// send 14. NGAP-PDU Session Resource Setup Response
			_sendMsg, err = test.GetPDUSessionResourceSetupResponse(10,ueQ[idx].AmfUeNgapId, ueQ[idx].RanUeNgapId, ranN3Ipv4Addr)
			assert.Nil(t, err)
			_, err = connQ[idx].Write(_sendMsg)
			assert.Nil(t, err)
			t4 := time.Now()
			fmt.Println("Finish PDU Session : ",t4.Sub(t3).Seconds() ,"(UE ",idx+1,")" )

			time.Sleep(1 * time.Second)
		}(tmp)
	}
	wg.Wait()


	//teid map to ranueid
	for ranue1 := range ranUeTeidNode1Map{
		fmt.Println("In node1 : ranUE ",ranue1," teid = ",ranUeTeidNode1Map[ranue1])
	}

	//node 2 simulator (go routine)
	go func(){
		var recvMsg_go = make([]byte, 2048)
		for {

			n, err := conn2.Read(recvMsg_go)
			assert.Nil(t, err)
			ngapPdu, err := ngap.Decoder(recvMsg_go[:n])
			assert.Nil(t, err)
			teidFromHandover , amfUeId , ranUeId := getTeidNgapID(ngapPdu)
			//get teid from handover request
			if teidFromHandover > 0 && ranUeId < 0{
				ranUeId = teidRanUeNode2Map[teidFromHandover]
			}
			if amfUeId == -1{
				fmt.Println("There is something wrong ><")
				fmt.Println("TEID ",teidFromHandover," AMF ",amfUeId," RAN ",ranUeId)
			}
			//just to transfer the result of decode message
			decodeResult := DecodeResult{
				amfUeNgapId: amfUeId,
				ranUeNgapId: ranUeId,
			}
			channelMap[ranUeId] <- decodeResult
			/* use to transfer all packet
			pktMeta := PktMeta{
				payloadLen : n,
				payload : recvMsg_go,
			}
			channelMap[teidFromHandover] <- pktMeta
			*/

		}
	}()

	time.Sleep(1*time.Second)
	fmt.Println("Start Multiple Handover")	
	// ============================================
	//var wg sync.WaitGroup
	for i := 0; i < numUE; i++ {
//		idx := i
		tmp := i
		wg.Add(1)
		go func(idx int) {
			defer wg.Done()
			fmt.Println("Start N2 Handover","(UE ",idx+1,")" )
			t5 := time.Now()

			// Source RAN send ngap Handover Required Msg
			sendMsg, err = test.GetHandoverRequired(ueQ[idx].AmfUeNgapId, ueQ[idx].RanUeNgapId, []byte{0x00, 0x01, 0x02}, []byte{0x01, 0x20})
			assert.Nil(t, err)
			_, err = connQ[idx].Write(sendMsg)
			assert.Nil(t, err)

			// Target RAN receive ngap Handover Request
			//n, err = conn2Q[idx].Read(recvMsg)  //NEED MODIFY
			//pktMeta := <-channelMap[int64(idx+1)]
			decodeResult := <- channelMap[int64(idx+1)]
			//n = pktMeta.payloadLen
			//recv := pktMeta.payload
			amfueid := decodeResult.amfUeNgapId
			targetAmfUeNgapId := amfueid
			if targetAmfUeNgapId == -1{
				fmt.Println("GET AMFUENGAPID -1")
				return
			}else{
				fmt.Printf("UE : %d / GET AMFUENGAPID : %d\n",idx+1,targetAmfUeNgapId)
			}

			// Target RAN create New UE
			targetUe := deepcopy.Copy(ueQ[idx]).(*test.RanUeContext)
			targetUe.AmfUeNgapId = targetAmfUeNgapId
			//targetUe.RanUeNgapId = int64(idx+2) //need to change
			targetUe.ULCount.Set(ueQ[idx].ULCount.Overflow(), ueQ[idx].ULCount.SQN())
			targetUe.DLCount.Set(ueQ[idx].DLCount.Overflow(), ueQ[idx].DLCount.SQN())

			// Target RAN send ngap Handover Request Acknowledge Msg
			sendMsg, err = test.GetHandoverRequestAcknowledge(targetUe.AmfUeNgapId, targetUe.RanUeNgapId)
			assert.Nil(t, err)
			_, err = conn2Q[idx].Write(sendMsg)
			assert.Nil(t, err)


			// End of Preparation phase
			time.Sleep(10 * time.Millisecond)

			// Beginning of Execution

			// Source RAN receive ngap Handover Command
			n, err = connQ[idx].Read(recvMsg)  //READ NO NEED MODIFY
			assert.Nil(t, err)
			_, err = ngap.Decoder(recvMsg[:n])
			assert.Nil(t, err)

			// Target RAN send ngap Handover Notify
			sendMsg, err = test.GetHandoverNotify(targetUe.AmfUeNgapId, targetUe.RanUeNgapId)
			assert.Nil(t, err)
			_, err = conn2Q[idx].Write(sendMsg)
			assert.Nil(t, err)

			// Source RAN receive ngap UE Context Release Command
			n, err = connQ[idx].Read(recvMsg)  //READ NO NEED MODIFY
			assert.Nil(t, err)
			_, err = ngap.Decoder(recvMsg[:n])
			assert.Nil(t, err)

			// Source RAN send ngap UE Context Release Complete
			pduSessionIDList := []int64{10}
			sendMsg, err = test.GetUEContextReleaseComplete(ueQ[idx].AmfUeNgapId, ueQ[idx].RanUeNgapId, pduSessionIDList)
			assert.Nil(t, err)
			_, err = connQ[idx].Write(sendMsg)
			assert.Nil(t, err)


			// UE send NAS Registration Request(Mobility Registration Update) To Target AMF (2 AMF scenario not supportted yet) use suci
			ueID := "imsi-" + strconv.Itoa(2089300000000 + idx+1)
			suci, err := supiToSuci(ueID)
			assert.Nil(t, err)
			mobileIdentity5GS := nasType.MobileIdentity5GS{
				Len:    12, // suci
				// Buffer: []uint8{0x01, 0x02, 0xf8, 0x39, 0xf0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x47, 0x78},
				Buffer: suci,
			}

			uplinkDataStatus := nasType.NewUplinkDataStatus(nasMessage.RegistrationRequestUplinkDataStatusType)
			uplinkDataStatus.SetLen(2)
			uplinkDataStatus.SetPSI10(1)
			ueSecurityCapability := targetUe.GetUESecurityCapability()
			pdu[idx] = nasTestpacket.GetRegistrationRequest(nasMessage.RegistrationType5GSMobilityRegistrationUpdating,
				mobileIdentity5GS, nil, ueSecurityCapability, ueQ[idx].Get5GMMCapability(), nil, uplinkDataStatus)
			pdu[idx], err = test.EncodeNasPduWithSecurity(targetUe, pdu[idx], nas.SecurityHeaderTypeIntegrityProtectedAndCiphered, true, false)
			assert.Nil(t, err)
			sendMsg, err = test.GetInitialUEMessage(targetUe.RanUeNgapId, pdu[idx], "")
			assert.Nil(t, err)
			_, err = conn2Q[idx].Write(sendMsg)
			assert.Nil(t, err)

			// Target RAN receive ngap Initial Context Setup Request Msg
//			n, err = conn2Q[idx].Read(recvMsg) //NEED MODIFY
			decodeResult = <- channelMap[int64(idx+1)]

			// Target RAN send ngap Initial Context Setup Response Msg
			//sendMsg, err = test.GetInitialContextSetupResponseForServiceRequest(targetUe.AmfUeNgapId, targetUe.RanUeNgapId, "10.200.200.2")
			sendMsg, err = test.GetInitialContextSetupResponseForServiceRequest(targetUe.AmfUeNgapId, targetUe.RanUeNgapId, "127.0.0.1")
			assert.Nil(t, err)
			_, err = conn2Q[idx].Write(sendMsg)
			assert.Nil(t, err)

			// Target RAN send NAS Registration Complete Msg
			pdu[idx] = nasTestpacket.GetRegistrationComplete(nil)
			pdu[idx], err = test.EncodeNasPduWithSecurity(targetUe, pdu[idx], nas.SecurityHeaderTypeIntegrityProtectedAndCiphered, true, false)
			assert.Nil(t, err)
			sendMsg, err = test.GetUplinkNASTransport(targetUe.AmfUeNgapId, targetUe.RanUeNgapId, pdu[idx])
			assert.Nil(t, err)
			_, err = conn2Q[idx].Write(sendMsg)
			assert.Nil(t, err)

			t6 := time.Now()
			fmt.Println("Finish Handover : ",t6.Sub(t5).Seconds(),"(UE ",idx+1,")" )

			//wait 1000 ms
			time.Sleep(1000 * time.Millisecond)
		}(tmp)
	}
	wg.Wait()


	fmt.Println("Finish all")
	time.Sleep(2*time.Second)

	for i := 0; i < numUE; i++ {
		// delete test data
		test.DelAuthSubscriptionToMongoDB(ueQ[i].Supi)
		test.DelAccessAndMobilitySubscriptionDataFromMongoDB(ueQ[i].Supi, servingPlmnId)
		test.DelSmfSelectionSubscriptionDataFromMongoDB(ueQ[i].Supi, servingPlmnId)
	}

	for i := 0; i < numUE; i++ {
		connQ[i].Close()
		conn2Q[i].Close()
	}


	// close Connection
//	conn.Close()
//	conn2.Close()

	// terminate all NF
//	NfTerminate()

}

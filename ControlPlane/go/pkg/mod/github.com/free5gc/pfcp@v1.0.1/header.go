package pfcp

import (
	"bytes"
	"encoding/binary"
	"errors"

	"github.com/free5gc/pfcp/logger"
)

const PfcpVersion uint8 = 1

const (
	SEID_NOT_PRESENT = 0
	SEID_PRESENT     = 1
)

/*
var (
	sequenceCount uint32
)
*/

func init() {
	//sequenceCount = 0
}

type Header struct {
	Version         uint8
	MP              uint8
	S               uint8
	MessageType     MessageType
	MessageLength   uint16
	SEID            uint64
	SequenceNumber  uint32
	MessagePriority uint8
}

func (h *Header) MarshalBinary() (data []byte, err error) {
	var tmpbuf uint8
	buffer := new(bytes.Buffer)
	tmpbuf = h.Version<<5 | (h.MP&1)<<1 | (h.S & 1)
	if err := binary.Write(buffer, binary.BigEndian, &tmpbuf); err != nil {
		logger.PFCPLog.Warnf("Binary write error: %+v", err)
	}
	if err := binary.Write(buffer, binary.BigEndian, &h.MessageType); err != nil {
		logger.PFCPLog.Warnf("Binary write error: %+v", err)
	}
	if err := binary.Write(buffer, binary.BigEndian, &h.MessageLength); err != nil {
		logger.PFCPLog.Warnf("Binary write error: %+v", err)
	}
	if h.S&1 != 0 {
		if err := binary.Write(buffer, binary.BigEndian, &h.SEID); err != nil {
			logger.PFCPLog.Warnf("Binary write error: %+v", err)
		}
	}
	var snAndSpare uint32
	var spareAndMP uint8
	if h.MP&1 != 0 {
		spareAndMP = h.MessagePriority << 4
	} else {
		spareAndMP = 0
	}
	if h.SequenceNumber > (1<<24 - 1) {
		logger.PFCPLog.Warnf("Sequence number must be less 24bit integer")
	}

	snAndSpare = h.SequenceNumber<<8 | uint32(spareAndMP)
	if err := binary.Write(buffer, binary.BigEndian, &snAndSpare); err != nil {
		logger.PFCPLog.Warnf("Binary write error: %+v", err)
	}
	return buffer.Bytes(), nil
}

func (h *Header) UnmarshalBinary(data []byte) error {
	var tmpBuf uint8
	byteReader := bytes.NewReader(data)
	if err := binary.Read(byteReader, binary.BigEndian, &tmpBuf); err != nil {
		return errors.New("")
	}
	h.Version, h.MP, h.S = tmpBuf>>5, (tmpBuf&0x02)>>1, tmpBuf&0x01
	if err := binary.Read(byteReader, binary.BigEndian, &h.MessageType); err != nil {
		logger.PFCPLog.Warnf("Binary write error: %+v", err)
	}
	if err := binary.Read(byteReader, binary.BigEndian, &h.MessageLength); err != nil {
		logger.PFCPLog.Warnf("Binary write error: %+v", err)
	}
	if h.S&1 != 0 {
		if err := binary.Read(byteReader, binary.BigEndian, &h.SEID); err != nil {
			logger.PFCPLog.Warnf("Binary write error: %+v", err)
		}
	}
	var snAndSpare uint32
	if err := binary.Read(byteReader, binary.BigEndian, &snAndSpare); err != nil {
		logger.PFCPLog.Warnf("Binary write error: %+v", err)
	}

	h.SequenceNumber = snAndSpare >> 8

	if h.MP&1 != 0 {
		h.MessagePriority = uint8(snAndSpare&0x00FF) >> 4
	}
	return nil
}

func (h *Header) Len() int {
	// Node Related Header
	if int(h.MessageType) < 50 {
		return 8
	}
	return 16
}

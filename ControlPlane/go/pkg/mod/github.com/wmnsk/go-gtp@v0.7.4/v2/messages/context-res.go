// Copyright 2019-2020 go-gtp authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

package messages

import (
	"github.com/wmnsk/go-gtp/v2/ies"
)

// ContextResponse is a ContextResponse Header and its IEs above.
type ContextResponse struct {
	*Header
	Cause                           *ies.IE
	IMSI                            *ies.IE
	UEMMContext                     *ies.IE
	UEPDNConnections                *ies.IE
	SenderFTEID                     *ies.IE
	SGWS11S4FTEID                   *ies.IE
	SGWNodeName                     *ies.IE
	IndicationFlags                 *ies.IE
	TraceInformation                *ies.IE
	S101IPAddress                   *ies.IE
	S102IPAddress                   *ies.IE
	SubscribedRFSPIndex             *ies.IE
	RFSPIndexInUse                  *ies.IE
	UETimeZone                      *ies.IE
	MMESGSNLDN                      *ies.IE
	MDTConfiguration                *ies.IE
	SGSNNodeName                    *ies.IE
	MMENodeName                     *ies.IE
	UCI                             *ies.IE
	MonitoringEventInformation      *ies.IE
	UEUsageType                     *ies.IE
	SCEFPDNConnection               *ies.IE
	RATType                         *ies.IE
	ServingPLMNRateControl          *ies.IE
	MOExceptionDataCounter          *ies.IE
	RemainingRunningServiceGapTimer *ies.IE
	ExtendedTraceInformation        *ies.IE
	PrivateExtension                *ies.IE
	AdditionalIEs                   []*ies.IE
}

// NewContextResponse creates a new ContextResponse.
func NewContextResponse(teid, seq uint32, ie ...*ies.IE) *ContextResponse {
	c := &ContextResponse{
		Header: NewHeader(
			NewHeaderFlags(2, 0, 1),
			MsgTypeContextResponse, teid, seq, nil,
		),
	}

	for _, i := range ie {
		if i == nil {
			continue
		}
		switch i.Type {
		case ies.Cause:
			c.Cause = i
		case ies.IMSI:
			c.IMSI = i
		case ies.MMContextEPSSecurityContextQuadrupletsAndQuintuplets,
			ies.MMContextGSMKeyAndTriplets, ies.MMContextGSMKeyUsedCipherAndQuintuplets,
			ies.MMContextUMTSKeyAndQuintuplets, ies.MMContextUMTSKeyQuadrupletsAndQuintuplets,
			ies.MMContextUMTSKeyUsedCipherAndQuintuplets:
			if c.UEMMContext != nil {
				c.UEMMContext = i
			} else {
				c.AdditionalIEs = append(c.AdditionalIEs, i)
			}
		case ies.PDNConnection:
			c.UEPDNConnections = i
		case ies.FullyQualifiedTEID:
			switch i.Instance() {
			case 0:
				c.SenderFTEID = i
			case 1:
				c.SGWS11S4FTEID = i
			default:
				c.AdditionalIEs = append(c.AdditionalIEs, i)
			}
		case ies.FullyQualifiedDomainName:
			switch i.Instance() {
			case 0:
				c.SGWNodeName = i
			case 1:
				c.SGSNNodeName = i
			case 2:
				c.MMENodeName = i
			default:
				c.AdditionalIEs = append(c.AdditionalIEs, i)
			}
		case ies.Indication:
			c.IndicationFlags = i
		case ies.TraceInformation:
			c.TraceInformation = i
		case ies.IPAddress:
			switch i.Instance() {
			case 0:
				c.S101IPAddress = i
			case 1:
				c.S102IPAddress = i
			default:
				c.AdditionalIEs = append(c.AdditionalIEs, i)
			}
		case ies.RFSPIndex:
			switch i.Instance() {
			case 0:
				c.SubscribedRFSPIndex = i
			case 1:
				c.RFSPIndexInUse = i
			default:
				c.AdditionalIEs = append(c.AdditionalIEs, i)
			}
		case ies.UETimeZone:
			c.UETimeZone = i
		case ies.LocalDistinguishedName:
			c.MMESGSNLDN = i
		case ies.MDTConfiguration:
			c.MDTConfiguration = i
		case ies.UserCSGInformation:
			c.UCI = i
		case ies.MonitoringEventInformation:
			c.MonitoringEventInformation = i
		case ies.IntegerNumber:
			switch i.Instance() {
			case 0:
				c.UEUsageType = i
			case 1:
				c.RemainingRunningServiceGapTimer = i
			default:
				c.AdditionalIEs = append(c.AdditionalIEs, i)
			}
		case ies.SCEFPDNConnection:
			c.SCEFPDNConnection = i
		case ies.RATType:
			c.RATType = i
		case ies.ServingPLMNRateControl:
			c.ServingPLMNRateControl = i
		case ies.Counter:
			c.MOExceptionDataCounter = i
		case ies.ExtendedTraceInformation:
			c.ExtendedTraceInformation = i
		case ies.PrivateExtension:
			c.PrivateExtension = i
		default:
			c.AdditionalIEs = append(c.AdditionalIEs, i)
		}
	}

	c.SetLength()
	return c
}

// Marshal serializes ContextResponse into bytes.
func (c *ContextResponse) Marshal() ([]byte, error) {
	b := make([]byte, c.MarshalLen())
	if err := c.MarshalTo(b); err != nil {
		return nil, err
	}
	return b, nil
}

// MarshalTo serializes ContextResponse into bytes.
func (c *ContextResponse) MarshalTo(b []byte) error {
	if c.Header.Payload != nil {
		c.Header.Payload = nil
	}
	c.Header.Payload = make([]byte, c.MarshalLen()-c.Header.MarshalLen())

	offset := 0
	if ie := c.Cause; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := c.IMSI; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := c.UEMMContext; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := c.UEPDNConnections; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := c.SenderFTEID; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := c.SGWS11S4FTEID; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := c.SGWNodeName; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := c.IndicationFlags; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := c.TraceInformation; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := c.S101IPAddress; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := c.S102IPAddress; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := c.SubscribedRFSPIndex; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := c.RFSPIndexInUse; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := c.UETimeZone; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := c.MMESGSNLDN; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := c.MDTConfiguration; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := c.SGSNNodeName; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := c.MMENodeName; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := c.UCI; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := c.MonitoringEventInformation; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := c.UEUsageType; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := c.SCEFPDNConnection; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := c.RATType; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := c.ServingPLMNRateControl; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := c.MOExceptionDataCounter; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := c.RemainingRunningServiceGapTimer; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := c.ExtendedTraceInformation; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := c.PrivateExtension; ie != nil {
		if err := ie.MarshalTo(c.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}

	for _, ie := range c.AdditionalIEs {
		if ie == nil {
			continue
		}
		if err := ie.MarshalTo(c.Header.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}

	c.Header.SetLength()
	return c.Header.MarshalTo(b)
}

// ParseContextResponse decodes given bytes as ContextResponse.
func ParseContextResponse(b []byte) (*ContextResponse, error) {
	c := &ContextResponse{}
	if err := c.UnmarshalBinary(b); err != nil {
		return nil, err
	}
	return c, nil
}

// UnmarshalBinary decodes given bytes as ContextResponse.
func (c *ContextResponse) UnmarshalBinary(b []byte) error {
	var err error
	c.Header, err = ParseHeader(b)
	if err != nil {
		return err
	}
	if len(c.Header.Payload) < 2 {
		return nil
	}

	decodedIEs, err := ies.ParseMultiIEs(c.Header.Payload)
	if err != nil {
		return err
	}
	for _, i := range decodedIEs {
		if i == nil {
			continue
		}
		switch i.Type {
		case ies.Cause:
			c.Cause = i
		case ies.IMSI:
			c.IMSI = i
		case ies.MMContextEPSSecurityContextQuadrupletsAndQuintuplets,
			ies.MMContextGSMKeyAndTriplets, ies.MMContextGSMKeyUsedCipherAndQuintuplets,
			ies.MMContextUMTSKeyAndQuintuplets, ies.MMContextUMTSKeyQuadrupletsAndQuintuplets,
			ies.MMContextUMTSKeyUsedCipherAndQuintuplets:
			if c.UEMMContext != nil {
				c.UEMMContext = i
			} else {
				c.AdditionalIEs = append(c.AdditionalIEs, i)
			}
		case ies.PDNConnection:
			c.UEPDNConnections = i
		case ies.FullyQualifiedTEID:
			switch i.Instance() {
			case 0:
				c.SenderFTEID = i
			case 1:
				c.SGWS11S4FTEID = i
			default:
				c.AdditionalIEs = append(c.AdditionalIEs, i)
			}
		case ies.FullyQualifiedDomainName:
			switch i.Instance() {
			case 0:
				c.SGWNodeName = i
			case 1:
				c.SGSNNodeName = i
			case 2:
				c.MMENodeName = i
			default:
				c.AdditionalIEs = append(c.AdditionalIEs, i)
			}
		case ies.Indication:
			c.IndicationFlags = i
		case ies.TraceInformation:
			c.TraceInformation = i
		case ies.IPAddress:
			switch i.Instance() {
			case 0:
				c.S101IPAddress = i
			case 1:
				c.S102IPAddress = i
			default:
				c.AdditionalIEs = append(c.AdditionalIEs, i)
			}
		case ies.RFSPIndex:
			switch i.Instance() {
			case 0:
				c.SubscribedRFSPIndex = i
			case 1:
				c.RFSPIndexInUse = i
			default:
				c.AdditionalIEs = append(c.AdditionalIEs, i)
			}
		case ies.UETimeZone:
			c.UETimeZone = i
		case ies.LocalDistinguishedName:
			c.MMESGSNLDN = i
		case ies.MDTConfiguration:
			c.MDTConfiguration = i
		case ies.UserCSGInformation:
			c.UCI = i
		case ies.MonitoringEventInformation:
			c.MonitoringEventInformation = i
		case ies.IntegerNumber:
			switch i.Instance() {
			case 0:
				c.UEUsageType = i
			case 1:
				c.RemainingRunningServiceGapTimer = i
			default:
				c.AdditionalIEs = append(c.AdditionalIEs, i)
			}
		case ies.SCEFPDNConnection:
			c.SCEFPDNConnection = i
		case ies.RATType:
			c.RATType = i
		case ies.ServingPLMNRateControl:
			c.ServingPLMNRateControl = i
		case ies.Counter:
			c.MOExceptionDataCounter = i
		case ies.ExtendedTraceInformation:
			c.ExtendedTraceInformation = i
		case ies.PrivateExtension:
			c.PrivateExtension = i
		default:
			c.AdditionalIEs = append(c.AdditionalIEs, i)
		}
	}

	return nil
}

// MarshalLen returns the serial length in int.
func (c *ContextResponse) MarshalLen() int {
	l := c.Header.MarshalLen() - len(c.Header.Payload)

	if ie := c.Cause; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := c.IMSI; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := c.UEMMContext; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := c.UEPDNConnections; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := c.SenderFTEID; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := c.SGWS11S4FTEID; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := c.SGWNodeName; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := c.IndicationFlags; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := c.TraceInformation; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := c.S101IPAddress; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := c.S102IPAddress; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := c.SubscribedRFSPIndex; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := c.RFSPIndexInUse; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := c.UETimeZone; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := c.MMESGSNLDN; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := c.MDTConfiguration; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := c.SGSNNodeName; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := c.MMENodeName; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := c.UCI; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := c.MonitoringEventInformation; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := c.UEUsageType; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := c.SCEFPDNConnection; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := c.RATType; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := c.ServingPLMNRateControl; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := c.MOExceptionDataCounter; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := c.RemainingRunningServiceGapTimer; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := c.ExtendedTraceInformation; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := c.PrivateExtension; ie != nil {
		l += ie.MarshalLen()
	}

	for _, ie := range c.AdditionalIEs {
		if ie == nil {
			continue
		}
		l += ie.MarshalLen()
	}
	return l
}

// SetLength sets the length in Length field.
func (c *ContextResponse) SetLength() {
	c.Header.Length = uint16(c.MarshalLen() - 4)
}

// MessageTypeName returns the name of protocol.
func (c *ContextResponse) MessageTypeName() string {
	return "Context Response"
}

// TEID returns the TEID in uint32.
func (c *ContextResponse) TEID() uint32 {
	return c.Header.teid()
}

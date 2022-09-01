// Copyright 2019-2020 go-gtp authors. All rights reservev.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

package messages

import "github.com/wmnsk/go-gtp/v2/ies"

// ModifyAccessBearersRequest is a ModifyAccessBearersRequest Header and its IEs above.
type ModifyAccessBearersRequest struct {
	*Header
	IndicationFlags                        *ies.IE
	SenderFTEIDC                           *ies.IE
	DelayDownlinkPacketNotificationRequest *ies.IE
	BearerContextsToBeModified             *ies.IE
	BearerContextsToBeRemoved              *ies.IE
	Recovery                               *ies.IE
	SecondaryRATUsageDataReport            *ies.IE
	PrivateExtension                       *ies.IE
	AdditionalIEs                          []*ies.IE
}

// NewModifyAccessBearersRequest creates a new ModifyAccessBearersRequest.
func NewModifyAccessBearersRequest(teid, seq uint32, ie ...*ies.IE) *ModifyAccessBearersRequest {
	m := &ModifyAccessBearersRequest{
		Header: NewHeader(
			NewHeaderFlags(2, 0, 1),
			MsgTypeModifyAccessBearersRequest, teid, seq, nil,
		),
	}

	for _, i := range ie {
		if i == nil {
			continue
		}
		switch i.Type {
		case ies.Indication:
			m.IndicationFlags = i
		case ies.NodeType:
			m.SenderFTEIDC = i
		case ies.DelayValue:
			m.DelayDownlinkPacketNotificationRequest = i
		case ies.BearerContext:
			switch i.Instance() {
			case 0:
				m.BearerContextsToBeModified = i
			case 1:
				m.BearerContextsToBeRemoved = i
			}
		case ies.Recovery:
			m.Recovery = i
		case ies.SecondaryRATUsageDataReport:
			m.SecondaryRATUsageDataReport = i
		case ies.PrivateExtension:
			m.PrivateExtension = i
		default:
			m.AdditionalIEs = append(m.AdditionalIEs, i)
		}
	}

	m.SetLength()
	return m
}

// Marshal serializes ModifyAccessBearersRequest into bytes.
func (m *ModifyAccessBearersRequest) Marshal() ([]byte, error) {
	b := make([]byte, m.MarshalLen())
	if err := m.MarshalTo(b); err != nil {
		return nil, err
	}
	return b, nil
}

// MarshalTo serializes ModifyAccessBearersRequest into bytes.
func (m *ModifyAccessBearersRequest) MarshalTo(b []byte) error {
	if m.Header.Payload != nil {
		m.Header.Payload = nil
	}
	m.Header.Payload = make([]byte, m.MarshalLen()-m.Header.MarshalLen())

	offset := 0
	if ie := m.IndicationFlags; ie != nil {
		if err := ie.MarshalTo(m.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := m.SenderFTEIDC; ie != nil {
		if err := ie.MarshalTo(m.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := m.DelayDownlinkPacketNotificationRequest; ie != nil {
		if err := ie.MarshalTo(m.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := m.BearerContextsToBeModified; ie != nil {
		if err := ie.MarshalTo(m.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := m.BearerContextsToBeRemoved; ie != nil {
		if err := ie.MarshalTo(m.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := m.Recovery; ie != nil {
		if err := ie.MarshalTo(m.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := m.SecondaryRATUsageDataReport; ie != nil {
		if err := ie.MarshalTo(m.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := m.PrivateExtension; ie != nil {
		if err := ie.MarshalTo(m.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}

	for _, ie := range m.AdditionalIEs {
		if ie == nil {
			continue
		}
		if err := ie.MarshalTo(m.Header.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}

	m.Header.SetLength()
	return m.Header.MarshalTo(b)
}

// ParseModifyAccessBearersRequest decodes given bytes as ModifyAccessBearersRequest.
func ParseModifyAccessBearersRequest(b []byte) (*ModifyAccessBearersRequest, error) {
	m := &ModifyAccessBearersRequest{}
	if err := m.UnmarshalBinary(b); err != nil {
		return nil, err
	}
	return m, nil
}

// UnmarshalBinary decodes given bytes as ModifyAccessBearersRequest.
func (m *ModifyAccessBearersRequest) UnmarshalBinary(b []byte) error {
	var err error
	m.Header, err = ParseHeader(b)
	if err != nil {
		return err
	}
	if len(m.Header.Payload) < 2 {
		return nil
	}

	decodedIEs, err := ies.ParseMultiIEs(m.Header.Payload)
	if err != nil {
		return err
	}
	for _, i := range decodedIEs {
		if i == nil {
			continue
		}
		switch i.Type {
		case ies.Indication:
			m.IndicationFlags = i
		case ies.NodeType:
			m.SenderFTEIDC = i
		case ies.DelayValue:
			m.DelayDownlinkPacketNotificationRequest = i
		case ies.BearerContext:
			switch i.Instance() {
			case 0:
				m.BearerContextsToBeModified = i
			case 1:
				m.BearerContextsToBeRemoved = i
			}
		case ies.Recovery:
			m.Recovery = i
		case ies.SecondaryRATUsageDataReport:
			m.SecondaryRATUsageDataReport = i
		case ies.PrivateExtension:
			m.PrivateExtension = i
		default:
			m.AdditionalIEs = append(m.AdditionalIEs, i)
		}
	}

	return nil
}

// MarshalLen returns the serial length in int.
func (m *ModifyAccessBearersRequest) MarshalLen() int {
	l := m.Header.MarshalLen() - len(m.Header.Payload)
	if ie := m.IndicationFlags; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := m.SenderFTEIDC; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := m.DelayDownlinkPacketNotificationRequest; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := m.BearerContextsToBeModified; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := m.BearerContextsToBeRemoved; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := m.Recovery; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := m.SecondaryRATUsageDataReport; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := m.PrivateExtension; ie != nil {
		l += ie.MarshalLen()
	}

	for _, ie := range m.AdditionalIEs {
		if ie == nil {
			continue
		}
		l += ie.MarshalLen()
	}
	return l
}

// SetLength sets the length in Length field.
func (m *ModifyAccessBearersRequest) SetLength() {
	m.Header.Length = uint16(m.MarshalLen() - 4)
}

// MessageTypeName returns the name of protocol.
func (m *ModifyAccessBearersRequest) MessageTypeName() string {
	return "Modify Access Bearers Request"
}

// TEID returns the TEID in uint32.
func (m *ModifyAccessBearersRequest) TEID() uint32 {
	return m.Header.teid()
}

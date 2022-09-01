// Copyright 2019-2020 go-gtp authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

package messages

import (
	"github.com/wmnsk/go-gtp/v2/ies"
)

// DeleteSessionResponse is a DeleteSessionResponse Header and its IEs above.
type DeleteSessionResponse struct {
	*Header
	Cause                         *ies.IE
	Recovery                      *ies.IE
	PCO                           *ies.IE
	IndicationFlags               *ies.IE
	PGWNodeLoadControlInformation *ies.IE
	PGWAPNLoadControlInformation  *ies.IE
	SGWNodeLoadControlInformation *ies.IE
	PGWOverloadControlInformation *ies.IE
	SGWOverloadControlInformation *ies.IE
	EPCO                          *ies.IE
	APNRateControlStatus          *ies.IE
	PrivateExtension              *ies.IE
	AdditionalIEs                 []*ies.IE
}

// NewDeleteSessionResponse creates a new DeleteSessionResponse.
func NewDeleteSessionResponse(teid, seq uint32, ie ...*ies.IE) *DeleteSessionResponse {
	d := &DeleteSessionResponse{
		Header: NewHeader(
			NewHeaderFlags(2, 0, 1),
			MsgTypeDeleteSessionResponse, teid, seq, nil,
		),
	}

	for _, i := range ie {
		if i == nil {
			continue
		}
		switch i.Type {
		case ies.Cause:
			d.Cause = i
		case ies.Recovery:
			d.Recovery = i
		case ies.ProtocolConfigurationOptions:
			d.PCO = i
		case ies.Indication:
			d.IndicationFlags = i
		case ies.LoadControlInformation:
			switch i.Instance() {
			case 1:
				d.PGWNodeLoadControlInformation = i
			case 2:
				d.PGWAPNLoadControlInformation = i
			case 3:
				d.SGWNodeLoadControlInformation = i
			default:
				d.AdditionalIEs = append(d.AdditionalIEs, i)
			}
		case ies.OverloadControlInformation:
			switch i.Instance() {
			case 1:
				d.PGWOverloadControlInformation = i
			case 2:
				d.SGWOverloadControlInformation = i
			default:
				d.AdditionalIEs = append(d.AdditionalIEs, i)
			}
		case ies.ExtendedProtocolConfigurationOptions:
			d.EPCO = i
		case ies.APNRateControlStatus:
			d.APNRateControlStatus = i
		case ies.PrivateExtension:
			d.PrivateExtension = i
		default:
			d.AdditionalIEs = append(d.AdditionalIEs, i)
		}
	}

	d.SetLength()
	return d
}

// Marshal serializes DeleteSessionResponse into bytes.
func (d *DeleteSessionResponse) Marshal() ([]byte, error) {
	b := make([]byte, d.MarshalLen())
	if err := d.MarshalTo(b); err != nil {
		return nil, err
	}
	return b, nil
}

// MarshalTo serializes DeleteSessionResponse into bytes.
func (d *DeleteSessionResponse) MarshalTo(b []byte) error {
	if d.Header.Payload != nil {
		d.Header.Payload = nil
	}
	d.Header.Payload = make([]byte, d.MarshalLen()-d.Header.MarshalLen())

	offset := 0
	if ie := d.Cause; ie != nil {
		if err := ie.MarshalTo(d.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := d.Recovery; ie != nil {
		if err := ie.MarshalTo(d.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := d.PCO; ie != nil {
		if err := ie.MarshalTo(d.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := d.IndicationFlags; ie != nil {
		if err := ie.MarshalTo(d.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := d.PGWNodeLoadControlInformation; ie != nil {
		if err := ie.MarshalTo(d.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := d.PGWAPNLoadControlInformation; ie != nil {
		if err := ie.MarshalTo(d.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := d.SGWNodeLoadControlInformation; ie != nil {
		if err := ie.MarshalTo(d.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := d.PGWOverloadControlInformation; ie != nil {
		if err := ie.MarshalTo(d.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := d.SGWOverloadControlInformation; ie != nil {
		if err := ie.MarshalTo(d.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := d.EPCO; ie != nil {
		if err := ie.MarshalTo(d.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := d.APNRateControlStatus; ie != nil {
		if err := ie.MarshalTo(d.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := d.PrivateExtension; ie != nil {
		if err := ie.MarshalTo(d.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}

	for _, ie := range d.AdditionalIEs {
		if ie == nil {
			continue
		}
		if err := ie.MarshalTo(d.Header.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}

	d.Header.SetLength()
	return d.Header.MarshalTo(b)
}

// ParseDeleteSessionResponse decodes given bytes as DeleteSessionResponse.
func ParseDeleteSessionResponse(b []byte) (*DeleteSessionResponse, error) {
	d := &DeleteSessionResponse{}
	if err := d.UnmarshalBinary(b); err != nil {
		return nil, err
	}
	return d, nil
}

// UnmarshalBinary decodes given bytes as DeleteSessionResponse.
func (d *DeleteSessionResponse) UnmarshalBinary(b []byte) error {
	var err error
	d.Header, err = ParseHeader(b)
	if err != nil {
		return err
	}
	if len(d.Header.Payload) < 2 {
		return nil
	}

	decodedIEs, err := ies.ParseMultiIEs(d.Header.Payload)
	if err != nil {
		return err
	}

	for _, i := range decodedIEs {
		if i == nil {
			continue
		}
		switch i.Type {
		case ies.Cause:
			d.Cause = i
		case ies.Recovery:
			d.Recovery = i
		case ies.ProtocolConfigurationOptions:
			d.PCO = i
		case ies.Indication:
			d.IndicationFlags = i
		case ies.LoadControlInformation:
			switch i.Instance() {
			case 1:
				d.PGWNodeLoadControlInformation = i
			case 2:
				d.PGWAPNLoadControlInformation = i
			case 3:
				d.SGWNodeLoadControlInformation = i
			default:
				d.AdditionalIEs = append(d.AdditionalIEs, i)
			}
		case ies.OverloadControlInformation:
			switch i.Instance() {
			case 1:
				d.PGWOverloadControlInformation = i
			case 2:
				d.SGWOverloadControlInformation = i
			default:
				d.AdditionalIEs = append(d.AdditionalIEs, i)
			}
		case ies.ExtendedProtocolConfigurationOptions:
			d.EPCO = i
		case ies.APNRateControlStatus:
			d.APNRateControlStatus = i
		case ies.PrivateExtension:
			d.PrivateExtension = i
		default:
			d.AdditionalIEs = append(d.AdditionalIEs, i)
		}
	}

	return nil
}

// MarshalLen returns the serial length in int.
func (d *DeleteSessionResponse) MarshalLen() int {
	l := d.Header.MarshalLen() - len(d.Header.Payload)

	if ie := d.Cause; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := d.Recovery; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := d.PCO; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := d.IndicationFlags; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := d.PGWNodeLoadControlInformation; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := d.PGWAPNLoadControlInformation; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := d.SGWNodeLoadControlInformation; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := d.PGWOverloadControlInformation; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := d.SGWOverloadControlInformation; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := d.EPCO; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := d.APNRateControlStatus; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := d.PrivateExtension; ie != nil {
		l += ie.MarshalLen()
	}

	for _, ie := range d.AdditionalIEs {
		if ie == nil {
			continue
		}
		l += ie.MarshalLen()
	}
	return l
}

// SetLength sets the length in Length field.
func (d *DeleteSessionResponse) SetLength() {
	d.Header.Length = uint16(d.MarshalLen() - 4)
}

// MessageTypeName returns the name of protocol.
func (d *DeleteSessionResponse) MessageTypeName() string {
	return "Delete Session Response"
}

// TEID returns the TEID in uint32.
func (d *DeleteSessionResponse) TEID() uint32 {
	return d.Header.teid()
}

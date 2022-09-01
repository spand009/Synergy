// Copyright 2019-2020 go-gtp authors. All rights reservev.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

package messages

import "github.com/wmnsk/go-gtp/v2/ies"

// ReleaseAccessBearersResponse is a ReleaseAccessBearersResponse Header and its IEs above.
type ReleaseAccessBearersResponse struct {
	*Header
	Cause                         *ies.IE
	IndicationFlags               *ies.IE
	SGWNodeLoadControlInformation *ies.IE
	SGWOverloadControlInformation *ies.IE
	PrivateExtension              *ies.IE
	AdditionalIEs                 []*ies.IE
}

// NewReleaseAccessBearersResponse creates a new ReleaseAccessBearersResponse.
func NewReleaseAccessBearersResponse(teid, seq uint32, ie ...*ies.IE) *ReleaseAccessBearersResponse {
	r := &ReleaseAccessBearersResponse{
		Header: NewHeader(
			NewHeaderFlags(2, 0, 1),
			MsgTypeReleaseAccessBearersResponse, teid, seq, nil,
		),
	}

	for _, i := range ie {
		if i == nil {
			continue
		}
		switch i.Type {
		case ies.Cause:
			r.Cause = i
		case ies.Indication:
			r.IndicationFlags = i
		case ies.LoadControlInformation:
			r.SGWNodeLoadControlInformation = i
		case ies.OverloadControlInformation:
			r.SGWOverloadControlInformation = i
		case ies.PrivateExtension:
			r.PrivateExtension = i
		default:
			r.AdditionalIEs = append(r.AdditionalIEs, i)
		}
	}

	r.SetLength()
	return r
}

// Marshal serializes ReleaseAccessBearersResponse into bytes.
func (r *ReleaseAccessBearersResponse) Marshal() ([]byte, error) {
	b := make([]byte, r.MarshalLen())
	if err := r.MarshalTo(b); err != nil {
		return nil, err
	}
	return b, nil
}

// MarshalTo serializes ReleaseAccessBearersResponse into bytes.
func (r *ReleaseAccessBearersResponse) MarshalTo(b []byte) error {
	if r.Header.Payload != nil {
		r.Header.Payload = nil
	}
	r.Header.Payload = make([]byte, r.MarshalLen()-r.Header.MarshalLen())

	offset := 0
	if ie := r.Cause; ie != nil {
		if err := ie.MarshalTo(r.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := r.IndicationFlags; ie != nil {
		if err := ie.MarshalTo(r.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := r.SGWNodeLoadControlInformation; ie != nil {
		if err := ie.MarshalTo(r.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := r.SGWOverloadControlInformation; ie != nil {
		if err := ie.MarshalTo(r.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := r.PrivateExtension; ie != nil {
		if err := ie.MarshalTo(r.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}

	for _, ie := range r.AdditionalIEs {
		if ie == nil {
			continue
		}
		if err := ie.MarshalTo(r.Header.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}

	r.Header.SetLength()
	return r.Header.MarshalTo(b)
}

// ParseReleaseAccessBearersResponse decodes given bytes as ReleaseAccessBearersResponse.
func ParseReleaseAccessBearersResponse(b []byte) (*ReleaseAccessBearersResponse, error) {
	r := &ReleaseAccessBearersResponse{}
	if err := r.UnmarshalBinary(b); err != nil {
		return nil, err
	}
	return r, nil
}

// UnmarshalBinary decodes given bytes as ReleaseAccessBearersResponse.
func (r *ReleaseAccessBearersResponse) UnmarshalBinary(b []byte) error {
	var err error
	r.Header, err = ParseHeader(b)
	if err != nil {
		return err
	}
	if len(r.Header.Payload) < 2 {
		return nil
	}

	decodedIEs, err := ies.ParseMultiIEs(r.Header.Payload)
	if err != nil {
		return err
	}
	for _, i := range decodedIEs {
		if i == nil {
			continue
		}
		switch i.Type {
		case ies.Cause:
			r.Cause = i
		case ies.Indication:
			r.IndicationFlags = i
		case ies.LoadControlInformation:
			r.SGWNodeLoadControlInformation = i
		case ies.OverloadControlInformation:
			r.SGWOverloadControlInformation = i
		case ies.PrivateExtension:
			r.PrivateExtension = i
		default:
			r.AdditionalIEs = append(r.AdditionalIEs, i)
		}
	}

	return nil
}

// MarshalLen returns the serial length in int.
func (r *ReleaseAccessBearersResponse) MarshalLen() int {
	l := r.Header.MarshalLen() - len(r.Header.Payload)
	if ie := r.Cause; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := r.IndicationFlags; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := r.SGWNodeLoadControlInformation; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := r.SGWOverloadControlInformation; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := r.PrivateExtension; ie != nil {
		l += ie.MarshalLen()
	}

	for _, ie := range r.AdditionalIEs {
		if ie == nil {
			continue
		}
		l += ie.MarshalLen()
	}
	return l
}

// SetLength sets the length in Length field.
func (r *ReleaseAccessBearersResponse) SetLength() {
	r.Header.Length = uint16(r.MarshalLen() - 4)
}

// MessageTypeName returns the name of protocol.
func (r *ReleaseAccessBearersResponse) MessageTypeName() string {
	return "Release Access Bearers Response"
}

// TEID returns the TEID in uint32.
func (r *ReleaseAccessBearersResponse) TEID() uint32 {
	return r.Header.teid()
}

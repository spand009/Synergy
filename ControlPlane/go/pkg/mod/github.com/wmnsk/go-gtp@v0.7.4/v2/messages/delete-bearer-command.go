// Copyright 2019-2020 go-gtp authors. All rights reservev.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

package messages

import "github.com/wmnsk/go-gtp/v2/ies"

// DeleteBearerCommand is a DeleteBearerCommand Header and its IEs above.
type DeleteBearerCommand struct {
	*Header
	BearerContexts                     *ies.IE
	ULI                                *ies.IE
	ULITimestamp                       *ies.IE
	UETimeZone                         *ies.IE
	MMESGSNOverloadControlInformation  *ies.IE
	SGWOverloadControlInformation      *ies.IE
	TWANePDGOverloadControlInformation *ies.IE
	SenderFTEIDC                       *ies.IE
	SecondaryRATDataUsageReport        *ies.IE
	PrivateExtension                   *ies.IE
	AdditionalIEs                      []*ies.IE
}

// NewDeleteBearerCommand creates a new DeleteBearerCommand.
func NewDeleteBearerCommand(teid, seq uint32, ie ...*ies.IE) *DeleteBearerCommand {
	d := &DeleteBearerCommand{
		Header: NewHeader(
			NewHeaderFlags(2, 0, 1),
			MsgTypeDeleteBearerCommand, teid, seq, nil,
		),
	}

	for _, i := range ie {
		if i == nil {
			continue
		}
		switch i.Type {
		case ies.BearerContext:
			d.BearerContexts = i
		case ies.UserLocationInformation:
			d.ULI = i
		case ies.ULITimestamp:
			d.ULITimestamp = i
		case ies.UETimeZone:
			d.UETimeZone = i
		case ies.OverloadControlInformation:
			switch i.Instance() {
			case 0:
				d.MMESGSNOverloadControlInformation = i
			case 1:
				d.SGWOverloadControlInformation = i
			case 2:
				d.TWANePDGOverloadControlInformation = i
			}
		case ies.FullyQualifiedTEID:
			d.SenderFTEIDC = i
		case ies.SecondaryRATUsageDataReport:
			d.SecondaryRATDataUsageReport = i
		case ies.PrivateExtension:
			d.PrivateExtension = i
		default:
			d.AdditionalIEs = append(d.AdditionalIEs, i)
		}
	}

	d.SetLength()
	return d
}

// Marshal serializes DeleteBearerCommand into bytes.
func (d *DeleteBearerCommand) Marshal() ([]byte, error) {
	b := make([]byte, d.MarshalLen())
	if err := d.MarshalTo(b); err != nil {
		return nil, err
	}
	return b, nil
}

// MarshalTo serializes DeleteBearerCommand into bytes.
func (d *DeleteBearerCommand) MarshalTo(b []byte) error {
	if d.Header.Payload != nil {
		d.Header.Payload = nil
	}
	d.Header.Payload = make([]byte, d.MarshalLen()-d.Header.MarshalLen())

	offset := 0
	if ie := d.BearerContexts; ie != nil {
		if err := ie.MarshalTo(d.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := d.ULI; ie != nil {
		if err := ie.MarshalTo(d.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := d.ULITimestamp; ie != nil {
		if err := ie.MarshalTo(d.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := d.UETimeZone; ie != nil {
		if err := ie.MarshalTo(d.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := d.MMESGSNOverloadControlInformation; ie != nil {
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
	if ie := d.TWANePDGOverloadControlInformation; ie != nil {
		if err := ie.MarshalTo(d.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := d.SenderFTEIDC; ie != nil {
		if err := ie.MarshalTo(d.Payload[offset:]); err != nil {
			return err
		}
		offset += ie.MarshalLen()
	}
	if ie := d.SecondaryRATDataUsageReport; ie != nil {
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

// ParseDeleteBearerCommand decodes given bytes as DeleteBearerCommand.
func ParseDeleteBearerCommand(b []byte) (*DeleteBearerCommand, error) {
	d := &DeleteBearerCommand{}
	if err := d.UnmarshalBinary(b); err != nil {
		return nil, err
	}
	return d, nil
}

// UnmarshalBinary decodes given bytes as DeleteBearerCommand.
func (d *DeleteBearerCommand) UnmarshalBinary(b []byte) error {
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
		case ies.BearerContext:
			d.BearerContexts = i
		case ies.UserLocationInformation:
			d.ULI = i
		case ies.ULITimestamp:
			d.ULITimestamp = i
		case ies.UETimeZone:
			d.UETimeZone = i
		case ies.OverloadControlInformation:
			switch i.Instance() {
			case 0:
				d.MMESGSNOverloadControlInformation = i
			case 1:
				d.SGWOverloadControlInformation = i
			case 2:
				d.TWANePDGOverloadControlInformation = i
			}
		case ies.FullyQualifiedTEID:
			d.SenderFTEIDC = i
		case ies.SecondaryRATUsageDataReport:
			d.SecondaryRATDataUsageReport = i
		case ies.PrivateExtension:
			d.PrivateExtension = i
		default:
			d.AdditionalIEs = append(d.AdditionalIEs, i)
		}
	}

	return nil
}

// MarshalLen returns the serial length in int.
func (d *DeleteBearerCommand) MarshalLen() int {
	l := d.Header.MarshalLen() - len(d.Header.Payload)
	if ie := d.BearerContexts; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := d.ULI; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := d.ULITimestamp; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := d.UETimeZone; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := d.MMESGSNOverloadControlInformation; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := d.SGWOverloadControlInformation; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := d.TWANePDGOverloadControlInformation; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := d.SenderFTEIDC; ie != nil {
		l += ie.MarshalLen()
	}
	if ie := d.SecondaryRATDataUsageReport; ie != nil {
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
func (d *DeleteBearerCommand) SetLength() {
	d.Header.Length = uint16(d.MarshalLen() - 4)
}

// MessageTypeName returns the name of protocol.
func (d *DeleteBearerCommand) MessageTypeName() string {
	return "Delete Bearer Command"
}

// TEID returns the TEID in uint32.
func (d *DeleteBearerCommand) TEID() uint32 {
	return d.Header.teid()
}

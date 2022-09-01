// Copyright 2019-2020 go-gtp authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

package ies

import (
	"encoding/binary"
	"io"

	"github.com/wmnsk/go-gtp/utils"
)

// NewGUTI creates a new GUTI IE.
func NewGUTI(mcc, mnc string, groupID uint16, code uint8, mTMSI uint32) *IE {
	i := New(GUTI, 0x00, make([]byte, 10))
	plmn, err := utils.EncodePLMN(mcc, mnc)
	if err != nil {
		return nil
	}
	copy(i.Payload[0:3], plmn)
	binary.BigEndian.PutUint16(i.Payload[3:5], groupID)
	i.Payload[5] = code
	binary.BigEndian.PutUint32(i.Payload[6:10], mTMSI)
	return i
}

// MMEGroupID returns MMEGroupID in uint16 if the type of IE matches.
func (i *IE) MMEGroupID() (uint16, error) {
	switch i.Type {
	case GUTI:
		if len(i.Payload) < 5 {
			return 0, io.ErrUnexpectedEOF
		}
		return binary.BigEndian.Uint16(i.Payload[3:5]), nil
	default:
		return 0, &InvalidTypeError{Type: i.Type}
	}
}

// MustMMEGroupID returns MMEGroupID in uint16, ignoring errors.
// This should only be used if it is assured to have the value.
func (i *IE) MustMMEGroupID() uint16 {
	v, _ := i.MMEGroupID()
	return v
}

// MMECode returns MMECode in uint8 if the type of IE matches.
func (i *IE) MMECode() (uint8, error) {
	switch i.Type {
	case GUTI:
		if len(i.Payload) < 6 {
			return 0, io.ErrUnexpectedEOF
		}
		return i.Payload[5], nil
	default:
		return 0, &InvalidTypeError{Type: i.Type}
	}
}

// MustMMECode returns MMECode in uint8, ignoring errors.
// This should only be used if it is assured to have the value.
func (i *IE) MustMMECode() uint8 {
	v, _ := i.MMECode()
	return v
}

// MTMSI returns MTMSI in uint32 if the type of IE matches.
func (i *IE) MTMSI() (uint32, error) {
	switch i.Type {
	case GUTI:
		if len(i.Payload) < 10 {
			return 0, io.ErrUnexpectedEOF
		}
		return binary.BigEndian.Uint32(i.Payload[6:10]), nil
	default:
		return 0, &InvalidTypeError{Type: i.Type}
	}
}

// MustMTMSI returns MTMSI in uint32, ignoring errors.
// This should only be used if it is assured to have the value.
func (i *IE) MustMTMSI() uint32 {
	v, _ := i.MTMSI()
	return v
}

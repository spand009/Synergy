// Copyright 2019-2020 go-gtp authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

package ies

import (
	"io"

	"github.com/wmnsk/go-gtp/utils"
)

// NewIMSI creates a new IMSI IE.
func NewIMSI(imsi string) *IE {
	i, err := utils.StrToSwappedBytes(imsi, "f")
	if err != nil {
		return nil
	}

	return New(IMSI, 0x00, i)
}

// IMSI returns IMSI in string if the type of IE matches.
func (i *IE) IMSI() (string, error) {
	if i.Type != IMSI {
		return "", &InvalidTypeError{Type: i.Type}
	}
	if len(i.Payload) == 0 {
		return "", io.ErrUnexpectedEOF
	}

	return utils.SwappedBytesToStr(i.Payload, true), nil
}

// MustIMSI returns IMSI in string, ignoring errors.
// This should only be used if it is assured to have the value.
func (i *IE) MustIMSI() string {
	v, _ := i.IMSI()
	return v
}

// Copyright 2019-2020 go-gtp authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

package ies

import (
	"io"

	"github.com/wmnsk/go-gtp/utils"
)

// NewIMEISV creates a new IMEISV IE.
func NewIMEISV(imei string) *IE {
	i, err := utils.StrToSwappedBytes(imei, "f")
	if err != nil {
		return nil
	}
	return New(IMEISV, i)
}

// IMEISV returns IMEISV value if type matches.
func (i *IE) IMEISV() (string, error) {
	if i.Type != IMEISV {
		return "", &InvalidTypeError{Type: i.Type}
	}
	if len(i.Payload) == 0 {
		return "", io.ErrUnexpectedEOF
	}
	return utils.SwappedBytesToStr(i.Payload, true), nil
}

// MustIMEISV returns IMEISV in string if type matches.
// This should only be used if it is assured to have the value.
func (i *IE) MustIMEISV() string {
	v, _ := i.IMEISV()
	return v
}

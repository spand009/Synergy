// Copyright 2019-2020 go-gtp authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

package messages_test

import (
	"testing"

	"github.com/wmnsk/go-gtp/v1/ies"
	"github.com/wmnsk/go-gtp/v1/messages"
	"github.com/wmnsk/go-gtp/v1/testutils"
)

func TestErrorIndication(t *testing.T) {
	cases := []testutils.TestCase{
		{
			Description: "Normal",
			Structured: messages.NewErrorIndication(
				testutils.TestBearerInfo.TEID, testutils.TestBearerInfo.Seq,
				ies.NewTEIDDataI(0xdeadbeef),
				ies.NewGSNAddress("1.1.1.1"),
			),
			Serialized: []byte{
				// Header
				0x32, 0x1a, 0x00, 0x10, 0x11, 0x22, 0x33, 0x44,
				0x00, 0x01, 0x00, 0x00,
				// TEID-U
				0x10, 0xde, 0xad, 0xbe, 0xef,
				// GSN Address
				0x85, 0x00, 0x04, 0x01, 0x01, 0x01, 0x01,
			},
		},
	}

	testutils.Run(t, cases, func(b []byte) (testutils.Serializable, error) {
		v, err := messages.ParseErrorIndication(b)
		if err != nil {
			return nil, err
		}
		v.Payload = nil
		return v, nil
	})
}

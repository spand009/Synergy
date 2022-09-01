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

func TestUpdatePDPContextRequest(t *testing.T) {
	cases := []testutils.TestCase{
		{
			Description: "Normal",
			Structured: messages.NewUpdatePDPContextRequest(
				testutils.TestBearerInfo.TEID, testutils.TestBearerInfo.Seq,
				ies.NewIMSI("123450123456789"),
				ies.NewTEIDDataI(0xdeadbeef),
				ies.NewTEIDCPlane(0xdeadbeef),
				ies.NewNSAPI(5),
				ies.NewGSNAddress("1.1.1.1"),
				ies.NewGSNAddress("2.2.2.2"),
			),
			Serialized: []byte{
				// Header
				0x32, 0x12, 0x00, 0x27, 0x11, 0x22, 0x33, 0x44,
				0x00, 0x01, 0x00, 0x00,
				// IMSI
				0x02, 0x21, 0x43, 0x05, 0x21, 0x43, 0x65, 0x87, 0xf9,
				// TEID-U
				0x10, 0xde, 0xad, 0xbe, 0xef,
				// TEID-C
				0x11, 0xde, 0xad, 0xbe, 0xef,
				// NSAPI
				0x14, 0x05,
				// GSN Address
				0x85, 0x00, 0x04, 0x01, 0x01, 0x01, 0x01,
				// GSN Address
				0x85, 0x00, 0x04, 0x02, 0x02, 0x02, 0x02,
			},
		},
	}

	testutils.Run(t, cases, func(b []byte) (testutils.Serializable, error) {
		v, err := messages.ParseUpdatePDPContextRequest(b)
		if err != nil {
			return nil, err
		}
		v.Payload = nil
		return v, nil
	})
}

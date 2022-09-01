// Copyright 2019-2020 go-gtp authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

package messages_test

import (
	"testing"

	"github.com/wmnsk/go-gtp/v2/messages"
	"github.com/wmnsk/go-gtp/v2/testutils"

	v2 "github.com/wmnsk/go-gtp/v2"
	"github.com/wmnsk/go-gtp/v2/ies"
)

func TestCreateBearerResponse(t *testing.T) {
	cases := []testutils.TestCase{
		{
			Description: "Normal",
			Structured: messages.NewCreateBearerResponse(
				testutils.TestBearerInfo.TEID, testutils.TestBearerInfo.Seq,
				ies.NewCause(v2.CauseRequestAccepted, 0, 0, 0, nil),
				ies.NewBearerContext(
					ies.NewEPSBearerID(0),
					ies.NewBearerQoS(1, 2, 1, 0xff, 0x1111111111, 0x2222222222, 0x1111111111, 0x2222222222),
				),
			),
			Serialized: []byte{
				// Header
				0x48, 0x60, 0x00, 0x31, 0x11, 0x22, 0x33, 0x44, 0x00, 0x00, 0x01, 0x00,
				// Cause
				0x02, 0x00, 0x02, 0x00, 0x10, 0x00,
				// BearerContext
				0x5d, 0x00, 0x1f, 0x00,
				//   EBI
				0x49, 0x00, 0x01, 0x00, 0x00,
				//   BearerQoS
				0x50, 0x00, 0x16, 0x00, 0x49, 0xff,
				0x11, 0x11, 0x11, 0x11, 0x11, 0x22, 0x22, 0x22, 0x22, 0x22,
				0x11, 0x11, 0x11, 0x11, 0x11, 0x22, 0x22, 0x22, 0x22, 0x22,
			},
		},
	}

	testutils.Run(t, cases, func(b []byte) (testutils.Serializable, error) {
		v, err := messages.ParseCreateBearerResponse(b)
		if err != nil {
			return nil, err
		}
		v.Payload = nil
		return v, nil
	})
}

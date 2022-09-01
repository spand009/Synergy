// Copyright 2019-2020 go-gtp authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

package messages_test

import (
	"testing"

	v0 "github.com/wmnsk/go-gtp/v0"
	"github.com/wmnsk/go-gtp/v0/ies"
	"github.com/wmnsk/go-gtp/v0/messages"
	"github.com/wmnsk/go-gtp/v0/testutils"
)

func TestDeletePDPContextResponse(t *testing.T) {
	cases := []testutils.TestCase{
		{
			Description: "request-accepted",
			Structured: messages.NewDeletePDPContextResponse(
				testutils.TestFlow.Seq, testutils.TestFlow.Label, testutils.TestFlow.TID,
				ies.NewCause(v0.CauseRequestAccepted),
			),
			Serialized: []byte{
				// Hewader
				0x1e, 0x15, 0x00, 0x02,
				// SequenceNumber
				0x00, 0x01, 0x00, 0x00,
				// Sndpd
				0xff, 0xff, 0xff, 0xff,
				// TID
				0x21, 0x43, 0x65, 0x87, 0x09, 0x21, 0x43, 0x55,
				// Cause
				0x01, 0x80,
			},
		},
	}

	testutils.Run(t, cases, func(b []byte) (testutils.Serializable, error) {
		v, err := messages.ParseDeletePDPContextResponse(b)
		if err != nil {
			return nil, err
		}
		v.Payload = nil
		return v, nil
	})
}

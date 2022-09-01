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

func TestCreatePDPContextResponse(t *testing.T) {
	cases := []testutils.TestCase{
		{
			Description: "request-accepted",
			Structured: messages.NewCreatePDPContextResponse(
				testutils.TestFlow.Seq, testutils.TestFlow.Label, testutils.TestFlow.TID,
				ies.NewCause(v0.CauseRequestAccepted),
				ies.NewQualityOfServiceProfile(1, 1, 1, 1, 1),
				ies.NewReorderingRequired(false),
				ies.NewFlowLabelDataI(11),
				ies.NewFlowLabelSignalling(22),
				ies.NewChargingID(0xff),
				ies.NewEndUserAddress("1.1.1.1"),
				ies.NewGSNAddress("2.2.2.2"),
				ies.NewGSNAddress("3.3.3.3"),
			),
			Serialized: []byte{
				// Header
				0x1e, 0x11, 0x00, 0x2a,
				// SequenceNumber
				0x00, 0x01, 0x00, 0x00,
				// Sndpd
				0xff, 0xff, 0xff, 0xff,
				// TID
				0x21, 0x43, 0x65, 0x87, 0x09, 0x21, 0x43, 0x55,
				// Cause
				0x01, 0x80,
				// QualityOfServiceProfile
				0x06, 0x09, 0x11, 0x01,
				// ReorderingRequired
				0x08, 0xfe,
				// FlowLabelDataI
				0x10, 0x00, 0x0b,
				// FlowLabelSignalling
				0x11, 0x00, 0x16,
				// ChargingID
				0x7f, 0x00, 0x00, 0x00, 0xff,
				// EndUserAddress
				0x80, 0x00, 0x06, 0xf1, 0x21, 0x01, 0x01, 0x01, 0x01,
				// SGSNAddressForSignalling
				0x85, 0x00, 0x04, 0x02, 0x02, 0x02, 0x02,
				// SGSNAddressForUserData
				0x85, 0x00, 0x04, 0x03, 0x03, 0x03, 0x03,
			},
		}, {
			Description: "no-resources",
			Structured: messages.NewCreatePDPContextResponse(
				testutils.TestFlow.Seq, testutils.TestFlow.Label, testutils.TestFlow.TID,
				ies.NewCause(v0.CauseNoResourcesAvailable),
			),
			Serialized: []byte{
				// Header
				0x1e, 0x11, 0x00, 0x02,
				// SequenceNumber
				0x00, 0x01, 0x00, 0x00,
				// Sndpd
				0xff, 0xff, 0xff, 0xff,
				// TID
				0x21, 0x43, 0x65, 0x87, 0x09, 0x21, 0x43, 0x55,
				// Cause
				0x01, 0xc7,
			},
		},
	}

	testutils.Run(t, cases, func(b []byte) (testutils.Serializable, error) {
		v, err := messages.ParseCreatePDPContextResponse(b)
		if err != nil {
			return nil, err
		}
		v.Payload = nil
		return v, nil
	})
}

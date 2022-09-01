// Copyright 2019-2020 go-gtp authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

// Package testutils is an internal package to be used for unit tests. Don't use this.
package testutils

import (
	"testing"

	"github.com/pascaldekloe/goe/verify"
	"github.com/wmnsk/go-gtp/v0/messages"
)

// Serializable is just for testing v2.Messages. Don't use this.
type Serializable interface {
	Marshal() ([]byte, error)
	MarshalLen() int
}

// TestCase is just for testing v2.Messages. Don't use this.
type TestCase struct {
	Description string
	Structured  Serializable
	Serialized  []byte
}

// ParseFunc is just for testing v2.Messages. Don't use this.
type ParseFunc func([]byte) (Serializable, error)

// TestFlow is just for testing v2.Messages. Don't use this.
var TestFlow = struct {
	Seq, Label uint16
	TID        uint64
}{
	0x0001, 0x0000, 0x2143658709214355,
}

// Run is just for testing v2.Messages. Don't use this.
func Run(t *testing.T, cases []TestCase, Parse ParseFunc) {
	t.Helper()

	for _, c := range cases {
		t.Run(c.Description, func(t *testing.T) {
			t.Run("Parse", func(t *testing.T) {
				v, err := Parse(c.Serialized)
				if err != nil {
					t.Fatal(err)
				}

				if got, want := v, c.Structured; !verify.Values(t, "", got, want) {
					t.Fail()
				}
			})

			t.Run("Marshal", func(t *testing.T) {
				b, err := c.Structured.Marshal()
				if err != nil {
					t.Fatal(err)
				}

				if got, want := b, c.Serialized; !verify.Values(t, "", got, want) {
					t.Fail()
				}
			})

			t.Run("Len", func(t *testing.T) {
				if got, want := c.Structured.MarshalLen(), len(c.Serialized); got != want {
					t.Fatalf("got %v want %v", got, want)
				}
			})

			t.Run("Interface", func(t *testing.T) {
				// Ignore *Header and Generic in this tests.
				if _, ok := c.Structured.(*messages.Header); ok {
					return
				}

				if _, ok := c.Structured.(*messages.Generic); ok {
					return
				}

				Parsed, err := messages.Parse(c.Serialized)
				if err != nil {
					t.Fatal(err)
				}

				if got, want := Parsed.Version(), c.Structured.(messages.Message).Version(); got != want {
					t.Fatalf("got %v want %v", got, want)
				}
				if got, want := Parsed.MessageType(), c.Structured.(messages.Message).MessageType(); got != want {
					t.Fatalf("got %v want %v", got, want)
				}
				if got, want := Parsed.MessageTypeName(), c.Structured.(messages.Message).MessageTypeName(); got != want {
					t.Fatalf("got %v want %v", got, want)
				}
				if got, want := Parsed.TID(), c.Structured.(messages.Message).TID(); got != want {
					t.Fatalf("got %v want %v", got, want)
				}
			})
		})
	}
}

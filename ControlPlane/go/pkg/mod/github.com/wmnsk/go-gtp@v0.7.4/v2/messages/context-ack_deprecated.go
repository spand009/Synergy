// Copyright 2019-2020 go-gtp authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

package messages

import "log"

// Serialize serializes ContextAcknowledge into bytes.
//
// DEPRECATED: use ContextAcknowledge.Marshal instead.
func (c *ContextAcknowledge) Serialize() ([]byte, error) {
	log.Println("ContextAcknowledge.Serialize is deprecated. use ContextAcknowledge.Marshal instead")
	return c.Marshal()
}

// SerializeTo serializes ContextAcknowledge into bytes given as b.
//
// DEPRECATED: use ContextAcknowledge.MarshalTo instead.
func (c *ContextAcknowledge) SerializeTo(b []byte) error {
	log.Println("ContextAcknowledge.SerializeTo is deprecated. use ContextAcknowledge.MarshalTo instead")
	return c.MarshalTo(b)
}

// DecodeContextAcknowledge decodes bytes as ContextAcknowledge.
//
// DEPRECATED: use ParseContextAcknowledge instead.
func DecodeContextAcknowledge(b []byte) (*ContextAcknowledge, error) {
	log.Println("DecodeContextAcknowledge is deprecated. use ParseContextAcknowledge instead")
	return ParseContextAcknowledge(b)
}

// DecodeFromBytes decodes bytes as ContextAcknowledge.
//
// DEPRECATED: use ContextAcknowledge.UnmarshalBinary instead.
func (c *ContextAcknowledge) DecodeFromBytes(b []byte) error {
	log.Println("ContextAcknowledge.DecodeFromBytes is deprecated. use ContextAcknowledge.UnmarshalBinary instead")
	return c.UnmarshalBinary(b)
}

// Len returns the actual length of ContextAcknowledge.
//
// DEPRECATED: use ContextAcknowledge.MarshalLen instead.
func (c *ContextAcknowledge) Len() int {
	log.Println("ContextAcknowledge.Len is deprecated. use ContextAcknowledge.MarshalLen instead")
	return c.MarshalLen()
}

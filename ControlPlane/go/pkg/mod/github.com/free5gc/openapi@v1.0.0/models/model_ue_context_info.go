/*
 * Namf_MT
 *
 * AMF Mobile Termination Service
 *
 * API version: 1.0.0
 * Generated by: OpenAPI Generator (https://openapi-generator.tech)
 */

package models

import (
	"time"
)

type UeContextInfo struct {
	SupportVoPS       bool       `json:"supportVoPS,omitempty" bson:"supportVoPS"`
	SupportVoPSn3gpp  bool       `json:"supportVoPSn3gpp,omitempty" bson:"supportVoPSn3gpp"`
	LastActTime       *time.Time `json:"lastActTime,omitempty" bson:"lastActTime"`
	AccessType        AccessType `json:"accessType,omitempty" bson:"accessType"`
	RatType           RatType    `json:"ratType,omitempty" bson:"ratType"`
	SupportedFeatures string     `json:"supportedFeatures,omitempty" bson:"supportedFeatures"`
}

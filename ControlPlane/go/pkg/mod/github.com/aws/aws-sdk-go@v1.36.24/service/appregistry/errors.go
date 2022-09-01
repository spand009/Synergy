// Code generated by private/model/cli/gen-api/main.go. DO NOT EDIT.

package appregistry

import (
	"github.com/aws/aws-sdk-go/private/protocol"
)

const (

	// ErrCodeConflictException for service response error code
	// "ConflictException".
	//
	// There was a conflict when processing the request (for example, a resource
	// with the given name already exists within the account).
	ErrCodeConflictException = "ConflictException"

	// ErrCodeInternalServerException for service response error code
	// "InternalServerException".
	//
	// The service is experiencing internal problems.
	ErrCodeInternalServerException = "InternalServerException"

	// ErrCodeResourceNotFoundException for service response error code
	// "ResourceNotFoundException".
	//
	// The specified resource does not exist.
	ErrCodeResourceNotFoundException = "ResourceNotFoundException"

	// ErrCodeServiceQuotaExceededException for service response error code
	// "ServiceQuotaExceededException".
	//
	// The maximum number of resources per account has been reached.
	ErrCodeServiceQuotaExceededException = "ServiceQuotaExceededException"

	// ErrCodeValidationException for service response error code
	// "ValidationException".
	//
	// The request has invalid or missing parameters.
	ErrCodeValidationException = "ValidationException"
)

var exceptionFromCode = map[string]func(protocol.ResponseMetadata) error{
	"ConflictException":             newErrorConflictException,
	"InternalServerException":       newErrorInternalServerException,
	"ResourceNotFoundException":     newErrorResourceNotFoundException,
	"ServiceQuotaExceededException": newErrorServiceQuotaExceededException,
	"ValidationException":           newErrorValidationException,
}

package util

import (
	"net/http"

	"github.com/free5gc/openapi/models"
)

func ProblemDetailsSystemFailure(detail string) *models.ProblemDetails {
	return &models.ProblemDetails{
		Title:  "System failure",
		Status: http.StatusInternalServerError,
		Detail: detail,
		Cause:  "SYSTEM_FAILURE",
	}
}

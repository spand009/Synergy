package Namf_Communication

import (
	"context"
	"github.com/free5gc/openapi"
	"github.com/free5gc/openapi/models"
	"io/ioutil"
	"net/http"
	"net/url"
	"strings"
)

// Linger please
var (
	_ context.Context
)

type N2MessageNotifyCallbackDocumentApiService service

func (a *N2MessageNotifyCallbackDocumentApiService) N2InfoNotify(ctx context.Context, n2InfoNotifyUrl string, request models.N2InformationNotification) (models.N2InfoNotifyResponse, *http.Response, error) {
	var (
		localVarHttpMethod   = strings.ToUpper("Post")
		localVarPostBody     interface{}
		localVarFormFileName string
		localVarFileName     string
		localVarFileBytes    []byte
		localVarReturnValue  models.N2InfoNotifyResponse
	)

	// create path and map variables
	localVarPath := n2InfoNotifyUrl
	localVarHeaderParams := make(map[string]string)
	localVarQueryParams := url.Values{}
	localVarFormParams := url.Values{}

	localVarHttpContentTypes := []string{"application / json"}
	localVarHeaderParams["Content-Type"] = localVarHttpContentTypes[0] // use the first content type specified in 'consumes'

	// to determine the Accept header
	localVarHttpHeaderAccepts := []string{"application/problem+json"}

	// set Accept header
	localVarHttpHeaderAccept := openapi.SelectHeaderAccept(localVarHttpHeaderAccepts)
	if localVarHttpHeaderAccept != "" {
		localVarHeaderParams["Accept"] = localVarHttpHeaderAccept
	}

	r, err := openapi.PrepareRequest(ctx, a.client.cfg, localVarPath, localVarHttpMethod, localVarPostBody, localVarHeaderParams, localVarQueryParams, localVarFormParams, localVarFormFileName, localVarFileName, localVarFileBytes)
	if err != nil {
		return localVarReturnValue, nil, err
	}

	localVarHttpResponse, err := openapi.CallAPI(a.client.cfg, r)
	if err != nil || localVarHttpResponse == nil {
		return localVarReturnValue, localVarHttpResponse, err
	}

	localVarBody, err := ioutil.ReadAll(localVarHttpResponse.Body)
	localVarHttpResponse.Body.Close()
	if err != nil {
		return localVarReturnValue, localVarHttpResponse, err
	}

	apiError := openapi.GenericOpenAPIError{
		RawBody:     localVarBody,
		ErrorStatus: localVarHttpResponse.Status,
	}
	switch localVarHttpResponse.StatusCode {
	case 200:
		err = openapi.Deserialize(&localVarReturnValue, localVarBody, localVarHttpResponse.Header.Get("Content-Type"))
		if err != nil {
			apiError.ErrorStatus = err.Error()
		}
		return localVarReturnValue, localVarHttpResponse, nil
	case 204:
		return localVarReturnValue, localVarHttpResponse, err
	case 400:
		var v models.ProblemDetails
		err = openapi.Deserialize(&v, localVarBody, localVarHttpResponse.Header.Get("Content-Type"))
		if err != nil {
			apiError.ErrorStatus = err.Error()
			return localVarReturnValue, localVarHttpResponse, apiError
		}
		apiError.ErrorModel = v
		return localVarReturnValue, localVarHttpResponse, apiError
	case 411:
		var v models.ProblemDetails
		err = openapi.Deserialize(&v, localVarBody, localVarHttpResponse.Header.Get("Content-Type"))
		if err != nil {
			apiError.ErrorStatus = err.Error()
			return localVarReturnValue, localVarHttpResponse, apiError
		}
		apiError.ErrorModel = v
		return localVarReturnValue, localVarHttpResponse, apiError
	case 413:
		var v models.ProblemDetails
		err = openapi.Deserialize(&v, localVarBody, localVarHttpResponse.Header.Get("Content-Type"))
		if err != nil {
			apiError.ErrorStatus = err.Error()
			return localVarReturnValue, localVarHttpResponse, apiError
		}
		apiError.ErrorModel = v
		return localVarReturnValue, localVarHttpResponse, apiError
	case 415:
		var v models.ProblemDetails
		err = openapi.Deserialize(&v, localVarBody, localVarHttpResponse.Header.Get("Content-Type"))
		if err != nil {
			apiError.ErrorStatus = err.Error()
			return localVarReturnValue, localVarHttpResponse, apiError
		}
		apiError.ErrorModel = v
		return localVarReturnValue, localVarHttpResponse, apiError
	case 429:
		var v models.ProblemDetails
		err = openapi.Deserialize(&v, localVarBody, localVarHttpResponse.Header.Get("Content-Type"))
		if err != nil {
			apiError.ErrorStatus = err.Error()
			return localVarReturnValue, localVarHttpResponse, apiError
		}
		apiError.ErrorModel = v
		return localVarReturnValue, localVarHttpResponse, apiError
	case 500:
		var v models.ProblemDetails
		err = openapi.Deserialize(&v, localVarBody, localVarHttpResponse.Header.Get("Content-Type"))
		if err != nil {
			apiError.ErrorStatus = err.Error()
			return localVarReturnValue, localVarHttpResponse, apiError
		}
		apiError.ErrorModel = v
		return localVarReturnValue, localVarHttpResponse, apiError
	case 503:
		var v models.ProblemDetails
		err = openapi.Deserialize(&v, localVarBody, localVarHttpResponse.Header.Get("Content-Type"))
		if err != nil {
			apiError.ErrorStatus = err.Error()
			return localVarReturnValue, localVarHttpResponse, apiError
		}
		apiError.ErrorModel = v
		return localVarReturnValue, localVarHttpResponse, apiError
	default:
		return localVarReturnValue, localVarHttpResponse, openapi.ReportError("%d is not a valid status code in N1N2MessageSubscribe", localVarHttpResponse.StatusCode)
	}
}

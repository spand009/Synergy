// Code generated by private/model/cli/gen-api/main.go. DO NOT EDIT.

// Package elasticsearchserviceiface provides an interface to enable mocking the Amazon Elasticsearch Service service client
// for testing your code.
//
// It is important to note that this interface will have breaking changes
// when the service model is updated and adds new API operations, paginators,
// and waiters.
package elasticsearchserviceiface

import (
	"github.com/aws/aws-sdk-go/aws"
	"github.com/aws/aws-sdk-go/aws/request"
	"github.com/aws/aws-sdk-go/service/elasticsearchservice"
)

// ElasticsearchServiceAPI provides an interface to enable mocking the
// elasticsearchservice.ElasticsearchService service client's API operation,
// paginators, and waiters. This make unit testing your code that calls out
// to the SDK's service client's calls easier.
//
// The best way to use this interface is so the SDK's service client's calls
// can be stubbed out for unit testing your code with the SDK without needing
// to inject custom request handlers into the SDK's request pipeline.
//
//    // myFunc uses an SDK service client to make a request to
//    // Amazon Elasticsearch Service.
//    func myFunc(svc elasticsearchserviceiface.ElasticsearchServiceAPI) bool {
//        // Make svc.AcceptInboundCrossClusterSearchConnection request
//    }
//
//    func main() {
//        sess := session.New()
//        svc := elasticsearchservice.New(sess)
//
//        myFunc(svc)
//    }
//
// In your _test.go file:
//
//    // Define a mock struct to be used in your unit tests of myFunc.
//    type mockElasticsearchServiceClient struct {
//        elasticsearchserviceiface.ElasticsearchServiceAPI
//    }
//    func (m *mockElasticsearchServiceClient) AcceptInboundCrossClusterSearchConnection(input *elasticsearchservice.AcceptInboundCrossClusterSearchConnectionInput) (*elasticsearchservice.AcceptInboundCrossClusterSearchConnectionOutput, error) {
//        // mock response/functionality
//    }
//
//    func TestMyFunc(t *testing.T) {
//        // Setup Test
//        mockSvc := &mockElasticsearchServiceClient{}
//
//        myfunc(mockSvc)
//
//        // Verify myFunc's functionality
//    }
//
// It is important to note that this interface will have breaking changes
// when the service model is updated and adds new API operations, paginators,
// and waiters. Its suggested to use the pattern above for testing, or using
// tooling to generate mocks to satisfy the interfaces.
type ElasticsearchServiceAPI interface {
	AcceptInboundCrossClusterSearchConnection(*elasticsearchservice.AcceptInboundCrossClusterSearchConnectionInput) (*elasticsearchservice.AcceptInboundCrossClusterSearchConnectionOutput, error)
	AcceptInboundCrossClusterSearchConnectionWithContext(aws.Context, *elasticsearchservice.AcceptInboundCrossClusterSearchConnectionInput, ...request.Option) (*elasticsearchservice.AcceptInboundCrossClusterSearchConnectionOutput, error)
	AcceptInboundCrossClusterSearchConnectionRequest(*elasticsearchservice.AcceptInboundCrossClusterSearchConnectionInput) (*request.Request, *elasticsearchservice.AcceptInboundCrossClusterSearchConnectionOutput)

	AddTags(*elasticsearchservice.AddTagsInput) (*elasticsearchservice.AddTagsOutput, error)
	AddTagsWithContext(aws.Context, *elasticsearchservice.AddTagsInput, ...request.Option) (*elasticsearchservice.AddTagsOutput, error)
	AddTagsRequest(*elasticsearchservice.AddTagsInput) (*request.Request, *elasticsearchservice.AddTagsOutput)

	AssociatePackage(*elasticsearchservice.AssociatePackageInput) (*elasticsearchservice.AssociatePackageOutput, error)
	AssociatePackageWithContext(aws.Context, *elasticsearchservice.AssociatePackageInput, ...request.Option) (*elasticsearchservice.AssociatePackageOutput, error)
	AssociatePackageRequest(*elasticsearchservice.AssociatePackageInput) (*request.Request, *elasticsearchservice.AssociatePackageOutput)

	CancelElasticsearchServiceSoftwareUpdate(*elasticsearchservice.CancelElasticsearchServiceSoftwareUpdateInput) (*elasticsearchservice.CancelElasticsearchServiceSoftwareUpdateOutput, error)
	CancelElasticsearchServiceSoftwareUpdateWithContext(aws.Context, *elasticsearchservice.CancelElasticsearchServiceSoftwareUpdateInput, ...request.Option) (*elasticsearchservice.CancelElasticsearchServiceSoftwareUpdateOutput, error)
	CancelElasticsearchServiceSoftwareUpdateRequest(*elasticsearchservice.CancelElasticsearchServiceSoftwareUpdateInput) (*request.Request, *elasticsearchservice.CancelElasticsearchServiceSoftwareUpdateOutput)

	CreateElasticsearchDomain(*elasticsearchservice.CreateElasticsearchDomainInput) (*elasticsearchservice.CreateElasticsearchDomainOutput, error)
	CreateElasticsearchDomainWithContext(aws.Context, *elasticsearchservice.CreateElasticsearchDomainInput, ...request.Option) (*elasticsearchservice.CreateElasticsearchDomainOutput, error)
	CreateElasticsearchDomainRequest(*elasticsearchservice.CreateElasticsearchDomainInput) (*request.Request, *elasticsearchservice.CreateElasticsearchDomainOutput)

	CreateOutboundCrossClusterSearchConnection(*elasticsearchservice.CreateOutboundCrossClusterSearchConnectionInput) (*elasticsearchservice.CreateOutboundCrossClusterSearchConnectionOutput, error)
	CreateOutboundCrossClusterSearchConnectionWithContext(aws.Context, *elasticsearchservice.CreateOutboundCrossClusterSearchConnectionInput, ...request.Option) (*elasticsearchservice.CreateOutboundCrossClusterSearchConnectionOutput, error)
	CreateOutboundCrossClusterSearchConnectionRequest(*elasticsearchservice.CreateOutboundCrossClusterSearchConnectionInput) (*request.Request, *elasticsearchservice.CreateOutboundCrossClusterSearchConnectionOutput)

	CreatePackage(*elasticsearchservice.CreatePackageInput) (*elasticsearchservice.CreatePackageOutput, error)
	CreatePackageWithContext(aws.Context, *elasticsearchservice.CreatePackageInput, ...request.Option) (*elasticsearchservice.CreatePackageOutput, error)
	CreatePackageRequest(*elasticsearchservice.CreatePackageInput) (*request.Request, *elasticsearchservice.CreatePackageOutput)

	DeleteElasticsearchDomain(*elasticsearchservice.DeleteElasticsearchDomainInput) (*elasticsearchservice.DeleteElasticsearchDomainOutput, error)
	DeleteElasticsearchDomainWithContext(aws.Context, *elasticsearchservice.DeleteElasticsearchDomainInput, ...request.Option) (*elasticsearchservice.DeleteElasticsearchDomainOutput, error)
	DeleteElasticsearchDomainRequest(*elasticsearchservice.DeleteElasticsearchDomainInput) (*request.Request, *elasticsearchservice.DeleteElasticsearchDomainOutput)

	DeleteElasticsearchServiceRole(*elasticsearchservice.DeleteElasticsearchServiceRoleInput) (*elasticsearchservice.DeleteElasticsearchServiceRoleOutput, error)
	DeleteElasticsearchServiceRoleWithContext(aws.Context, *elasticsearchservice.DeleteElasticsearchServiceRoleInput, ...request.Option) (*elasticsearchservice.DeleteElasticsearchServiceRoleOutput, error)
	DeleteElasticsearchServiceRoleRequest(*elasticsearchservice.DeleteElasticsearchServiceRoleInput) (*request.Request, *elasticsearchservice.DeleteElasticsearchServiceRoleOutput)

	DeleteInboundCrossClusterSearchConnection(*elasticsearchservice.DeleteInboundCrossClusterSearchConnectionInput) (*elasticsearchservice.DeleteInboundCrossClusterSearchConnectionOutput, error)
	DeleteInboundCrossClusterSearchConnectionWithContext(aws.Context, *elasticsearchservice.DeleteInboundCrossClusterSearchConnectionInput, ...request.Option) (*elasticsearchservice.DeleteInboundCrossClusterSearchConnectionOutput, error)
	DeleteInboundCrossClusterSearchConnectionRequest(*elasticsearchservice.DeleteInboundCrossClusterSearchConnectionInput) (*request.Request, *elasticsearchservice.DeleteInboundCrossClusterSearchConnectionOutput)

	DeleteOutboundCrossClusterSearchConnection(*elasticsearchservice.DeleteOutboundCrossClusterSearchConnectionInput) (*elasticsearchservice.DeleteOutboundCrossClusterSearchConnectionOutput, error)
	DeleteOutboundCrossClusterSearchConnectionWithContext(aws.Context, *elasticsearchservice.DeleteOutboundCrossClusterSearchConnectionInput, ...request.Option) (*elasticsearchservice.DeleteOutboundCrossClusterSearchConnectionOutput, error)
	DeleteOutboundCrossClusterSearchConnectionRequest(*elasticsearchservice.DeleteOutboundCrossClusterSearchConnectionInput) (*request.Request, *elasticsearchservice.DeleteOutboundCrossClusterSearchConnectionOutput)

	DeletePackage(*elasticsearchservice.DeletePackageInput) (*elasticsearchservice.DeletePackageOutput, error)
	DeletePackageWithContext(aws.Context, *elasticsearchservice.DeletePackageInput, ...request.Option) (*elasticsearchservice.DeletePackageOutput, error)
	DeletePackageRequest(*elasticsearchservice.DeletePackageInput) (*request.Request, *elasticsearchservice.DeletePackageOutput)

	DescribeElasticsearchDomain(*elasticsearchservice.DescribeElasticsearchDomainInput) (*elasticsearchservice.DescribeElasticsearchDomainOutput, error)
	DescribeElasticsearchDomainWithContext(aws.Context, *elasticsearchservice.DescribeElasticsearchDomainInput, ...request.Option) (*elasticsearchservice.DescribeElasticsearchDomainOutput, error)
	DescribeElasticsearchDomainRequest(*elasticsearchservice.DescribeElasticsearchDomainInput) (*request.Request, *elasticsearchservice.DescribeElasticsearchDomainOutput)

	DescribeElasticsearchDomainConfig(*elasticsearchservice.DescribeElasticsearchDomainConfigInput) (*elasticsearchservice.DescribeElasticsearchDomainConfigOutput, error)
	DescribeElasticsearchDomainConfigWithContext(aws.Context, *elasticsearchservice.DescribeElasticsearchDomainConfigInput, ...request.Option) (*elasticsearchservice.DescribeElasticsearchDomainConfigOutput, error)
	DescribeElasticsearchDomainConfigRequest(*elasticsearchservice.DescribeElasticsearchDomainConfigInput) (*request.Request, *elasticsearchservice.DescribeElasticsearchDomainConfigOutput)

	DescribeElasticsearchDomains(*elasticsearchservice.DescribeElasticsearchDomainsInput) (*elasticsearchservice.DescribeElasticsearchDomainsOutput, error)
	DescribeElasticsearchDomainsWithContext(aws.Context, *elasticsearchservice.DescribeElasticsearchDomainsInput, ...request.Option) (*elasticsearchservice.DescribeElasticsearchDomainsOutput, error)
	DescribeElasticsearchDomainsRequest(*elasticsearchservice.DescribeElasticsearchDomainsInput) (*request.Request, *elasticsearchservice.DescribeElasticsearchDomainsOutput)

	DescribeElasticsearchInstanceTypeLimits(*elasticsearchservice.DescribeElasticsearchInstanceTypeLimitsInput) (*elasticsearchservice.DescribeElasticsearchInstanceTypeLimitsOutput, error)
	DescribeElasticsearchInstanceTypeLimitsWithContext(aws.Context, *elasticsearchservice.DescribeElasticsearchInstanceTypeLimitsInput, ...request.Option) (*elasticsearchservice.DescribeElasticsearchInstanceTypeLimitsOutput, error)
	DescribeElasticsearchInstanceTypeLimitsRequest(*elasticsearchservice.DescribeElasticsearchInstanceTypeLimitsInput) (*request.Request, *elasticsearchservice.DescribeElasticsearchInstanceTypeLimitsOutput)

	DescribeInboundCrossClusterSearchConnections(*elasticsearchservice.DescribeInboundCrossClusterSearchConnectionsInput) (*elasticsearchservice.DescribeInboundCrossClusterSearchConnectionsOutput, error)
	DescribeInboundCrossClusterSearchConnectionsWithContext(aws.Context, *elasticsearchservice.DescribeInboundCrossClusterSearchConnectionsInput, ...request.Option) (*elasticsearchservice.DescribeInboundCrossClusterSearchConnectionsOutput, error)
	DescribeInboundCrossClusterSearchConnectionsRequest(*elasticsearchservice.DescribeInboundCrossClusterSearchConnectionsInput) (*request.Request, *elasticsearchservice.DescribeInboundCrossClusterSearchConnectionsOutput)

	DescribeInboundCrossClusterSearchConnectionsPages(*elasticsearchservice.DescribeInboundCrossClusterSearchConnectionsInput, func(*elasticsearchservice.DescribeInboundCrossClusterSearchConnectionsOutput, bool) bool) error
	DescribeInboundCrossClusterSearchConnectionsPagesWithContext(aws.Context, *elasticsearchservice.DescribeInboundCrossClusterSearchConnectionsInput, func(*elasticsearchservice.DescribeInboundCrossClusterSearchConnectionsOutput, bool) bool, ...request.Option) error

	DescribeOutboundCrossClusterSearchConnections(*elasticsearchservice.DescribeOutboundCrossClusterSearchConnectionsInput) (*elasticsearchservice.DescribeOutboundCrossClusterSearchConnectionsOutput, error)
	DescribeOutboundCrossClusterSearchConnectionsWithContext(aws.Context, *elasticsearchservice.DescribeOutboundCrossClusterSearchConnectionsInput, ...request.Option) (*elasticsearchservice.DescribeOutboundCrossClusterSearchConnectionsOutput, error)
	DescribeOutboundCrossClusterSearchConnectionsRequest(*elasticsearchservice.DescribeOutboundCrossClusterSearchConnectionsInput) (*request.Request, *elasticsearchservice.DescribeOutboundCrossClusterSearchConnectionsOutput)

	DescribeOutboundCrossClusterSearchConnectionsPages(*elasticsearchservice.DescribeOutboundCrossClusterSearchConnectionsInput, func(*elasticsearchservice.DescribeOutboundCrossClusterSearchConnectionsOutput, bool) bool) error
	DescribeOutboundCrossClusterSearchConnectionsPagesWithContext(aws.Context, *elasticsearchservice.DescribeOutboundCrossClusterSearchConnectionsInput, func(*elasticsearchservice.DescribeOutboundCrossClusterSearchConnectionsOutput, bool) bool, ...request.Option) error

	DescribePackages(*elasticsearchservice.DescribePackagesInput) (*elasticsearchservice.DescribePackagesOutput, error)
	DescribePackagesWithContext(aws.Context, *elasticsearchservice.DescribePackagesInput, ...request.Option) (*elasticsearchservice.DescribePackagesOutput, error)
	DescribePackagesRequest(*elasticsearchservice.DescribePackagesInput) (*request.Request, *elasticsearchservice.DescribePackagesOutput)

	DescribePackagesPages(*elasticsearchservice.DescribePackagesInput, func(*elasticsearchservice.DescribePackagesOutput, bool) bool) error
	DescribePackagesPagesWithContext(aws.Context, *elasticsearchservice.DescribePackagesInput, func(*elasticsearchservice.DescribePackagesOutput, bool) bool, ...request.Option) error

	DescribeReservedElasticsearchInstanceOfferings(*elasticsearchservice.DescribeReservedElasticsearchInstanceOfferingsInput) (*elasticsearchservice.DescribeReservedElasticsearchInstanceOfferingsOutput, error)
	DescribeReservedElasticsearchInstanceOfferingsWithContext(aws.Context, *elasticsearchservice.DescribeReservedElasticsearchInstanceOfferingsInput, ...request.Option) (*elasticsearchservice.DescribeReservedElasticsearchInstanceOfferingsOutput, error)
	DescribeReservedElasticsearchInstanceOfferingsRequest(*elasticsearchservice.DescribeReservedElasticsearchInstanceOfferingsInput) (*request.Request, *elasticsearchservice.DescribeReservedElasticsearchInstanceOfferingsOutput)

	DescribeReservedElasticsearchInstanceOfferingsPages(*elasticsearchservice.DescribeReservedElasticsearchInstanceOfferingsInput, func(*elasticsearchservice.DescribeReservedElasticsearchInstanceOfferingsOutput, bool) bool) error
	DescribeReservedElasticsearchInstanceOfferingsPagesWithContext(aws.Context, *elasticsearchservice.DescribeReservedElasticsearchInstanceOfferingsInput, func(*elasticsearchservice.DescribeReservedElasticsearchInstanceOfferingsOutput, bool) bool, ...request.Option) error

	DescribeReservedElasticsearchInstances(*elasticsearchservice.DescribeReservedElasticsearchInstancesInput) (*elasticsearchservice.DescribeReservedElasticsearchInstancesOutput, error)
	DescribeReservedElasticsearchInstancesWithContext(aws.Context, *elasticsearchservice.DescribeReservedElasticsearchInstancesInput, ...request.Option) (*elasticsearchservice.DescribeReservedElasticsearchInstancesOutput, error)
	DescribeReservedElasticsearchInstancesRequest(*elasticsearchservice.DescribeReservedElasticsearchInstancesInput) (*request.Request, *elasticsearchservice.DescribeReservedElasticsearchInstancesOutput)

	DescribeReservedElasticsearchInstancesPages(*elasticsearchservice.DescribeReservedElasticsearchInstancesInput, func(*elasticsearchservice.DescribeReservedElasticsearchInstancesOutput, bool) bool) error
	DescribeReservedElasticsearchInstancesPagesWithContext(aws.Context, *elasticsearchservice.DescribeReservedElasticsearchInstancesInput, func(*elasticsearchservice.DescribeReservedElasticsearchInstancesOutput, bool) bool, ...request.Option) error

	DissociatePackage(*elasticsearchservice.DissociatePackageInput) (*elasticsearchservice.DissociatePackageOutput, error)
	DissociatePackageWithContext(aws.Context, *elasticsearchservice.DissociatePackageInput, ...request.Option) (*elasticsearchservice.DissociatePackageOutput, error)
	DissociatePackageRequest(*elasticsearchservice.DissociatePackageInput) (*request.Request, *elasticsearchservice.DissociatePackageOutput)

	GetCompatibleElasticsearchVersions(*elasticsearchservice.GetCompatibleElasticsearchVersionsInput) (*elasticsearchservice.GetCompatibleElasticsearchVersionsOutput, error)
	GetCompatibleElasticsearchVersionsWithContext(aws.Context, *elasticsearchservice.GetCompatibleElasticsearchVersionsInput, ...request.Option) (*elasticsearchservice.GetCompatibleElasticsearchVersionsOutput, error)
	GetCompatibleElasticsearchVersionsRequest(*elasticsearchservice.GetCompatibleElasticsearchVersionsInput) (*request.Request, *elasticsearchservice.GetCompatibleElasticsearchVersionsOutput)

	GetPackageVersionHistory(*elasticsearchservice.GetPackageVersionHistoryInput) (*elasticsearchservice.GetPackageVersionHistoryOutput, error)
	GetPackageVersionHistoryWithContext(aws.Context, *elasticsearchservice.GetPackageVersionHistoryInput, ...request.Option) (*elasticsearchservice.GetPackageVersionHistoryOutput, error)
	GetPackageVersionHistoryRequest(*elasticsearchservice.GetPackageVersionHistoryInput) (*request.Request, *elasticsearchservice.GetPackageVersionHistoryOutput)

	GetPackageVersionHistoryPages(*elasticsearchservice.GetPackageVersionHistoryInput, func(*elasticsearchservice.GetPackageVersionHistoryOutput, bool) bool) error
	GetPackageVersionHistoryPagesWithContext(aws.Context, *elasticsearchservice.GetPackageVersionHistoryInput, func(*elasticsearchservice.GetPackageVersionHistoryOutput, bool) bool, ...request.Option) error

	GetUpgradeHistory(*elasticsearchservice.GetUpgradeHistoryInput) (*elasticsearchservice.GetUpgradeHistoryOutput, error)
	GetUpgradeHistoryWithContext(aws.Context, *elasticsearchservice.GetUpgradeHistoryInput, ...request.Option) (*elasticsearchservice.GetUpgradeHistoryOutput, error)
	GetUpgradeHistoryRequest(*elasticsearchservice.GetUpgradeHistoryInput) (*request.Request, *elasticsearchservice.GetUpgradeHistoryOutput)

	GetUpgradeHistoryPages(*elasticsearchservice.GetUpgradeHistoryInput, func(*elasticsearchservice.GetUpgradeHistoryOutput, bool) bool) error
	GetUpgradeHistoryPagesWithContext(aws.Context, *elasticsearchservice.GetUpgradeHistoryInput, func(*elasticsearchservice.GetUpgradeHistoryOutput, bool) bool, ...request.Option) error

	GetUpgradeStatus(*elasticsearchservice.GetUpgradeStatusInput) (*elasticsearchservice.GetUpgradeStatusOutput, error)
	GetUpgradeStatusWithContext(aws.Context, *elasticsearchservice.GetUpgradeStatusInput, ...request.Option) (*elasticsearchservice.GetUpgradeStatusOutput, error)
	GetUpgradeStatusRequest(*elasticsearchservice.GetUpgradeStatusInput) (*request.Request, *elasticsearchservice.GetUpgradeStatusOutput)

	ListDomainNames(*elasticsearchservice.ListDomainNamesInput) (*elasticsearchservice.ListDomainNamesOutput, error)
	ListDomainNamesWithContext(aws.Context, *elasticsearchservice.ListDomainNamesInput, ...request.Option) (*elasticsearchservice.ListDomainNamesOutput, error)
	ListDomainNamesRequest(*elasticsearchservice.ListDomainNamesInput) (*request.Request, *elasticsearchservice.ListDomainNamesOutput)

	ListDomainsForPackage(*elasticsearchservice.ListDomainsForPackageInput) (*elasticsearchservice.ListDomainsForPackageOutput, error)
	ListDomainsForPackageWithContext(aws.Context, *elasticsearchservice.ListDomainsForPackageInput, ...request.Option) (*elasticsearchservice.ListDomainsForPackageOutput, error)
	ListDomainsForPackageRequest(*elasticsearchservice.ListDomainsForPackageInput) (*request.Request, *elasticsearchservice.ListDomainsForPackageOutput)

	ListDomainsForPackagePages(*elasticsearchservice.ListDomainsForPackageInput, func(*elasticsearchservice.ListDomainsForPackageOutput, bool) bool) error
	ListDomainsForPackagePagesWithContext(aws.Context, *elasticsearchservice.ListDomainsForPackageInput, func(*elasticsearchservice.ListDomainsForPackageOutput, bool) bool, ...request.Option) error

	ListElasticsearchInstanceTypes(*elasticsearchservice.ListElasticsearchInstanceTypesInput) (*elasticsearchservice.ListElasticsearchInstanceTypesOutput, error)
	ListElasticsearchInstanceTypesWithContext(aws.Context, *elasticsearchservice.ListElasticsearchInstanceTypesInput, ...request.Option) (*elasticsearchservice.ListElasticsearchInstanceTypesOutput, error)
	ListElasticsearchInstanceTypesRequest(*elasticsearchservice.ListElasticsearchInstanceTypesInput) (*request.Request, *elasticsearchservice.ListElasticsearchInstanceTypesOutput)

	ListElasticsearchInstanceTypesPages(*elasticsearchservice.ListElasticsearchInstanceTypesInput, func(*elasticsearchservice.ListElasticsearchInstanceTypesOutput, bool) bool) error
	ListElasticsearchInstanceTypesPagesWithContext(aws.Context, *elasticsearchservice.ListElasticsearchInstanceTypesInput, func(*elasticsearchservice.ListElasticsearchInstanceTypesOutput, bool) bool, ...request.Option) error

	ListElasticsearchVersions(*elasticsearchservice.ListElasticsearchVersionsInput) (*elasticsearchservice.ListElasticsearchVersionsOutput, error)
	ListElasticsearchVersionsWithContext(aws.Context, *elasticsearchservice.ListElasticsearchVersionsInput, ...request.Option) (*elasticsearchservice.ListElasticsearchVersionsOutput, error)
	ListElasticsearchVersionsRequest(*elasticsearchservice.ListElasticsearchVersionsInput) (*request.Request, *elasticsearchservice.ListElasticsearchVersionsOutput)

	ListElasticsearchVersionsPages(*elasticsearchservice.ListElasticsearchVersionsInput, func(*elasticsearchservice.ListElasticsearchVersionsOutput, bool) bool) error
	ListElasticsearchVersionsPagesWithContext(aws.Context, *elasticsearchservice.ListElasticsearchVersionsInput, func(*elasticsearchservice.ListElasticsearchVersionsOutput, bool) bool, ...request.Option) error

	ListPackagesForDomain(*elasticsearchservice.ListPackagesForDomainInput) (*elasticsearchservice.ListPackagesForDomainOutput, error)
	ListPackagesForDomainWithContext(aws.Context, *elasticsearchservice.ListPackagesForDomainInput, ...request.Option) (*elasticsearchservice.ListPackagesForDomainOutput, error)
	ListPackagesForDomainRequest(*elasticsearchservice.ListPackagesForDomainInput) (*request.Request, *elasticsearchservice.ListPackagesForDomainOutput)

	ListPackagesForDomainPages(*elasticsearchservice.ListPackagesForDomainInput, func(*elasticsearchservice.ListPackagesForDomainOutput, bool) bool) error
	ListPackagesForDomainPagesWithContext(aws.Context, *elasticsearchservice.ListPackagesForDomainInput, func(*elasticsearchservice.ListPackagesForDomainOutput, bool) bool, ...request.Option) error

	ListTags(*elasticsearchservice.ListTagsInput) (*elasticsearchservice.ListTagsOutput, error)
	ListTagsWithContext(aws.Context, *elasticsearchservice.ListTagsInput, ...request.Option) (*elasticsearchservice.ListTagsOutput, error)
	ListTagsRequest(*elasticsearchservice.ListTagsInput) (*request.Request, *elasticsearchservice.ListTagsOutput)

	PurchaseReservedElasticsearchInstanceOffering(*elasticsearchservice.PurchaseReservedElasticsearchInstanceOfferingInput) (*elasticsearchservice.PurchaseReservedElasticsearchInstanceOfferingOutput, error)
	PurchaseReservedElasticsearchInstanceOfferingWithContext(aws.Context, *elasticsearchservice.PurchaseReservedElasticsearchInstanceOfferingInput, ...request.Option) (*elasticsearchservice.PurchaseReservedElasticsearchInstanceOfferingOutput, error)
	PurchaseReservedElasticsearchInstanceOfferingRequest(*elasticsearchservice.PurchaseReservedElasticsearchInstanceOfferingInput) (*request.Request, *elasticsearchservice.PurchaseReservedElasticsearchInstanceOfferingOutput)

	RejectInboundCrossClusterSearchConnection(*elasticsearchservice.RejectInboundCrossClusterSearchConnectionInput) (*elasticsearchservice.RejectInboundCrossClusterSearchConnectionOutput, error)
	RejectInboundCrossClusterSearchConnectionWithContext(aws.Context, *elasticsearchservice.RejectInboundCrossClusterSearchConnectionInput, ...request.Option) (*elasticsearchservice.RejectInboundCrossClusterSearchConnectionOutput, error)
	RejectInboundCrossClusterSearchConnectionRequest(*elasticsearchservice.RejectInboundCrossClusterSearchConnectionInput) (*request.Request, *elasticsearchservice.RejectInboundCrossClusterSearchConnectionOutput)

	RemoveTags(*elasticsearchservice.RemoveTagsInput) (*elasticsearchservice.RemoveTagsOutput, error)
	RemoveTagsWithContext(aws.Context, *elasticsearchservice.RemoveTagsInput, ...request.Option) (*elasticsearchservice.RemoveTagsOutput, error)
	RemoveTagsRequest(*elasticsearchservice.RemoveTagsInput) (*request.Request, *elasticsearchservice.RemoveTagsOutput)

	StartElasticsearchServiceSoftwareUpdate(*elasticsearchservice.StartElasticsearchServiceSoftwareUpdateInput) (*elasticsearchservice.StartElasticsearchServiceSoftwareUpdateOutput, error)
	StartElasticsearchServiceSoftwareUpdateWithContext(aws.Context, *elasticsearchservice.StartElasticsearchServiceSoftwareUpdateInput, ...request.Option) (*elasticsearchservice.StartElasticsearchServiceSoftwareUpdateOutput, error)
	StartElasticsearchServiceSoftwareUpdateRequest(*elasticsearchservice.StartElasticsearchServiceSoftwareUpdateInput) (*request.Request, *elasticsearchservice.StartElasticsearchServiceSoftwareUpdateOutput)

	UpdateElasticsearchDomainConfig(*elasticsearchservice.UpdateElasticsearchDomainConfigInput) (*elasticsearchservice.UpdateElasticsearchDomainConfigOutput, error)
	UpdateElasticsearchDomainConfigWithContext(aws.Context, *elasticsearchservice.UpdateElasticsearchDomainConfigInput, ...request.Option) (*elasticsearchservice.UpdateElasticsearchDomainConfigOutput, error)
	UpdateElasticsearchDomainConfigRequest(*elasticsearchservice.UpdateElasticsearchDomainConfigInput) (*request.Request, *elasticsearchservice.UpdateElasticsearchDomainConfigOutput)

	UpdatePackage(*elasticsearchservice.UpdatePackageInput) (*elasticsearchservice.UpdatePackageOutput, error)
	UpdatePackageWithContext(aws.Context, *elasticsearchservice.UpdatePackageInput, ...request.Option) (*elasticsearchservice.UpdatePackageOutput, error)
	UpdatePackageRequest(*elasticsearchservice.UpdatePackageInput) (*request.Request, *elasticsearchservice.UpdatePackageOutput)

	UpgradeElasticsearchDomain(*elasticsearchservice.UpgradeElasticsearchDomainInput) (*elasticsearchservice.UpgradeElasticsearchDomainOutput, error)
	UpgradeElasticsearchDomainWithContext(aws.Context, *elasticsearchservice.UpgradeElasticsearchDomainInput, ...request.Option) (*elasticsearchservice.UpgradeElasticsearchDomainOutput, error)
	UpgradeElasticsearchDomainRequest(*elasticsearchservice.UpgradeElasticsearchDomainInput) (*request.Request, *elasticsearchservice.UpgradeElasticsearchDomainOutput)
}

var _ ElasticsearchServiceAPI = (*elasticsearchservice.ElasticsearchService)(nil)

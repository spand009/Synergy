// Copyright 2020 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Code generated by protoc-gen-go. DO NOT EDIT.
// versions:
// 	protoc-gen-go v1.25.0
// 	protoc        v3.12.3
// source: google/ads/googleads/v2/services/ad_group_service.proto

package services

import (
	context "context"
	reflect "reflect"
	sync "sync"

	proto "github.com/golang/protobuf/proto"
	resources "google.golang.org/genproto/googleapis/ads/googleads/v2/resources"
	_ "google.golang.org/genproto/googleapis/api/annotations"
	status "google.golang.org/genproto/googleapis/rpc/status"
	grpc "google.golang.org/grpc"
	codes "google.golang.org/grpc/codes"
	status1 "google.golang.org/grpc/status"
	protoreflect "google.golang.org/protobuf/reflect/protoreflect"
	protoimpl "google.golang.org/protobuf/runtime/protoimpl"
	fieldmaskpb "google.golang.org/protobuf/types/known/fieldmaskpb"
)

const (
	// Verify that this generated code is sufficiently up-to-date.
	_ = protoimpl.EnforceVersion(20 - protoimpl.MinVersion)
	// Verify that runtime/protoimpl is sufficiently up-to-date.
	_ = protoimpl.EnforceVersion(protoimpl.MaxVersion - 20)
)

// This is a compile-time assertion that a sufficiently up-to-date version
// of the legacy proto package is being used.
const _ = proto.ProtoPackageIsVersion4

// Request message for [AdGroupService.GetAdGroup][google.ads.googleads.v2.services.AdGroupService.GetAdGroup].
type GetAdGroupRequest struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	// Required. The resource name of the ad group to fetch.
	ResourceName string `protobuf:"bytes,1,opt,name=resource_name,json=resourceName,proto3" json:"resource_name,omitempty"`
}

func (x *GetAdGroupRequest) Reset() {
	*x = GetAdGroupRequest{}
	if protoimpl.UnsafeEnabled {
		mi := &file_google_ads_googleads_v2_services_ad_group_service_proto_msgTypes[0]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *GetAdGroupRequest) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*GetAdGroupRequest) ProtoMessage() {}

func (x *GetAdGroupRequest) ProtoReflect() protoreflect.Message {
	mi := &file_google_ads_googleads_v2_services_ad_group_service_proto_msgTypes[0]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use GetAdGroupRequest.ProtoReflect.Descriptor instead.
func (*GetAdGroupRequest) Descriptor() ([]byte, []int) {
	return file_google_ads_googleads_v2_services_ad_group_service_proto_rawDescGZIP(), []int{0}
}

func (x *GetAdGroupRequest) GetResourceName() string {
	if x != nil {
		return x.ResourceName
	}
	return ""
}

// Request message for [AdGroupService.MutateAdGroups][google.ads.googleads.v2.services.AdGroupService.MutateAdGroups].
type MutateAdGroupsRequest struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	// Required. The ID of the customer whose ad groups are being modified.
	CustomerId string `protobuf:"bytes,1,opt,name=customer_id,json=customerId,proto3" json:"customer_id,omitempty"`
	// Required. The list of operations to perform on individual ad groups.
	Operations []*AdGroupOperation `protobuf:"bytes,2,rep,name=operations,proto3" json:"operations,omitempty"`
	// If true, successful operations will be carried out and invalid
	// operations will return errors. If false, all operations will be carried
	// out in one transaction if and only if they are all valid.
	// Default is false.
	PartialFailure bool `protobuf:"varint,3,opt,name=partial_failure,json=partialFailure,proto3" json:"partial_failure,omitempty"`
	// If true, the request is validated but not executed. Only errors are
	// returned, not results.
	ValidateOnly bool `protobuf:"varint,4,opt,name=validate_only,json=validateOnly,proto3" json:"validate_only,omitempty"`
}

func (x *MutateAdGroupsRequest) Reset() {
	*x = MutateAdGroupsRequest{}
	if protoimpl.UnsafeEnabled {
		mi := &file_google_ads_googleads_v2_services_ad_group_service_proto_msgTypes[1]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *MutateAdGroupsRequest) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*MutateAdGroupsRequest) ProtoMessage() {}

func (x *MutateAdGroupsRequest) ProtoReflect() protoreflect.Message {
	mi := &file_google_ads_googleads_v2_services_ad_group_service_proto_msgTypes[1]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use MutateAdGroupsRequest.ProtoReflect.Descriptor instead.
func (*MutateAdGroupsRequest) Descriptor() ([]byte, []int) {
	return file_google_ads_googleads_v2_services_ad_group_service_proto_rawDescGZIP(), []int{1}
}

func (x *MutateAdGroupsRequest) GetCustomerId() string {
	if x != nil {
		return x.CustomerId
	}
	return ""
}

func (x *MutateAdGroupsRequest) GetOperations() []*AdGroupOperation {
	if x != nil {
		return x.Operations
	}
	return nil
}

func (x *MutateAdGroupsRequest) GetPartialFailure() bool {
	if x != nil {
		return x.PartialFailure
	}
	return false
}

func (x *MutateAdGroupsRequest) GetValidateOnly() bool {
	if x != nil {
		return x.ValidateOnly
	}
	return false
}

// A single operation (create, update, remove) on an ad group.
type AdGroupOperation struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	// FieldMask that determines which resource fields are modified in an update.
	UpdateMask *fieldmaskpb.FieldMask `protobuf:"bytes,4,opt,name=update_mask,json=updateMask,proto3" json:"update_mask,omitempty"`
	// The mutate operation.
	//
	// Types that are assignable to Operation:
	//	*AdGroupOperation_Create
	//	*AdGroupOperation_Update
	//	*AdGroupOperation_Remove
	Operation isAdGroupOperation_Operation `protobuf_oneof:"operation"`
}

func (x *AdGroupOperation) Reset() {
	*x = AdGroupOperation{}
	if protoimpl.UnsafeEnabled {
		mi := &file_google_ads_googleads_v2_services_ad_group_service_proto_msgTypes[2]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *AdGroupOperation) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*AdGroupOperation) ProtoMessage() {}

func (x *AdGroupOperation) ProtoReflect() protoreflect.Message {
	mi := &file_google_ads_googleads_v2_services_ad_group_service_proto_msgTypes[2]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use AdGroupOperation.ProtoReflect.Descriptor instead.
func (*AdGroupOperation) Descriptor() ([]byte, []int) {
	return file_google_ads_googleads_v2_services_ad_group_service_proto_rawDescGZIP(), []int{2}
}

func (x *AdGroupOperation) GetUpdateMask() *fieldmaskpb.FieldMask {
	if x != nil {
		return x.UpdateMask
	}
	return nil
}

func (m *AdGroupOperation) GetOperation() isAdGroupOperation_Operation {
	if m != nil {
		return m.Operation
	}
	return nil
}

func (x *AdGroupOperation) GetCreate() *resources.AdGroup {
	if x, ok := x.GetOperation().(*AdGroupOperation_Create); ok {
		return x.Create
	}
	return nil
}

func (x *AdGroupOperation) GetUpdate() *resources.AdGroup {
	if x, ok := x.GetOperation().(*AdGroupOperation_Update); ok {
		return x.Update
	}
	return nil
}

func (x *AdGroupOperation) GetRemove() string {
	if x, ok := x.GetOperation().(*AdGroupOperation_Remove); ok {
		return x.Remove
	}
	return ""
}

type isAdGroupOperation_Operation interface {
	isAdGroupOperation_Operation()
}

type AdGroupOperation_Create struct {
	// Create operation: No resource name is expected for the new ad group.
	Create *resources.AdGroup `protobuf:"bytes,1,opt,name=create,proto3,oneof"`
}

type AdGroupOperation_Update struct {
	// Update operation: The ad group is expected to have a valid resource name.
	Update *resources.AdGroup `protobuf:"bytes,2,opt,name=update,proto3,oneof"`
}

type AdGroupOperation_Remove struct {
	// Remove operation: A resource name for the removed ad group is expected,
	// in this format:
	//
	// `customers/{customer_id}/adGroups/{ad_group_id}`
	Remove string `protobuf:"bytes,3,opt,name=remove,proto3,oneof"`
}

func (*AdGroupOperation_Create) isAdGroupOperation_Operation() {}

func (*AdGroupOperation_Update) isAdGroupOperation_Operation() {}

func (*AdGroupOperation_Remove) isAdGroupOperation_Operation() {}

// Response message for an ad group mutate.
type MutateAdGroupsResponse struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	// Errors that pertain to operation failures in the partial failure mode.
	// Returned only when partial_failure = true and all errors occur inside the
	// operations. If any errors occur outside the operations (e.g. auth errors),
	// we return an RPC level error.
	PartialFailureError *status.Status `protobuf:"bytes,3,opt,name=partial_failure_error,json=partialFailureError,proto3" json:"partial_failure_error,omitempty"`
	// All results for the mutate.
	Results []*MutateAdGroupResult `protobuf:"bytes,2,rep,name=results,proto3" json:"results,omitempty"`
}

func (x *MutateAdGroupsResponse) Reset() {
	*x = MutateAdGroupsResponse{}
	if protoimpl.UnsafeEnabled {
		mi := &file_google_ads_googleads_v2_services_ad_group_service_proto_msgTypes[3]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *MutateAdGroupsResponse) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*MutateAdGroupsResponse) ProtoMessage() {}

func (x *MutateAdGroupsResponse) ProtoReflect() protoreflect.Message {
	mi := &file_google_ads_googleads_v2_services_ad_group_service_proto_msgTypes[3]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use MutateAdGroupsResponse.ProtoReflect.Descriptor instead.
func (*MutateAdGroupsResponse) Descriptor() ([]byte, []int) {
	return file_google_ads_googleads_v2_services_ad_group_service_proto_rawDescGZIP(), []int{3}
}

func (x *MutateAdGroupsResponse) GetPartialFailureError() *status.Status {
	if x != nil {
		return x.PartialFailureError
	}
	return nil
}

func (x *MutateAdGroupsResponse) GetResults() []*MutateAdGroupResult {
	if x != nil {
		return x.Results
	}
	return nil
}

// The result for the ad group mutate.
type MutateAdGroupResult struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	// Returned for successful operations.
	ResourceName string `protobuf:"bytes,1,opt,name=resource_name,json=resourceName,proto3" json:"resource_name,omitempty"`
}

func (x *MutateAdGroupResult) Reset() {
	*x = MutateAdGroupResult{}
	if protoimpl.UnsafeEnabled {
		mi := &file_google_ads_googleads_v2_services_ad_group_service_proto_msgTypes[4]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *MutateAdGroupResult) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*MutateAdGroupResult) ProtoMessage() {}

func (x *MutateAdGroupResult) ProtoReflect() protoreflect.Message {
	mi := &file_google_ads_googleads_v2_services_ad_group_service_proto_msgTypes[4]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use MutateAdGroupResult.ProtoReflect.Descriptor instead.
func (*MutateAdGroupResult) Descriptor() ([]byte, []int) {
	return file_google_ads_googleads_v2_services_ad_group_service_proto_rawDescGZIP(), []int{4}
}

func (x *MutateAdGroupResult) GetResourceName() string {
	if x != nil {
		return x.ResourceName
	}
	return ""
}

var File_google_ads_googleads_v2_services_ad_group_service_proto protoreflect.FileDescriptor

var file_google_ads_googleads_v2_services_ad_group_service_proto_rawDesc = []byte{
	0x0a, 0x37, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2f, 0x61, 0x64, 0x73, 0x2f, 0x67, 0x6f, 0x6f,
	0x67, 0x6c, 0x65, 0x61, 0x64, 0x73, 0x2f, 0x76, 0x32, 0x2f, 0x73, 0x65, 0x72, 0x76, 0x69, 0x63,
	0x65, 0x73, 0x2f, 0x61, 0x64, 0x5f, 0x67, 0x72, 0x6f, 0x75, 0x70, 0x5f, 0x73, 0x65, 0x72, 0x76,
	0x69, 0x63, 0x65, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x12, 0x20, 0x67, 0x6f, 0x6f, 0x67, 0x6c,
	0x65, 0x2e, 0x61, 0x64, 0x73, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x64, 0x73, 0x2e,
	0x76, 0x32, 0x2e, 0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x73, 0x1a, 0x30, 0x67, 0x6f, 0x6f,
	0x67, 0x6c, 0x65, 0x2f, 0x61, 0x64, 0x73, 0x2f, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x64,
	0x73, 0x2f, 0x76, 0x32, 0x2f, 0x72, 0x65, 0x73, 0x6f, 0x75, 0x72, 0x63, 0x65, 0x73, 0x2f, 0x61,
	0x64, 0x5f, 0x67, 0x72, 0x6f, 0x75, 0x70, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x1a, 0x1c, 0x67,
	0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2f, 0x61, 0x70, 0x69, 0x2f, 0x61, 0x6e, 0x6e, 0x6f, 0x74, 0x61,
	0x74, 0x69, 0x6f, 0x6e, 0x73, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x1a, 0x17, 0x67, 0x6f, 0x6f,
	0x67, 0x6c, 0x65, 0x2f, 0x61, 0x70, 0x69, 0x2f, 0x63, 0x6c, 0x69, 0x65, 0x6e, 0x74, 0x2e, 0x70,
	0x72, 0x6f, 0x74, 0x6f, 0x1a, 0x1f, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2f, 0x61, 0x70, 0x69,
	0x2f, 0x66, 0x69, 0x65, 0x6c, 0x64, 0x5f, 0x62, 0x65, 0x68, 0x61, 0x76, 0x69, 0x6f, 0x72, 0x2e,
	0x70, 0x72, 0x6f, 0x74, 0x6f, 0x1a, 0x19, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2f, 0x61, 0x70,
	0x69, 0x2f, 0x72, 0x65, 0x73, 0x6f, 0x75, 0x72, 0x63, 0x65, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f,
	0x1a, 0x20, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2f, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x62, 0x75,
	0x66, 0x2f, 0x66, 0x69, 0x65, 0x6c, 0x64, 0x5f, 0x6d, 0x61, 0x73, 0x6b, 0x2e, 0x70, 0x72, 0x6f,
	0x74, 0x6f, 0x1a, 0x17, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2f, 0x72, 0x70, 0x63, 0x2f, 0x73,
	0x74, 0x61, 0x74, 0x75, 0x73, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x22, 0x62, 0x0a, 0x11, 0x47,
	0x65, 0x74, 0x41, 0x64, 0x47, 0x72, 0x6f, 0x75, 0x70, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74,
	0x12, 0x4d, 0x0a, 0x0d, 0x72, 0x65, 0x73, 0x6f, 0x75, 0x72, 0x63, 0x65, 0x5f, 0x6e, 0x61, 0x6d,
	0x65, 0x18, 0x01, 0x20, 0x01, 0x28, 0x09, 0x42, 0x28, 0xe0, 0x41, 0x02, 0xfa, 0x41, 0x22, 0x0a,
	0x20, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x64, 0x73, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c,
	0x65, 0x61, 0x70, 0x69, 0x73, 0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x41, 0x64, 0x47, 0x72, 0x6f, 0x75,
	0x70, 0x52, 0x0c, 0x72, 0x65, 0x73, 0x6f, 0x75, 0x72, 0x63, 0x65, 0x4e, 0x61, 0x6d, 0x65, 0x22,
	0xe4, 0x01, 0x0a, 0x15, 0x4d, 0x75, 0x74, 0x61, 0x74, 0x65, 0x41, 0x64, 0x47, 0x72, 0x6f, 0x75,
	0x70, 0x73, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x12, 0x24, 0x0a, 0x0b, 0x63, 0x75, 0x73,
	0x74, 0x6f, 0x6d, 0x65, 0x72, 0x5f, 0x69, 0x64, 0x18, 0x01, 0x20, 0x01, 0x28, 0x09, 0x42, 0x03,
	0xe0, 0x41, 0x02, 0x52, 0x0a, 0x63, 0x75, 0x73, 0x74, 0x6f, 0x6d, 0x65, 0x72, 0x49, 0x64, 0x12,
	0x57, 0x0a, 0x0a, 0x6f, 0x70, 0x65, 0x72, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x73, 0x18, 0x02, 0x20,
	0x03, 0x28, 0x0b, 0x32, 0x32, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2e, 0x61, 0x64, 0x73,
	0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x64, 0x73, 0x2e, 0x76, 0x32, 0x2e, 0x73, 0x65,
	0x72, 0x76, 0x69, 0x63, 0x65, 0x73, 0x2e, 0x41, 0x64, 0x47, 0x72, 0x6f, 0x75, 0x70, 0x4f, 0x70,
	0x65, 0x72, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x42, 0x03, 0xe0, 0x41, 0x02, 0x52, 0x0a, 0x6f, 0x70,
	0x65, 0x72, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x73, 0x12, 0x27, 0x0a, 0x0f, 0x70, 0x61, 0x72, 0x74,
	0x69, 0x61, 0x6c, 0x5f, 0x66, 0x61, 0x69, 0x6c, 0x75, 0x72, 0x65, 0x18, 0x03, 0x20, 0x01, 0x28,
	0x08, 0x52, 0x0e, 0x70, 0x61, 0x72, 0x74, 0x69, 0x61, 0x6c, 0x46, 0x61, 0x69, 0x6c, 0x75, 0x72,
	0x65, 0x12, 0x23, 0x0a, 0x0d, 0x76, 0x61, 0x6c, 0x69, 0x64, 0x61, 0x74, 0x65, 0x5f, 0x6f, 0x6e,
	0x6c, 0x79, 0x18, 0x04, 0x20, 0x01, 0x28, 0x08, 0x52, 0x0c, 0x76, 0x61, 0x6c, 0x69, 0x64, 0x61,
	0x74, 0x65, 0x4f, 0x6e, 0x6c, 0x79, 0x22, 0x82, 0x02, 0x0a, 0x10, 0x41, 0x64, 0x47, 0x72, 0x6f,
	0x75, 0x70, 0x4f, 0x70, 0x65, 0x72, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x12, 0x3b, 0x0a, 0x0b, 0x75,
	0x70, 0x64, 0x61, 0x74, 0x65, 0x5f, 0x6d, 0x61, 0x73, 0x6b, 0x18, 0x04, 0x20, 0x01, 0x28, 0x0b,
	0x32, 0x1a, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x62,
	0x75, 0x66, 0x2e, 0x46, 0x69, 0x65, 0x6c, 0x64, 0x4d, 0x61, 0x73, 0x6b, 0x52, 0x0a, 0x75, 0x70,
	0x64, 0x61, 0x74, 0x65, 0x4d, 0x61, 0x73, 0x6b, 0x12, 0x44, 0x0a, 0x06, 0x63, 0x72, 0x65, 0x61,
	0x74, 0x65, 0x18, 0x01, 0x20, 0x01, 0x28, 0x0b, 0x32, 0x2a, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c,
	0x65, 0x2e, 0x61, 0x64, 0x73, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x64, 0x73, 0x2e,
	0x76, 0x32, 0x2e, 0x72, 0x65, 0x73, 0x6f, 0x75, 0x72, 0x63, 0x65, 0x73, 0x2e, 0x41, 0x64, 0x47,
	0x72, 0x6f, 0x75, 0x70, 0x48, 0x00, 0x52, 0x06, 0x63, 0x72, 0x65, 0x61, 0x74, 0x65, 0x12, 0x44,
	0x0a, 0x06, 0x75, 0x70, 0x64, 0x61, 0x74, 0x65, 0x18, 0x02, 0x20, 0x01, 0x28, 0x0b, 0x32, 0x2a,
	0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2e, 0x61, 0x64, 0x73, 0x2e, 0x67, 0x6f, 0x6f, 0x67,
	0x6c, 0x65, 0x61, 0x64, 0x73, 0x2e, 0x76, 0x32, 0x2e, 0x72, 0x65, 0x73, 0x6f, 0x75, 0x72, 0x63,
	0x65, 0x73, 0x2e, 0x41, 0x64, 0x47, 0x72, 0x6f, 0x75, 0x70, 0x48, 0x00, 0x52, 0x06, 0x75, 0x70,
	0x64, 0x61, 0x74, 0x65, 0x12, 0x18, 0x0a, 0x06, 0x72, 0x65, 0x6d, 0x6f, 0x76, 0x65, 0x18, 0x03,
	0x20, 0x01, 0x28, 0x09, 0x48, 0x00, 0x52, 0x06, 0x72, 0x65, 0x6d, 0x6f, 0x76, 0x65, 0x42, 0x0b,
	0x0a, 0x09, 0x6f, 0x70, 0x65, 0x72, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x22, 0xb1, 0x01, 0x0a, 0x16,
	0x4d, 0x75, 0x74, 0x61, 0x74, 0x65, 0x41, 0x64, 0x47, 0x72, 0x6f, 0x75, 0x70, 0x73, 0x52, 0x65,
	0x73, 0x70, 0x6f, 0x6e, 0x73, 0x65, 0x12, 0x46, 0x0a, 0x15, 0x70, 0x61, 0x72, 0x74, 0x69, 0x61,
	0x6c, 0x5f, 0x66, 0x61, 0x69, 0x6c, 0x75, 0x72, 0x65, 0x5f, 0x65, 0x72, 0x72, 0x6f, 0x72, 0x18,
	0x03, 0x20, 0x01, 0x28, 0x0b, 0x32, 0x12, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2e, 0x72,
	0x70, 0x63, 0x2e, 0x53, 0x74, 0x61, 0x74, 0x75, 0x73, 0x52, 0x13, 0x70, 0x61, 0x72, 0x74, 0x69,
	0x61, 0x6c, 0x46, 0x61, 0x69, 0x6c, 0x75, 0x72, 0x65, 0x45, 0x72, 0x72, 0x6f, 0x72, 0x12, 0x4f,
	0x0a, 0x07, 0x72, 0x65, 0x73, 0x75, 0x6c, 0x74, 0x73, 0x18, 0x02, 0x20, 0x03, 0x28, 0x0b, 0x32,
	0x35, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2e, 0x61, 0x64, 0x73, 0x2e, 0x67, 0x6f, 0x6f,
	0x67, 0x6c, 0x65, 0x61, 0x64, 0x73, 0x2e, 0x76, 0x32, 0x2e, 0x73, 0x65, 0x72, 0x76, 0x69, 0x63,
	0x65, 0x73, 0x2e, 0x4d, 0x75, 0x74, 0x61, 0x74, 0x65, 0x41, 0x64, 0x47, 0x72, 0x6f, 0x75, 0x70,
	0x52, 0x65, 0x73, 0x75, 0x6c, 0x74, 0x52, 0x07, 0x72, 0x65, 0x73, 0x75, 0x6c, 0x74, 0x73, 0x22,
	0x3a, 0x0a, 0x13, 0x4d, 0x75, 0x74, 0x61, 0x74, 0x65, 0x41, 0x64, 0x47, 0x72, 0x6f, 0x75, 0x70,
	0x52, 0x65, 0x73, 0x75, 0x6c, 0x74, 0x12, 0x23, 0x0a, 0x0d, 0x72, 0x65, 0x73, 0x6f, 0x75, 0x72,
	0x63, 0x65, 0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x18, 0x01, 0x20, 0x01, 0x28, 0x09, 0x52, 0x0c, 0x72,
	0x65, 0x73, 0x6f, 0x75, 0x72, 0x63, 0x65, 0x4e, 0x61, 0x6d, 0x65, 0x32, 0xba, 0x03, 0x0a, 0x0e,
	0x41, 0x64, 0x47, 0x72, 0x6f, 0x75, 0x70, 0x53, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x12, 0xb1,
	0x01, 0x0a, 0x0a, 0x47, 0x65, 0x74, 0x41, 0x64, 0x47, 0x72, 0x6f, 0x75, 0x70, 0x12, 0x33, 0x2e,
	0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2e, 0x61, 0x64, 0x73, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c,
	0x65, 0x61, 0x64, 0x73, 0x2e, 0x76, 0x32, 0x2e, 0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x73,
	0x2e, 0x47, 0x65, 0x74, 0x41, 0x64, 0x47, 0x72, 0x6f, 0x75, 0x70, 0x52, 0x65, 0x71, 0x75, 0x65,
	0x73, 0x74, 0x1a, 0x2a, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2e, 0x61, 0x64, 0x73, 0x2e,
	0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x64, 0x73, 0x2e, 0x76, 0x32, 0x2e, 0x72, 0x65, 0x73,
	0x6f, 0x75, 0x72, 0x63, 0x65, 0x73, 0x2e, 0x41, 0x64, 0x47, 0x72, 0x6f, 0x75, 0x70, 0x22, 0x42,
	0x82, 0xd3, 0xe4, 0x93, 0x02, 0x2c, 0x12, 0x2a, 0x2f, 0x76, 0x32, 0x2f, 0x7b, 0x72, 0x65, 0x73,
	0x6f, 0x75, 0x72, 0x63, 0x65, 0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x3d, 0x63, 0x75, 0x73, 0x74, 0x6f,
	0x6d, 0x65, 0x72, 0x73, 0x2f, 0x2a, 0x2f, 0x61, 0x64, 0x47, 0x72, 0x6f, 0x75, 0x70, 0x73, 0x2f,
	0x2a, 0x7d, 0xda, 0x41, 0x0d, 0x72, 0x65, 0x73, 0x6f, 0x75, 0x72, 0x63, 0x65, 0x5f, 0x6e, 0x61,
	0x6d, 0x65, 0x12, 0xd6, 0x01, 0x0a, 0x0e, 0x4d, 0x75, 0x74, 0x61, 0x74, 0x65, 0x41, 0x64, 0x47,
	0x72, 0x6f, 0x75, 0x70, 0x73, 0x12, 0x37, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2e, 0x61,
	0x64, 0x73, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x64, 0x73, 0x2e, 0x76, 0x32, 0x2e,
	0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x73, 0x2e, 0x4d, 0x75, 0x74, 0x61, 0x74, 0x65, 0x41,
	0x64, 0x47, 0x72, 0x6f, 0x75, 0x70, 0x73, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x1a, 0x38,
	0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2e, 0x61, 0x64, 0x73, 0x2e, 0x67, 0x6f, 0x6f, 0x67,
	0x6c, 0x65, 0x61, 0x64, 0x73, 0x2e, 0x76, 0x32, 0x2e, 0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65,
	0x73, 0x2e, 0x4d, 0x75, 0x74, 0x61, 0x74, 0x65, 0x41, 0x64, 0x47, 0x72, 0x6f, 0x75, 0x70, 0x73,
	0x52, 0x65, 0x73, 0x70, 0x6f, 0x6e, 0x73, 0x65, 0x22, 0x51, 0x82, 0xd3, 0xe4, 0x93, 0x02, 0x32,
	0x22, 0x2d, 0x2f, 0x76, 0x32, 0x2f, 0x63, 0x75, 0x73, 0x74, 0x6f, 0x6d, 0x65, 0x72, 0x73, 0x2f,
	0x7b, 0x63, 0x75, 0x73, 0x74, 0x6f, 0x6d, 0x65, 0x72, 0x5f, 0x69, 0x64, 0x3d, 0x2a, 0x7d, 0x2f,
	0x61, 0x64, 0x47, 0x72, 0x6f, 0x75, 0x70, 0x73, 0x3a, 0x6d, 0x75, 0x74, 0x61, 0x74, 0x65, 0x3a,
	0x01, 0x2a, 0xda, 0x41, 0x16, 0x63, 0x75, 0x73, 0x74, 0x6f, 0x6d, 0x65, 0x72, 0x5f, 0x69, 0x64,
	0x2c, 0x6f, 0x70, 0x65, 0x72, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x73, 0x1a, 0x1b, 0xca, 0x41, 0x18,
	0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x64, 0x73, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65,
	0x61, 0x70, 0x69, 0x73, 0x2e, 0x63, 0x6f, 0x6d, 0x42, 0xfa, 0x01, 0x0a, 0x24, 0x63, 0x6f, 0x6d,
	0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2e, 0x61, 0x64, 0x73, 0x2e, 0x67, 0x6f, 0x6f, 0x67,
	0x6c, 0x65, 0x61, 0x64, 0x73, 0x2e, 0x76, 0x32, 0x2e, 0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65,
	0x73, 0x42, 0x13, 0x41, 0x64, 0x47, 0x72, 0x6f, 0x75, 0x70, 0x53, 0x65, 0x72, 0x76, 0x69, 0x63,
	0x65, 0x50, 0x72, 0x6f, 0x74, 0x6f, 0x50, 0x01, 0x5a, 0x48, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65,
	0x2e, 0x67, 0x6f, 0x6c, 0x61, 0x6e, 0x67, 0x2e, 0x6f, 0x72, 0x67, 0x2f, 0x67, 0x65, 0x6e, 0x70,
	0x72, 0x6f, 0x74, 0x6f, 0x2f, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x70, 0x69, 0x73, 0x2f,
	0x61, 0x64, 0x73, 0x2f, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x64, 0x73, 0x2f, 0x76, 0x32,
	0x2f, 0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x73, 0x3b, 0x73, 0x65, 0x72, 0x76, 0x69, 0x63,
	0x65, 0x73, 0xa2, 0x02, 0x03, 0x47, 0x41, 0x41, 0xaa, 0x02, 0x20, 0x47, 0x6f, 0x6f, 0x67, 0x6c,
	0x65, 0x2e, 0x41, 0x64, 0x73, 0x2e, 0x47, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x41, 0x64, 0x73, 0x2e,
	0x56, 0x32, 0x2e, 0x53, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x73, 0xca, 0x02, 0x20, 0x47, 0x6f,
	0x6f, 0x67, 0x6c, 0x65, 0x5c, 0x41, 0x64, 0x73, 0x5c, 0x47, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x41,
	0x64, 0x73, 0x5c, 0x56, 0x32, 0x5c, 0x53, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x73, 0xea, 0x02,
	0x24, 0x47, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x3a, 0x3a, 0x41, 0x64, 0x73, 0x3a, 0x3a, 0x47, 0x6f,
	0x6f, 0x67, 0x6c, 0x65, 0x41, 0x64, 0x73, 0x3a, 0x3a, 0x56, 0x32, 0x3a, 0x3a, 0x53, 0x65, 0x72,
	0x76, 0x69, 0x63, 0x65, 0x73, 0x62, 0x06, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x33,
}

var (
	file_google_ads_googleads_v2_services_ad_group_service_proto_rawDescOnce sync.Once
	file_google_ads_googleads_v2_services_ad_group_service_proto_rawDescData = file_google_ads_googleads_v2_services_ad_group_service_proto_rawDesc
)

func file_google_ads_googleads_v2_services_ad_group_service_proto_rawDescGZIP() []byte {
	file_google_ads_googleads_v2_services_ad_group_service_proto_rawDescOnce.Do(func() {
		file_google_ads_googleads_v2_services_ad_group_service_proto_rawDescData = protoimpl.X.CompressGZIP(file_google_ads_googleads_v2_services_ad_group_service_proto_rawDescData)
	})
	return file_google_ads_googleads_v2_services_ad_group_service_proto_rawDescData
}

var file_google_ads_googleads_v2_services_ad_group_service_proto_msgTypes = make([]protoimpl.MessageInfo, 5)
var file_google_ads_googleads_v2_services_ad_group_service_proto_goTypes = []interface{}{
	(*GetAdGroupRequest)(nil),      // 0: google.ads.googleads.v2.services.GetAdGroupRequest
	(*MutateAdGroupsRequest)(nil),  // 1: google.ads.googleads.v2.services.MutateAdGroupsRequest
	(*AdGroupOperation)(nil),       // 2: google.ads.googleads.v2.services.AdGroupOperation
	(*MutateAdGroupsResponse)(nil), // 3: google.ads.googleads.v2.services.MutateAdGroupsResponse
	(*MutateAdGroupResult)(nil),    // 4: google.ads.googleads.v2.services.MutateAdGroupResult
	(*fieldmaskpb.FieldMask)(nil),  // 5: google.protobuf.FieldMask
	(*resources.AdGroup)(nil),      // 6: google.ads.googleads.v2.resources.AdGroup
	(*status.Status)(nil),          // 7: google.rpc.Status
}
var file_google_ads_googleads_v2_services_ad_group_service_proto_depIdxs = []int32{
	2, // 0: google.ads.googleads.v2.services.MutateAdGroupsRequest.operations:type_name -> google.ads.googleads.v2.services.AdGroupOperation
	5, // 1: google.ads.googleads.v2.services.AdGroupOperation.update_mask:type_name -> google.protobuf.FieldMask
	6, // 2: google.ads.googleads.v2.services.AdGroupOperation.create:type_name -> google.ads.googleads.v2.resources.AdGroup
	6, // 3: google.ads.googleads.v2.services.AdGroupOperation.update:type_name -> google.ads.googleads.v2.resources.AdGroup
	7, // 4: google.ads.googleads.v2.services.MutateAdGroupsResponse.partial_failure_error:type_name -> google.rpc.Status
	4, // 5: google.ads.googleads.v2.services.MutateAdGroupsResponse.results:type_name -> google.ads.googleads.v2.services.MutateAdGroupResult
	0, // 6: google.ads.googleads.v2.services.AdGroupService.GetAdGroup:input_type -> google.ads.googleads.v2.services.GetAdGroupRequest
	1, // 7: google.ads.googleads.v2.services.AdGroupService.MutateAdGroups:input_type -> google.ads.googleads.v2.services.MutateAdGroupsRequest
	6, // 8: google.ads.googleads.v2.services.AdGroupService.GetAdGroup:output_type -> google.ads.googleads.v2.resources.AdGroup
	3, // 9: google.ads.googleads.v2.services.AdGroupService.MutateAdGroups:output_type -> google.ads.googleads.v2.services.MutateAdGroupsResponse
	8, // [8:10] is the sub-list for method output_type
	6, // [6:8] is the sub-list for method input_type
	6, // [6:6] is the sub-list for extension type_name
	6, // [6:6] is the sub-list for extension extendee
	0, // [0:6] is the sub-list for field type_name
}

func init() { file_google_ads_googleads_v2_services_ad_group_service_proto_init() }
func file_google_ads_googleads_v2_services_ad_group_service_proto_init() {
	if File_google_ads_googleads_v2_services_ad_group_service_proto != nil {
		return
	}
	if !protoimpl.UnsafeEnabled {
		file_google_ads_googleads_v2_services_ad_group_service_proto_msgTypes[0].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*GetAdGroupRequest); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
		file_google_ads_googleads_v2_services_ad_group_service_proto_msgTypes[1].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*MutateAdGroupsRequest); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
		file_google_ads_googleads_v2_services_ad_group_service_proto_msgTypes[2].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*AdGroupOperation); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
		file_google_ads_googleads_v2_services_ad_group_service_proto_msgTypes[3].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*MutateAdGroupsResponse); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
		file_google_ads_googleads_v2_services_ad_group_service_proto_msgTypes[4].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*MutateAdGroupResult); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
	}
	file_google_ads_googleads_v2_services_ad_group_service_proto_msgTypes[2].OneofWrappers = []interface{}{
		(*AdGroupOperation_Create)(nil),
		(*AdGroupOperation_Update)(nil),
		(*AdGroupOperation_Remove)(nil),
	}
	type x struct{}
	out := protoimpl.TypeBuilder{
		File: protoimpl.DescBuilder{
			GoPackagePath: reflect.TypeOf(x{}).PkgPath(),
			RawDescriptor: file_google_ads_googleads_v2_services_ad_group_service_proto_rawDesc,
			NumEnums:      0,
			NumMessages:   5,
			NumExtensions: 0,
			NumServices:   1,
		},
		GoTypes:           file_google_ads_googleads_v2_services_ad_group_service_proto_goTypes,
		DependencyIndexes: file_google_ads_googleads_v2_services_ad_group_service_proto_depIdxs,
		MessageInfos:      file_google_ads_googleads_v2_services_ad_group_service_proto_msgTypes,
	}.Build()
	File_google_ads_googleads_v2_services_ad_group_service_proto = out.File
	file_google_ads_googleads_v2_services_ad_group_service_proto_rawDesc = nil
	file_google_ads_googleads_v2_services_ad_group_service_proto_goTypes = nil
	file_google_ads_googleads_v2_services_ad_group_service_proto_depIdxs = nil
}

// Reference imports to suppress errors if they are not otherwise used.
var _ context.Context
var _ grpc.ClientConnInterface

// This is a compile-time assertion to ensure that this generated file
// is compatible with the grpc package it is being compiled against.
const _ = grpc.SupportPackageIsVersion6

// AdGroupServiceClient is the client API for AdGroupService service.
//
// For semantics around ctx use and closing/ending streaming RPCs, please refer to https://godoc.org/google.golang.org/grpc#ClientConn.NewStream.
type AdGroupServiceClient interface {
	// Returns the requested ad group in full detail.
	GetAdGroup(ctx context.Context, in *GetAdGroupRequest, opts ...grpc.CallOption) (*resources.AdGroup, error)
	// Creates, updates, or removes ad groups. Operation statuses are returned.
	MutateAdGroups(ctx context.Context, in *MutateAdGroupsRequest, opts ...grpc.CallOption) (*MutateAdGroupsResponse, error)
}

type adGroupServiceClient struct {
	cc grpc.ClientConnInterface
}

func NewAdGroupServiceClient(cc grpc.ClientConnInterface) AdGroupServiceClient {
	return &adGroupServiceClient{cc}
}

func (c *adGroupServiceClient) GetAdGroup(ctx context.Context, in *GetAdGroupRequest, opts ...grpc.CallOption) (*resources.AdGroup, error) {
	out := new(resources.AdGroup)
	err := c.cc.Invoke(ctx, "/google.ads.googleads.v2.services.AdGroupService/GetAdGroup", in, out, opts...)
	if err != nil {
		return nil, err
	}
	return out, nil
}

func (c *adGroupServiceClient) MutateAdGroups(ctx context.Context, in *MutateAdGroupsRequest, opts ...grpc.CallOption) (*MutateAdGroupsResponse, error) {
	out := new(MutateAdGroupsResponse)
	err := c.cc.Invoke(ctx, "/google.ads.googleads.v2.services.AdGroupService/MutateAdGroups", in, out, opts...)
	if err != nil {
		return nil, err
	}
	return out, nil
}

// AdGroupServiceServer is the server API for AdGroupService service.
type AdGroupServiceServer interface {
	// Returns the requested ad group in full detail.
	GetAdGroup(context.Context, *GetAdGroupRequest) (*resources.AdGroup, error)
	// Creates, updates, or removes ad groups. Operation statuses are returned.
	MutateAdGroups(context.Context, *MutateAdGroupsRequest) (*MutateAdGroupsResponse, error)
}

// UnimplementedAdGroupServiceServer can be embedded to have forward compatible implementations.
type UnimplementedAdGroupServiceServer struct {
}

func (*UnimplementedAdGroupServiceServer) GetAdGroup(context.Context, *GetAdGroupRequest) (*resources.AdGroup, error) {
	return nil, status1.Errorf(codes.Unimplemented, "method GetAdGroup not implemented")
}
func (*UnimplementedAdGroupServiceServer) MutateAdGroups(context.Context, *MutateAdGroupsRequest) (*MutateAdGroupsResponse, error) {
	return nil, status1.Errorf(codes.Unimplemented, "method MutateAdGroups not implemented")
}

func RegisterAdGroupServiceServer(s *grpc.Server, srv AdGroupServiceServer) {
	s.RegisterService(&_AdGroupService_serviceDesc, srv)
}

func _AdGroupService_GetAdGroup_Handler(srv interface{}, ctx context.Context, dec func(interface{}) error, interceptor grpc.UnaryServerInterceptor) (interface{}, error) {
	in := new(GetAdGroupRequest)
	if err := dec(in); err != nil {
		return nil, err
	}
	if interceptor == nil {
		return srv.(AdGroupServiceServer).GetAdGroup(ctx, in)
	}
	info := &grpc.UnaryServerInfo{
		Server:     srv,
		FullMethod: "/google.ads.googleads.v2.services.AdGroupService/GetAdGroup",
	}
	handler := func(ctx context.Context, req interface{}) (interface{}, error) {
		return srv.(AdGroupServiceServer).GetAdGroup(ctx, req.(*GetAdGroupRequest))
	}
	return interceptor(ctx, in, info, handler)
}

func _AdGroupService_MutateAdGroups_Handler(srv interface{}, ctx context.Context, dec func(interface{}) error, interceptor grpc.UnaryServerInterceptor) (interface{}, error) {
	in := new(MutateAdGroupsRequest)
	if err := dec(in); err != nil {
		return nil, err
	}
	if interceptor == nil {
		return srv.(AdGroupServiceServer).MutateAdGroups(ctx, in)
	}
	info := &grpc.UnaryServerInfo{
		Server:     srv,
		FullMethod: "/google.ads.googleads.v2.services.AdGroupService/MutateAdGroups",
	}
	handler := func(ctx context.Context, req interface{}) (interface{}, error) {
		return srv.(AdGroupServiceServer).MutateAdGroups(ctx, req.(*MutateAdGroupsRequest))
	}
	return interceptor(ctx, in, info, handler)
}

var _AdGroupService_serviceDesc = grpc.ServiceDesc{
	ServiceName: "google.ads.googleads.v2.services.AdGroupService",
	HandlerType: (*AdGroupServiceServer)(nil),
	Methods: []grpc.MethodDesc{
		{
			MethodName: "GetAdGroup",
			Handler:    _AdGroupService_GetAdGroup_Handler,
		},
		{
			MethodName: "MutateAdGroups",
			Handler:    _AdGroupService_MutateAdGroups_Handler,
		},
	},
	Streams:  []grpc.StreamDesc{},
	Metadata: "google/ads/googleads/v2/services/ad_group_service.proto",
}
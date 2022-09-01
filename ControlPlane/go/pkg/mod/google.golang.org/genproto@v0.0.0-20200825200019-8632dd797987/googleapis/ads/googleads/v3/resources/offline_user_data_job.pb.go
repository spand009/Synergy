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
// source: google/ads/googleads/v3/resources/offline_user_data_job.proto

package resources

import (
	reflect "reflect"
	sync "sync"

	proto "github.com/golang/protobuf/proto"
	common "google.golang.org/genproto/googleapis/ads/googleads/v3/common"
	enums "google.golang.org/genproto/googleapis/ads/googleads/v3/enums"
	_ "google.golang.org/genproto/googleapis/api/annotations"
	protoreflect "google.golang.org/protobuf/reflect/protoreflect"
	protoimpl "google.golang.org/protobuf/runtime/protoimpl"
	wrapperspb "google.golang.org/protobuf/types/known/wrapperspb"
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

// A job containing offline user data of store visitors, or user list members
// that will be processed asynchronously. The uploaded data isn't readable and
// the processing results of the job can only be read using
// OfflineUserDataJobService.GetOfflineUserDataJob.
type OfflineUserDataJob struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	// Immutable. The resource name of the offline user data job.
	// Offline user data job resource names have the form:
	//
	// `customers/{customer_id}/offlineUserDataJobs/{offline_user_data_job_id}`
	ResourceName string `protobuf:"bytes,1,opt,name=resource_name,json=resourceName,proto3" json:"resource_name,omitempty"`
	// Output only. ID of this offline user data job.
	Id *wrapperspb.Int64Value `protobuf:"bytes,2,opt,name=id,proto3" json:"id,omitempty"`
	// Output only. User specified job ID.
	ExternalId *wrapperspb.Int64Value `protobuf:"bytes,3,opt,name=external_id,json=externalId,proto3" json:"external_id,omitempty"`
	// Output only. Type of the job.
	Type enums.OfflineUserDataJobTypeEnum_OfflineUserDataJobType `protobuf:"varint,4,opt,name=type,proto3,enum=google.ads.googleads.v3.enums.OfflineUserDataJobTypeEnum_OfflineUserDataJobType" json:"type,omitempty"`
	// Output only. Status of the job.
	Status enums.OfflineUserDataJobStatusEnum_OfflineUserDataJobStatus `protobuf:"varint,5,opt,name=status,proto3,enum=google.ads.googleads.v3.enums.OfflineUserDataJobStatusEnum_OfflineUserDataJobStatus" json:"status,omitempty"`
	// Output only. Reason for the processing failure, if status is FAILED.
	FailureReason enums.OfflineUserDataJobFailureReasonEnum_OfflineUserDataJobFailureReason `protobuf:"varint,6,opt,name=failure_reason,json=failureReason,proto3,enum=google.ads.googleads.v3.enums.OfflineUserDataJobFailureReasonEnum_OfflineUserDataJobFailureReason" json:"failure_reason,omitempty"`
	// Metadata of the job.
	//
	// Types that are assignable to Metadata:
	//	*OfflineUserDataJob_CustomerMatchUserListMetadata
	//	*OfflineUserDataJob_StoreSalesMetadata
	Metadata isOfflineUserDataJob_Metadata `protobuf_oneof:"metadata"`
}

func (x *OfflineUserDataJob) Reset() {
	*x = OfflineUserDataJob{}
	if protoimpl.UnsafeEnabled {
		mi := &file_google_ads_googleads_v3_resources_offline_user_data_job_proto_msgTypes[0]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *OfflineUserDataJob) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*OfflineUserDataJob) ProtoMessage() {}

func (x *OfflineUserDataJob) ProtoReflect() protoreflect.Message {
	mi := &file_google_ads_googleads_v3_resources_offline_user_data_job_proto_msgTypes[0]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use OfflineUserDataJob.ProtoReflect.Descriptor instead.
func (*OfflineUserDataJob) Descriptor() ([]byte, []int) {
	return file_google_ads_googleads_v3_resources_offline_user_data_job_proto_rawDescGZIP(), []int{0}
}

func (x *OfflineUserDataJob) GetResourceName() string {
	if x != nil {
		return x.ResourceName
	}
	return ""
}

func (x *OfflineUserDataJob) GetId() *wrapperspb.Int64Value {
	if x != nil {
		return x.Id
	}
	return nil
}

func (x *OfflineUserDataJob) GetExternalId() *wrapperspb.Int64Value {
	if x != nil {
		return x.ExternalId
	}
	return nil
}

func (x *OfflineUserDataJob) GetType() enums.OfflineUserDataJobTypeEnum_OfflineUserDataJobType {
	if x != nil {
		return x.Type
	}
	return enums.OfflineUserDataJobTypeEnum_UNSPECIFIED
}

func (x *OfflineUserDataJob) GetStatus() enums.OfflineUserDataJobStatusEnum_OfflineUserDataJobStatus {
	if x != nil {
		return x.Status
	}
	return enums.OfflineUserDataJobStatusEnum_UNSPECIFIED
}

func (x *OfflineUserDataJob) GetFailureReason() enums.OfflineUserDataJobFailureReasonEnum_OfflineUserDataJobFailureReason {
	if x != nil {
		return x.FailureReason
	}
	return enums.OfflineUserDataJobFailureReasonEnum_UNSPECIFIED
}

func (m *OfflineUserDataJob) GetMetadata() isOfflineUserDataJob_Metadata {
	if m != nil {
		return m.Metadata
	}
	return nil
}

func (x *OfflineUserDataJob) GetCustomerMatchUserListMetadata() *common.CustomerMatchUserListMetadata {
	if x, ok := x.GetMetadata().(*OfflineUserDataJob_CustomerMatchUserListMetadata); ok {
		return x.CustomerMatchUserListMetadata
	}
	return nil
}

func (x *OfflineUserDataJob) GetStoreSalesMetadata() *common.StoreSalesMetadata {
	if x, ok := x.GetMetadata().(*OfflineUserDataJob_StoreSalesMetadata); ok {
		return x.StoreSalesMetadata
	}
	return nil
}

type isOfflineUserDataJob_Metadata interface {
	isOfflineUserDataJob_Metadata()
}

type OfflineUserDataJob_CustomerMatchUserListMetadata struct {
	// Output only. Metadata for data updates to a CRM-based user list.
	CustomerMatchUserListMetadata *common.CustomerMatchUserListMetadata `protobuf:"bytes,7,opt,name=customer_match_user_list_metadata,json=customerMatchUserListMetadata,proto3,oneof"`
}

type OfflineUserDataJob_StoreSalesMetadata struct {
	// Output only. Metadata for store sales data update.
	StoreSalesMetadata *common.StoreSalesMetadata `protobuf:"bytes,8,opt,name=store_sales_metadata,json=storeSalesMetadata,proto3,oneof"`
}

func (*OfflineUserDataJob_CustomerMatchUserListMetadata) isOfflineUserDataJob_Metadata() {}

func (*OfflineUserDataJob_StoreSalesMetadata) isOfflineUserDataJob_Metadata() {}

var File_google_ads_googleads_v3_resources_offline_user_data_job_proto protoreflect.FileDescriptor

var file_google_ads_googleads_v3_resources_offline_user_data_job_proto_rawDesc = []byte{
	0x0a, 0x3d, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2f, 0x61, 0x64, 0x73, 0x2f, 0x67, 0x6f, 0x6f,
	0x67, 0x6c, 0x65, 0x61, 0x64, 0x73, 0x2f, 0x76, 0x33, 0x2f, 0x72, 0x65, 0x73, 0x6f, 0x75, 0x72,
	0x63, 0x65, 0x73, 0x2f, 0x6f, 0x66, 0x66, 0x6c, 0x69, 0x6e, 0x65, 0x5f, 0x75, 0x73, 0x65, 0x72,
	0x5f, 0x64, 0x61, 0x74, 0x61, 0x5f, 0x6a, 0x6f, 0x62, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x12,
	0x21, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2e, 0x61, 0x64, 0x73, 0x2e, 0x67, 0x6f, 0x6f, 0x67,
	0x6c, 0x65, 0x61, 0x64, 0x73, 0x2e, 0x76, 0x33, 0x2e, 0x72, 0x65, 0x73, 0x6f, 0x75, 0x72, 0x63,
	0x65, 0x73, 0x1a, 0x36, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2f, 0x61, 0x64, 0x73, 0x2f, 0x67,
	0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x64, 0x73, 0x2f, 0x76, 0x33, 0x2f, 0x63, 0x6f, 0x6d, 0x6d,
	0x6f, 0x6e, 0x2f, 0x6f, 0x66, 0x66, 0x6c, 0x69, 0x6e, 0x65, 0x5f, 0x75, 0x73, 0x65, 0x72, 0x5f,
	0x64, 0x61, 0x74, 0x61, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x1a, 0x48, 0x67, 0x6f, 0x6f, 0x67,
	0x6c, 0x65, 0x2f, 0x61, 0x64, 0x73, 0x2f, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x64, 0x73,
	0x2f, 0x76, 0x33, 0x2f, 0x65, 0x6e, 0x75, 0x6d, 0x73, 0x2f, 0x6f, 0x66, 0x66, 0x6c, 0x69, 0x6e,
	0x65, 0x5f, 0x75, 0x73, 0x65, 0x72, 0x5f, 0x64, 0x61, 0x74, 0x61, 0x5f, 0x6a, 0x6f, 0x62, 0x5f,
	0x66, 0x61, 0x69, 0x6c, 0x75, 0x72, 0x65, 0x5f, 0x72, 0x65, 0x61, 0x73, 0x6f, 0x6e, 0x2e, 0x70,
	0x72, 0x6f, 0x74, 0x6f, 0x1a, 0x40, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2f, 0x61, 0x64, 0x73,
	0x2f, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x64, 0x73, 0x2f, 0x76, 0x33, 0x2f, 0x65, 0x6e,
	0x75, 0x6d, 0x73, 0x2f, 0x6f, 0x66, 0x66, 0x6c, 0x69, 0x6e, 0x65, 0x5f, 0x75, 0x73, 0x65, 0x72,
	0x5f, 0x64, 0x61, 0x74, 0x61, 0x5f, 0x6a, 0x6f, 0x62, 0x5f, 0x73, 0x74, 0x61, 0x74, 0x75, 0x73,
	0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x1a, 0x3e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2f, 0x61,
	0x64, 0x73, 0x2f, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x64, 0x73, 0x2f, 0x76, 0x33, 0x2f,
	0x65, 0x6e, 0x75, 0x6d, 0x73, 0x2f, 0x6f, 0x66, 0x66, 0x6c, 0x69, 0x6e, 0x65, 0x5f, 0x75, 0x73,
	0x65, 0x72, 0x5f, 0x64, 0x61, 0x74, 0x61, 0x5f, 0x6a, 0x6f, 0x62, 0x5f, 0x74, 0x79, 0x70, 0x65,
	0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x1a, 0x1f, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2f, 0x61,
	0x70, 0x69, 0x2f, 0x66, 0x69, 0x65, 0x6c, 0x64, 0x5f, 0x62, 0x65, 0x68, 0x61, 0x76, 0x69, 0x6f,
	0x72, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x1a, 0x19, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2f,
	0x61, 0x70, 0x69, 0x2f, 0x72, 0x65, 0x73, 0x6f, 0x75, 0x72, 0x63, 0x65, 0x2e, 0x70, 0x72, 0x6f,
	0x74, 0x6f, 0x1a, 0x1e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2f, 0x70, 0x72, 0x6f, 0x74, 0x6f,
	0x62, 0x75, 0x66, 0x2f, 0x77, 0x72, 0x61, 0x70, 0x70, 0x65, 0x72, 0x73, 0x2e, 0x70, 0x72, 0x6f,
	0x74, 0x6f, 0x1a, 0x1c, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2f, 0x61, 0x70, 0x69, 0x2f, 0x61,
	0x6e, 0x6e, 0x6f, 0x74, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x73, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f,
	0x22, 0xd0, 0x07, 0x0a, 0x12, 0x4f, 0x66, 0x66, 0x6c, 0x69, 0x6e, 0x65, 0x55, 0x73, 0x65, 0x72,
	0x44, 0x61, 0x74, 0x61, 0x4a, 0x6f, 0x62, 0x12, 0x58, 0x0a, 0x0d, 0x72, 0x65, 0x73, 0x6f, 0x75,
	0x72, 0x63, 0x65, 0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x18, 0x01, 0x20, 0x01, 0x28, 0x09, 0x42, 0x33,
	0xe0, 0x41, 0x05, 0xfa, 0x41, 0x2d, 0x0a, 0x2b, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x64,
	0x73, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x70, 0x69, 0x73, 0x2e, 0x63, 0x6f, 0x6d,
	0x2f, 0x4f, 0x66, 0x66, 0x6c, 0x69, 0x6e, 0x65, 0x55, 0x73, 0x65, 0x72, 0x44, 0x61, 0x74, 0x61,
	0x4a, 0x6f, 0x62, 0x52, 0x0c, 0x72, 0x65, 0x73, 0x6f, 0x75, 0x72, 0x63, 0x65, 0x4e, 0x61, 0x6d,
	0x65, 0x12, 0x30, 0x0a, 0x02, 0x69, 0x64, 0x18, 0x02, 0x20, 0x01, 0x28, 0x0b, 0x32, 0x1b, 0x2e,
	0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x62, 0x75, 0x66, 0x2e,
	0x49, 0x6e, 0x74, 0x36, 0x34, 0x56, 0x61, 0x6c, 0x75, 0x65, 0x42, 0x03, 0xe0, 0x41, 0x03, 0x52,
	0x02, 0x69, 0x64, 0x12, 0x41, 0x0a, 0x0b, 0x65, 0x78, 0x74, 0x65, 0x72, 0x6e, 0x61, 0x6c, 0x5f,
	0x69, 0x64, 0x18, 0x03, 0x20, 0x01, 0x28, 0x0b, 0x32, 0x1b, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c,
	0x65, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x62, 0x75, 0x66, 0x2e, 0x49, 0x6e, 0x74, 0x36, 0x34,
	0x56, 0x61, 0x6c, 0x75, 0x65, 0x42, 0x03, 0xe0, 0x41, 0x03, 0x52, 0x0a, 0x65, 0x78, 0x74, 0x65,
	0x72, 0x6e, 0x61, 0x6c, 0x49, 0x64, 0x12, 0x69, 0x0a, 0x04, 0x74, 0x79, 0x70, 0x65, 0x18, 0x04,
	0x20, 0x01, 0x28, 0x0e, 0x32, 0x50, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2e, 0x61, 0x64,
	0x73, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x64, 0x73, 0x2e, 0x76, 0x33, 0x2e, 0x65,
	0x6e, 0x75, 0x6d, 0x73, 0x2e, 0x4f, 0x66, 0x66, 0x6c, 0x69, 0x6e, 0x65, 0x55, 0x73, 0x65, 0x72,
	0x44, 0x61, 0x74, 0x61, 0x4a, 0x6f, 0x62, 0x54, 0x79, 0x70, 0x65, 0x45, 0x6e, 0x75, 0x6d, 0x2e,
	0x4f, 0x66, 0x66, 0x6c, 0x69, 0x6e, 0x65, 0x55, 0x73, 0x65, 0x72, 0x44, 0x61, 0x74, 0x61, 0x4a,
	0x6f, 0x62, 0x54, 0x79, 0x70, 0x65, 0x42, 0x03, 0xe0, 0x41, 0x03, 0x52, 0x04, 0x74, 0x79, 0x70,
	0x65, 0x12, 0x71, 0x0a, 0x06, 0x73, 0x74, 0x61, 0x74, 0x75, 0x73, 0x18, 0x05, 0x20, 0x01, 0x28,
	0x0e, 0x32, 0x54, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2e, 0x61, 0x64, 0x73, 0x2e, 0x67,
	0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x64, 0x73, 0x2e, 0x76, 0x33, 0x2e, 0x65, 0x6e, 0x75, 0x6d,
	0x73, 0x2e, 0x4f, 0x66, 0x66, 0x6c, 0x69, 0x6e, 0x65, 0x55, 0x73, 0x65, 0x72, 0x44, 0x61, 0x74,
	0x61, 0x4a, 0x6f, 0x62, 0x53, 0x74, 0x61, 0x74, 0x75, 0x73, 0x45, 0x6e, 0x75, 0x6d, 0x2e, 0x4f,
	0x66, 0x66, 0x6c, 0x69, 0x6e, 0x65, 0x55, 0x73, 0x65, 0x72, 0x44, 0x61, 0x74, 0x61, 0x4a, 0x6f,
	0x62, 0x53, 0x74, 0x61, 0x74, 0x75, 0x73, 0x42, 0x03, 0xe0, 0x41, 0x03, 0x52, 0x06, 0x73, 0x74,
	0x61, 0x74, 0x75, 0x73, 0x12, 0x8e, 0x01, 0x0a, 0x0e, 0x66, 0x61, 0x69, 0x6c, 0x75, 0x72, 0x65,
	0x5f, 0x72, 0x65, 0x61, 0x73, 0x6f, 0x6e, 0x18, 0x06, 0x20, 0x01, 0x28, 0x0e, 0x32, 0x62, 0x2e,
	0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2e, 0x61, 0x64, 0x73, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c,
	0x65, 0x61, 0x64, 0x73, 0x2e, 0x76, 0x33, 0x2e, 0x65, 0x6e, 0x75, 0x6d, 0x73, 0x2e, 0x4f, 0x66,
	0x66, 0x6c, 0x69, 0x6e, 0x65, 0x55, 0x73, 0x65, 0x72, 0x44, 0x61, 0x74, 0x61, 0x4a, 0x6f, 0x62,
	0x46, 0x61, 0x69, 0x6c, 0x75, 0x72, 0x65, 0x52, 0x65, 0x61, 0x73, 0x6f, 0x6e, 0x45, 0x6e, 0x75,
	0x6d, 0x2e, 0x4f, 0x66, 0x66, 0x6c, 0x69, 0x6e, 0x65, 0x55, 0x73, 0x65, 0x72, 0x44, 0x61, 0x74,
	0x61, 0x4a, 0x6f, 0x62, 0x46, 0x61, 0x69, 0x6c, 0x75, 0x72, 0x65, 0x52, 0x65, 0x61, 0x73, 0x6f,
	0x6e, 0x42, 0x03, 0xe0, 0x41, 0x03, 0x52, 0x0d, 0x66, 0x61, 0x69, 0x6c, 0x75, 0x72, 0x65, 0x52,
	0x65, 0x61, 0x73, 0x6f, 0x6e, 0x12, 0x8e, 0x01, 0x0a, 0x21, 0x63, 0x75, 0x73, 0x74, 0x6f, 0x6d,
	0x65, 0x72, 0x5f, 0x6d, 0x61, 0x74, 0x63, 0x68, 0x5f, 0x75, 0x73, 0x65, 0x72, 0x5f, 0x6c, 0x69,
	0x73, 0x74, 0x5f, 0x6d, 0x65, 0x74, 0x61, 0x64, 0x61, 0x74, 0x61, 0x18, 0x07, 0x20, 0x01, 0x28,
	0x0b, 0x32, 0x3d, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2e, 0x61, 0x64, 0x73, 0x2e, 0x67,
	0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x64, 0x73, 0x2e, 0x76, 0x33, 0x2e, 0x63, 0x6f, 0x6d, 0x6d,
	0x6f, 0x6e, 0x2e, 0x43, 0x75, 0x73, 0x74, 0x6f, 0x6d, 0x65, 0x72, 0x4d, 0x61, 0x74, 0x63, 0x68,
	0x55, 0x73, 0x65, 0x72, 0x4c, 0x69, 0x73, 0x74, 0x4d, 0x65, 0x74, 0x61, 0x64, 0x61, 0x74, 0x61,
	0x42, 0x03, 0xe0, 0x41, 0x03, 0x48, 0x00, 0x52, 0x1d, 0x63, 0x75, 0x73, 0x74, 0x6f, 0x6d, 0x65,
	0x72, 0x4d, 0x61, 0x74, 0x63, 0x68, 0x55, 0x73, 0x65, 0x72, 0x4c, 0x69, 0x73, 0x74, 0x4d, 0x65,
	0x74, 0x61, 0x64, 0x61, 0x74, 0x61, 0x12, 0x6b, 0x0a, 0x14, 0x73, 0x74, 0x6f, 0x72, 0x65, 0x5f,
	0x73, 0x61, 0x6c, 0x65, 0x73, 0x5f, 0x6d, 0x65, 0x74, 0x61, 0x64, 0x61, 0x74, 0x61, 0x18, 0x08,
	0x20, 0x01, 0x28, 0x0b, 0x32, 0x32, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2e, 0x61, 0x64,
	0x73, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x64, 0x73, 0x2e, 0x76, 0x33, 0x2e, 0x63,
	0x6f, 0x6d, 0x6d, 0x6f, 0x6e, 0x2e, 0x53, 0x74, 0x6f, 0x72, 0x65, 0x53, 0x61, 0x6c, 0x65, 0x73,
	0x4d, 0x65, 0x74, 0x61, 0x64, 0x61, 0x74, 0x61, 0x42, 0x03, 0xe0, 0x41, 0x03, 0x48, 0x00, 0x52,
	0x12, 0x73, 0x74, 0x6f, 0x72, 0x65, 0x53, 0x61, 0x6c, 0x65, 0x73, 0x4d, 0x65, 0x74, 0x61, 0x64,
	0x61, 0x74, 0x61, 0x3a, 0x72, 0xea, 0x41, 0x6f, 0x0a, 0x2b, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65,
	0x61, 0x64, 0x73, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x70, 0x69, 0x73, 0x2e, 0x63,
	0x6f, 0x6d, 0x2f, 0x4f, 0x66, 0x66, 0x6c, 0x69, 0x6e, 0x65, 0x55, 0x73, 0x65, 0x72, 0x44, 0x61,
	0x74, 0x61, 0x4a, 0x6f, 0x62, 0x12, 0x40, 0x63, 0x75, 0x73, 0x74, 0x6f, 0x6d, 0x65, 0x72, 0x73,
	0x2f, 0x7b, 0x63, 0x75, 0x73, 0x74, 0x6f, 0x6d, 0x65, 0x72, 0x7d, 0x2f, 0x6f, 0x66, 0x66, 0x6c,
	0x69, 0x6e, 0x65, 0x55, 0x73, 0x65, 0x72, 0x44, 0x61, 0x74, 0x61, 0x4a, 0x6f, 0x62, 0x73, 0x2f,
	0x7b, 0x6f, 0x66, 0x66, 0x6c, 0x69, 0x6e, 0x65, 0x5f, 0x75, 0x73, 0x65, 0x72, 0x5f, 0x64, 0x61,
	0x74, 0x61, 0x5f, 0x6a, 0x6f, 0x62, 0x7d, 0x42, 0x0a, 0x0a, 0x08, 0x6d, 0x65, 0x74, 0x61, 0x64,
	0x61, 0x74, 0x61, 0x42, 0x84, 0x02, 0x0a, 0x25, 0x63, 0x6f, 0x6d, 0x2e, 0x67, 0x6f, 0x6f, 0x67,
	0x6c, 0x65, 0x2e, 0x61, 0x64, 0x73, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x64, 0x73,
	0x2e, 0x76, 0x33, 0x2e, 0x72, 0x65, 0x73, 0x6f, 0x75, 0x72, 0x63, 0x65, 0x73, 0x42, 0x17, 0x4f,
	0x66, 0x66, 0x6c, 0x69, 0x6e, 0x65, 0x55, 0x73, 0x65, 0x72, 0x44, 0x61, 0x74, 0x61, 0x4a, 0x6f,
	0x62, 0x50, 0x72, 0x6f, 0x74, 0x6f, 0x50, 0x01, 0x5a, 0x4a, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65,
	0x2e, 0x67, 0x6f, 0x6c, 0x61, 0x6e, 0x67, 0x2e, 0x6f, 0x72, 0x67, 0x2f, 0x67, 0x65, 0x6e, 0x70,
	0x72, 0x6f, 0x74, 0x6f, 0x2f, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x70, 0x69, 0x73, 0x2f,
	0x61, 0x64, 0x73, 0x2f, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x64, 0x73, 0x2f, 0x76, 0x33,
	0x2f, 0x72, 0x65, 0x73, 0x6f, 0x75, 0x72, 0x63, 0x65, 0x73, 0x3b, 0x72, 0x65, 0x73, 0x6f, 0x75,
	0x72, 0x63, 0x65, 0x73, 0xa2, 0x02, 0x03, 0x47, 0x41, 0x41, 0xaa, 0x02, 0x21, 0x47, 0x6f, 0x6f,
	0x67, 0x6c, 0x65, 0x2e, 0x41, 0x64, 0x73, 0x2e, 0x47, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x41, 0x64,
	0x73, 0x2e, 0x56, 0x33, 0x2e, 0x52, 0x65, 0x73, 0x6f, 0x75, 0x72, 0x63, 0x65, 0x73, 0xca, 0x02,
	0x21, 0x47, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x5c, 0x41, 0x64, 0x73, 0x5c, 0x47, 0x6f, 0x6f, 0x67,
	0x6c, 0x65, 0x41, 0x64, 0x73, 0x5c, 0x56, 0x33, 0x5c, 0x52, 0x65, 0x73, 0x6f, 0x75, 0x72, 0x63,
	0x65, 0x73, 0xea, 0x02, 0x25, 0x47, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x3a, 0x3a, 0x41, 0x64, 0x73,
	0x3a, 0x3a, 0x47, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x41, 0x64, 0x73, 0x3a, 0x3a, 0x56, 0x33, 0x3a,
	0x3a, 0x52, 0x65, 0x73, 0x6f, 0x75, 0x72, 0x63, 0x65, 0x73, 0x62, 0x06, 0x70, 0x72, 0x6f, 0x74,
	0x6f, 0x33,
}

var (
	file_google_ads_googleads_v3_resources_offline_user_data_job_proto_rawDescOnce sync.Once
	file_google_ads_googleads_v3_resources_offline_user_data_job_proto_rawDescData = file_google_ads_googleads_v3_resources_offline_user_data_job_proto_rawDesc
)

func file_google_ads_googleads_v3_resources_offline_user_data_job_proto_rawDescGZIP() []byte {
	file_google_ads_googleads_v3_resources_offline_user_data_job_proto_rawDescOnce.Do(func() {
		file_google_ads_googleads_v3_resources_offline_user_data_job_proto_rawDescData = protoimpl.X.CompressGZIP(file_google_ads_googleads_v3_resources_offline_user_data_job_proto_rawDescData)
	})
	return file_google_ads_googleads_v3_resources_offline_user_data_job_proto_rawDescData
}

var file_google_ads_googleads_v3_resources_offline_user_data_job_proto_msgTypes = make([]protoimpl.MessageInfo, 1)
var file_google_ads_googleads_v3_resources_offline_user_data_job_proto_goTypes = []interface{}{
	(*OfflineUserDataJob)(nil),                                                     // 0: google.ads.googleads.v3.resources.OfflineUserDataJob
	(*wrapperspb.Int64Value)(nil),                                                  // 1: google.protobuf.Int64Value
	(enums.OfflineUserDataJobTypeEnum_OfflineUserDataJobType)(0),                   // 2: google.ads.googleads.v3.enums.OfflineUserDataJobTypeEnum.OfflineUserDataJobType
	(enums.OfflineUserDataJobStatusEnum_OfflineUserDataJobStatus)(0),               // 3: google.ads.googleads.v3.enums.OfflineUserDataJobStatusEnum.OfflineUserDataJobStatus
	(enums.OfflineUserDataJobFailureReasonEnum_OfflineUserDataJobFailureReason)(0), // 4: google.ads.googleads.v3.enums.OfflineUserDataJobFailureReasonEnum.OfflineUserDataJobFailureReason
	(*common.CustomerMatchUserListMetadata)(nil),                                   // 5: google.ads.googleads.v3.common.CustomerMatchUserListMetadata
	(*common.StoreSalesMetadata)(nil),                                              // 6: google.ads.googleads.v3.common.StoreSalesMetadata
}
var file_google_ads_googleads_v3_resources_offline_user_data_job_proto_depIdxs = []int32{
	1, // 0: google.ads.googleads.v3.resources.OfflineUserDataJob.id:type_name -> google.protobuf.Int64Value
	1, // 1: google.ads.googleads.v3.resources.OfflineUserDataJob.external_id:type_name -> google.protobuf.Int64Value
	2, // 2: google.ads.googleads.v3.resources.OfflineUserDataJob.type:type_name -> google.ads.googleads.v3.enums.OfflineUserDataJobTypeEnum.OfflineUserDataJobType
	3, // 3: google.ads.googleads.v3.resources.OfflineUserDataJob.status:type_name -> google.ads.googleads.v3.enums.OfflineUserDataJobStatusEnum.OfflineUserDataJobStatus
	4, // 4: google.ads.googleads.v3.resources.OfflineUserDataJob.failure_reason:type_name -> google.ads.googleads.v3.enums.OfflineUserDataJobFailureReasonEnum.OfflineUserDataJobFailureReason
	5, // 5: google.ads.googleads.v3.resources.OfflineUserDataJob.customer_match_user_list_metadata:type_name -> google.ads.googleads.v3.common.CustomerMatchUserListMetadata
	6, // 6: google.ads.googleads.v3.resources.OfflineUserDataJob.store_sales_metadata:type_name -> google.ads.googleads.v3.common.StoreSalesMetadata
	7, // [7:7] is the sub-list for method output_type
	7, // [7:7] is the sub-list for method input_type
	7, // [7:7] is the sub-list for extension type_name
	7, // [7:7] is the sub-list for extension extendee
	0, // [0:7] is the sub-list for field type_name
}

func init() { file_google_ads_googleads_v3_resources_offline_user_data_job_proto_init() }
func file_google_ads_googleads_v3_resources_offline_user_data_job_proto_init() {
	if File_google_ads_googleads_v3_resources_offline_user_data_job_proto != nil {
		return
	}
	if !protoimpl.UnsafeEnabled {
		file_google_ads_googleads_v3_resources_offline_user_data_job_proto_msgTypes[0].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*OfflineUserDataJob); i {
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
	file_google_ads_googleads_v3_resources_offline_user_data_job_proto_msgTypes[0].OneofWrappers = []interface{}{
		(*OfflineUserDataJob_CustomerMatchUserListMetadata)(nil),
		(*OfflineUserDataJob_StoreSalesMetadata)(nil),
	}
	type x struct{}
	out := protoimpl.TypeBuilder{
		File: protoimpl.DescBuilder{
			GoPackagePath: reflect.TypeOf(x{}).PkgPath(),
			RawDescriptor: file_google_ads_googleads_v3_resources_offline_user_data_job_proto_rawDesc,
			NumEnums:      0,
			NumMessages:   1,
			NumExtensions: 0,
			NumServices:   0,
		},
		GoTypes:           file_google_ads_googleads_v3_resources_offline_user_data_job_proto_goTypes,
		DependencyIndexes: file_google_ads_googleads_v3_resources_offline_user_data_job_proto_depIdxs,
		MessageInfos:      file_google_ads_googleads_v3_resources_offline_user_data_job_proto_msgTypes,
	}.Build()
	File_google_ads_googleads_v3_resources_offline_user_data_job_proto = out.File
	file_google_ads_googleads_v3_resources_offline_user_data_job_proto_rawDesc = nil
	file_google_ads_googleads_v3_resources_offline_user_data_job_proto_goTypes = nil
	file_google_ads_googleads_v3_resources_offline_user_data_job_proto_depIdxs = nil
}
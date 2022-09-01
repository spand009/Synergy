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
// source: google/ads/googleads/v4/resources/distance_view.proto

package resources

import (
	reflect "reflect"
	sync "sync"

	proto "github.com/golang/protobuf/proto"
	enums "google.golang.org/genproto/googleapis/ads/googleads/v4/enums"
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

// A distance view with metrics aggregated by the user's distance from an
// advertiser's location extensions. Each DistanceBucket includes all
// impressions that fall within its distance and a single impression will
// contribute to the metrics for all DistanceBuckets that include the user's
// distance.
type DistanceView struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	// Output only. The resource name of the distance view.
	// Distance view resource names have the form:
	//
	// `customers/{customer_id}/distanceViews/1~{distance_bucket}`
	ResourceName string `protobuf:"bytes,1,opt,name=resource_name,json=resourceName,proto3" json:"resource_name,omitempty"`
	// Output only. Grouping of user distance from location extensions.
	DistanceBucket enums.DistanceBucketEnum_DistanceBucket `protobuf:"varint,2,opt,name=distance_bucket,json=distanceBucket,proto3,enum=google.ads.googleads.v4.enums.DistanceBucketEnum_DistanceBucket" json:"distance_bucket,omitempty"`
	// Output only. True if the DistanceBucket is using the metric system, false otherwise.
	MetricSystem *wrapperspb.BoolValue `protobuf:"bytes,3,opt,name=metric_system,json=metricSystem,proto3" json:"metric_system,omitempty"`
}

func (x *DistanceView) Reset() {
	*x = DistanceView{}
	if protoimpl.UnsafeEnabled {
		mi := &file_google_ads_googleads_v4_resources_distance_view_proto_msgTypes[0]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *DistanceView) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*DistanceView) ProtoMessage() {}

func (x *DistanceView) ProtoReflect() protoreflect.Message {
	mi := &file_google_ads_googleads_v4_resources_distance_view_proto_msgTypes[0]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use DistanceView.ProtoReflect.Descriptor instead.
func (*DistanceView) Descriptor() ([]byte, []int) {
	return file_google_ads_googleads_v4_resources_distance_view_proto_rawDescGZIP(), []int{0}
}

func (x *DistanceView) GetResourceName() string {
	if x != nil {
		return x.ResourceName
	}
	return ""
}

func (x *DistanceView) GetDistanceBucket() enums.DistanceBucketEnum_DistanceBucket {
	if x != nil {
		return x.DistanceBucket
	}
	return enums.DistanceBucketEnum_UNSPECIFIED
}

func (x *DistanceView) GetMetricSystem() *wrapperspb.BoolValue {
	if x != nil {
		return x.MetricSystem
	}
	return nil
}

var File_google_ads_googleads_v4_resources_distance_view_proto protoreflect.FileDescriptor

var file_google_ads_googleads_v4_resources_distance_view_proto_rawDesc = []byte{
	0x0a, 0x35, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2f, 0x61, 0x64, 0x73, 0x2f, 0x67, 0x6f, 0x6f,
	0x67, 0x6c, 0x65, 0x61, 0x64, 0x73, 0x2f, 0x76, 0x34, 0x2f, 0x72, 0x65, 0x73, 0x6f, 0x75, 0x72,
	0x63, 0x65, 0x73, 0x2f, 0x64, 0x69, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x5f, 0x76, 0x69, 0x65,
	0x77, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x12, 0x21, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2e,
	0x61, 0x64, 0x73, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x64, 0x73, 0x2e, 0x76, 0x34,
	0x2e, 0x72, 0x65, 0x73, 0x6f, 0x75, 0x72, 0x63, 0x65, 0x73, 0x1a, 0x33, 0x67, 0x6f, 0x6f, 0x67,
	0x6c, 0x65, 0x2f, 0x61, 0x64, 0x73, 0x2f, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x64, 0x73,
	0x2f, 0x76, 0x34, 0x2f, 0x65, 0x6e, 0x75, 0x6d, 0x73, 0x2f, 0x64, 0x69, 0x73, 0x74, 0x61, 0x6e,
	0x63, 0x65, 0x5f, 0x62, 0x75, 0x63, 0x6b, 0x65, 0x74, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x1a,
	0x1f, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2f, 0x61, 0x70, 0x69, 0x2f, 0x66, 0x69, 0x65, 0x6c,
	0x64, 0x5f, 0x62, 0x65, 0x68, 0x61, 0x76, 0x69, 0x6f, 0x72, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f,
	0x1a, 0x19, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2f, 0x61, 0x70, 0x69, 0x2f, 0x72, 0x65, 0x73,
	0x6f, 0x75, 0x72, 0x63, 0x65, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x1a, 0x1e, 0x67, 0x6f, 0x6f,
	0x67, 0x6c, 0x65, 0x2f, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x62, 0x75, 0x66, 0x2f, 0x77, 0x72, 0x61,
	0x70, 0x70, 0x65, 0x72, 0x73, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x1a, 0x1c, 0x67, 0x6f, 0x6f,
	0x67, 0x6c, 0x65, 0x2f, 0x61, 0x70, 0x69, 0x2f, 0x61, 0x6e, 0x6e, 0x6f, 0x74, 0x61, 0x74, 0x69,
	0x6f, 0x6e, 0x73, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x22, 0xf8, 0x02, 0x0a, 0x0c, 0x44, 0x69,
	0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x56, 0x69, 0x65, 0x77, 0x12, 0x52, 0x0a, 0x0d, 0x72, 0x65,
	0x73, 0x6f, 0x75, 0x72, 0x63, 0x65, 0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x18, 0x01, 0x20, 0x01, 0x28,
	0x09, 0x42, 0x2d, 0xe0, 0x41, 0x03, 0xfa, 0x41, 0x27, 0x0a, 0x25, 0x67, 0x6f, 0x6f, 0x67, 0x6c,
	0x65, 0x61, 0x64, 0x73, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x70, 0x69, 0x73, 0x2e,
	0x63, 0x6f, 0x6d, 0x2f, 0x44, 0x69, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x56, 0x69, 0x65, 0x77,
	0x52, 0x0c, 0x72, 0x65, 0x73, 0x6f, 0x75, 0x72, 0x63, 0x65, 0x4e, 0x61, 0x6d, 0x65, 0x12, 0x6e,
	0x0a, 0x0f, 0x64, 0x69, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x5f, 0x62, 0x75, 0x63, 0x6b, 0x65,
	0x74, 0x18, 0x02, 0x20, 0x01, 0x28, 0x0e, 0x32, 0x40, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65,
	0x2e, 0x61, 0x64, 0x73, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x64, 0x73, 0x2e, 0x76,
	0x34, 0x2e, 0x65, 0x6e, 0x75, 0x6d, 0x73, 0x2e, 0x44, 0x69, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65,
	0x42, 0x75, 0x63, 0x6b, 0x65, 0x74, 0x45, 0x6e, 0x75, 0x6d, 0x2e, 0x44, 0x69, 0x73, 0x74, 0x61,
	0x6e, 0x63, 0x65, 0x42, 0x75, 0x63, 0x6b, 0x65, 0x74, 0x42, 0x03, 0xe0, 0x41, 0x03, 0x52, 0x0e,
	0x64, 0x69, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x42, 0x75, 0x63, 0x6b, 0x65, 0x74, 0x12, 0x44,
	0x0a, 0x0d, 0x6d, 0x65, 0x74, 0x72, 0x69, 0x63, 0x5f, 0x73, 0x79, 0x73, 0x74, 0x65, 0x6d, 0x18,
	0x03, 0x20, 0x01, 0x28, 0x0b, 0x32, 0x1a, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2e, 0x70,
	0x72, 0x6f, 0x74, 0x6f, 0x62, 0x75, 0x66, 0x2e, 0x42, 0x6f, 0x6f, 0x6c, 0x56, 0x61, 0x6c, 0x75,
	0x65, 0x42, 0x03, 0xe0, 0x41, 0x03, 0x52, 0x0c, 0x6d, 0x65, 0x74, 0x72, 0x69, 0x63, 0x53, 0x79,
	0x73, 0x74, 0x65, 0x6d, 0x3a, 0x5e, 0xea, 0x41, 0x5b, 0x0a, 0x25, 0x67, 0x6f, 0x6f, 0x67, 0x6c,
	0x65, 0x61, 0x64, 0x73, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x70, 0x69, 0x73, 0x2e,
	0x63, 0x6f, 0x6d, 0x2f, 0x44, 0x69, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x56, 0x69, 0x65, 0x77,
	0x12, 0x32, 0x63, 0x75, 0x73, 0x74, 0x6f, 0x6d, 0x65, 0x72, 0x73, 0x2f, 0x7b, 0x63, 0x75, 0x73,
	0x74, 0x6f, 0x6d, 0x65, 0x72, 0x7d, 0x2f, 0x64, 0x69, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x56,
	0x69, 0x65, 0x77, 0x73, 0x2f, 0x7b, 0x64, 0x69, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x5f, 0x76,
	0x69, 0x65, 0x77, 0x7d, 0x42, 0xfe, 0x01, 0x0a, 0x25, 0x63, 0x6f, 0x6d, 0x2e, 0x67, 0x6f, 0x6f,
	0x67, 0x6c, 0x65, 0x2e, 0x61, 0x64, 0x73, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x64,
	0x73, 0x2e, 0x76, 0x34, 0x2e, 0x72, 0x65, 0x73, 0x6f, 0x75, 0x72, 0x63, 0x65, 0x73, 0x42, 0x11,
	0x44, 0x69, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x56, 0x69, 0x65, 0x77, 0x50, 0x72, 0x6f, 0x74,
	0x6f, 0x50, 0x01, 0x5a, 0x4a, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2e, 0x67, 0x6f, 0x6c, 0x61,
	0x6e, 0x67, 0x2e, 0x6f, 0x72, 0x67, 0x2f, 0x67, 0x65, 0x6e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x2f,
	0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x70, 0x69, 0x73, 0x2f, 0x61, 0x64, 0x73, 0x2f, 0x67,
	0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x61, 0x64, 0x73, 0x2f, 0x76, 0x34, 0x2f, 0x72, 0x65, 0x73, 0x6f,
	0x75, 0x72, 0x63, 0x65, 0x73, 0x3b, 0x72, 0x65, 0x73, 0x6f, 0x75, 0x72, 0x63, 0x65, 0x73, 0xa2,
	0x02, 0x03, 0x47, 0x41, 0x41, 0xaa, 0x02, 0x21, 0x47, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2e, 0x41,
	0x64, 0x73, 0x2e, 0x47, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x41, 0x64, 0x73, 0x2e, 0x56, 0x34, 0x2e,
	0x52, 0x65, 0x73, 0x6f, 0x75, 0x72, 0x63, 0x65, 0x73, 0xca, 0x02, 0x21, 0x47, 0x6f, 0x6f, 0x67,
	0x6c, 0x65, 0x5c, 0x41, 0x64, 0x73, 0x5c, 0x47, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x41, 0x64, 0x73,
	0x5c, 0x56, 0x34, 0x5c, 0x52, 0x65, 0x73, 0x6f, 0x75, 0x72, 0x63, 0x65, 0x73, 0xea, 0x02, 0x25,
	0x47, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x3a, 0x3a, 0x41, 0x64, 0x73, 0x3a, 0x3a, 0x47, 0x6f, 0x6f,
	0x67, 0x6c, 0x65, 0x41, 0x64, 0x73, 0x3a, 0x3a, 0x56, 0x34, 0x3a, 0x3a, 0x52, 0x65, 0x73, 0x6f,
	0x75, 0x72, 0x63, 0x65, 0x73, 0x62, 0x06, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x33,
}

var (
	file_google_ads_googleads_v4_resources_distance_view_proto_rawDescOnce sync.Once
	file_google_ads_googleads_v4_resources_distance_view_proto_rawDescData = file_google_ads_googleads_v4_resources_distance_view_proto_rawDesc
)

func file_google_ads_googleads_v4_resources_distance_view_proto_rawDescGZIP() []byte {
	file_google_ads_googleads_v4_resources_distance_view_proto_rawDescOnce.Do(func() {
		file_google_ads_googleads_v4_resources_distance_view_proto_rawDescData = protoimpl.X.CompressGZIP(file_google_ads_googleads_v4_resources_distance_view_proto_rawDescData)
	})
	return file_google_ads_googleads_v4_resources_distance_view_proto_rawDescData
}

var file_google_ads_googleads_v4_resources_distance_view_proto_msgTypes = make([]protoimpl.MessageInfo, 1)
var file_google_ads_googleads_v4_resources_distance_view_proto_goTypes = []interface{}{
	(*DistanceView)(nil),                         // 0: google.ads.googleads.v4.resources.DistanceView
	(enums.DistanceBucketEnum_DistanceBucket)(0), // 1: google.ads.googleads.v4.enums.DistanceBucketEnum.DistanceBucket
	(*wrapperspb.BoolValue)(nil),                 // 2: google.protobuf.BoolValue
}
var file_google_ads_googleads_v4_resources_distance_view_proto_depIdxs = []int32{
	1, // 0: google.ads.googleads.v4.resources.DistanceView.distance_bucket:type_name -> google.ads.googleads.v4.enums.DistanceBucketEnum.DistanceBucket
	2, // 1: google.ads.googleads.v4.resources.DistanceView.metric_system:type_name -> google.protobuf.BoolValue
	2, // [2:2] is the sub-list for method output_type
	2, // [2:2] is the sub-list for method input_type
	2, // [2:2] is the sub-list for extension type_name
	2, // [2:2] is the sub-list for extension extendee
	0, // [0:2] is the sub-list for field type_name
}

func init() { file_google_ads_googleads_v4_resources_distance_view_proto_init() }
func file_google_ads_googleads_v4_resources_distance_view_proto_init() {
	if File_google_ads_googleads_v4_resources_distance_view_proto != nil {
		return
	}
	if !protoimpl.UnsafeEnabled {
		file_google_ads_googleads_v4_resources_distance_view_proto_msgTypes[0].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*DistanceView); i {
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
	type x struct{}
	out := protoimpl.TypeBuilder{
		File: protoimpl.DescBuilder{
			GoPackagePath: reflect.TypeOf(x{}).PkgPath(),
			RawDescriptor: file_google_ads_googleads_v4_resources_distance_view_proto_rawDesc,
			NumEnums:      0,
			NumMessages:   1,
			NumExtensions: 0,
			NumServices:   0,
		},
		GoTypes:           file_google_ads_googleads_v4_resources_distance_view_proto_goTypes,
		DependencyIndexes: file_google_ads_googleads_v4_resources_distance_view_proto_depIdxs,
		MessageInfos:      file_google_ads_googleads_v4_resources_distance_view_proto_msgTypes,
	}.Build()
	File_google_ads_googleads_v4_resources_distance_view_proto = out.File
	file_google_ads_googleads_v4_resources_distance_view_proto_rawDesc = nil
	file_google_ads_googleads_v4_resources_distance_view_proto_goTypes = nil
	file_google_ads_googleads_v4_resources_distance_view_proto_depIdxs = nil
}

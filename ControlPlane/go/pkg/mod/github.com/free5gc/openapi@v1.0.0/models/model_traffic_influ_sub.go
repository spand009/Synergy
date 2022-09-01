/*
 * 3gpp-traffic-influence
 *
 * No description provided (generated by Openapi Generator https://github.com/openapitools/openapi-generator)
 *
 * API version: 1.0.1
 * Generated by: OpenAPI Generator (https://openapi-generator.tech)
 */

package models

type TrafficInfluSub struct {
	// Identifies a service on behalf of which the AF is issuing the request.
	AfServiceId string `json:"afServiceId,omitempty" yaml:"afServiceId" bson:"afServiceId" mapstructure:"AfServiceId"`
	// Identifies an application.
	AfAppId string `json:"afAppId,omitempty" yaml:"afAppId" bson:"afAppId" mapstructure:"AfAppId"`
	// Identifies an NEF Northbound interface transaction, generated by the AF.
	AfTransId string `json:"afTransId,omitempty" yaml:"afTransId" bson:"afTransId" mapstructure:"AfTransId"`
	// Identifies whether an application can be relocated once a location of the application has been selected.
	AppReloInd bool    `json:"appReloInd,omitempty" yaml:"appReloInd" bson:"appReloInd" mapstructure:"AppReloInd"`
	Dnn        string  `json:"dnn,omitempty" yaml:"dnn" bson:"dnn" mapstructure:"Dnn"`
	Snssai     *Snssai `json:"snssai,omitempty" yaml:"snssai" bson:"snssai" mapstructure:"Snssai"`
	// string containing a local identifier followed by \"@\" and a domain identifier. Both the local identifier and the domain identifier shall be encoded as strings that do not contain any \"@\" characters. See Clauses 4.6.2 and 4.6.3 of 3GPP TS 23.682 for more information.
	ExternalGroupId string `json:"externalGroupId,omitempty" yaml:"externalGroupId" bson:"externalGroupId" mapstructure:"ExternalGroupId"`
	// Identifies whether the AF request applies to any UE. This attribute shall set to \"true\" if applicable for any UE, otherwise, set to \"false\".
	AnyUeInd bool `json:"anyUeInd,omitempty" yaml:"anyUeInd" bson:"anyUeInd" mapstructure:"AnyUeInd"`
	// Identifies the requirement to be notified of the event(s).
	SubscribedEvents []SubscribedEvent `json:"subscribedEvents,omitempty" yaml:"subscribedEvents" bson:"subscribedEvents" mapstructure:"SubscribedEvents"`
	Gpsi             string            `json:"gpsi,omitempty" yaml:"gpsi" bson:"gpsi" mapstructure:"Gpsi"`
	// string identifying a Ipv4 address formatted in the \"dotted decimal\" notation as defined in IETF RFC 1166.
	Ipv4Addr string `json:"ipv4Addr,omitempty" yaml:"ipv4Addr" bson:"ipv4Addr" mapstructure:"Ipv4Addr"`
	// string identifying a Ipv6 address formatted according to clause 4 in IETF RFC 5952. The mixed Ipv4 Ipv6 notation according to clause 5 of IETF RFC 5952 shall not be used.
	Ipv6Addr    string         `json:"ipv6Addr,omitempty" yaml:"ipv6Addr" bson:"ipv6Addr" mapstructure:"Ipv6Addr"`
	MacAddr     string         `json:"macAddr,omitempty" yaml:"macAddr" bson:"macAddr" mapstructure:"MacAddr"`
	DnaiChgType DnaiChangeType `json:"dnaiChgType,omitempty" yaml:"dnaiChgType" bson:"dnaiChgType" mapstructure:"DnaiChgType"`
	// string formatted according to IETF RFC 3986 identifying a referenced resource.
	NotificationDestination string `json:"notificationDestination,omitempty" yaml:"notificationDestination" bson:"notificationDestination" mapstructure:"NotificationDestination"`
	// Set to true by the SCS/AS to request the NEF to send a test notification as defined in subclause 5.2.5.3. Set to false or omitted otherwise.
	RequestTestNotification bool                `json:"requestTestNotification,omitempty" yaml:"requestTestNotification" bson:"requestTestNotification" mapstructure:"RequestTestNotification"`
	WebsockNotifConfig      *WebsockNotifConfig `json:"websockNotifConfig,omitempty" yaml:"websockNotifConfig" bson:"websockNotifConfig" mapstructure:"WebsockNotifConfig"`
	// string formatted according to IETF RFC 3986 identifying a referenced resource.
	Self string `json:"self,omitempty" yaml:"self" bson:"self" mapstructure:"Self"`
	// Identifies IP packet filters.
	TrafficFilters []FlowInfo `json:"trafficFilters,omitempty" yaml:"trafficFilters" bson:"trafficFilters" mapstructure:"TrafficFilters"`
	// Identifies Ethernet packet filters.
	EthTrafficFilters []EthFlowDescription `json:"ethTrafficFilters,omitempty" yaml:"ethTrafficFilters" bson:"ethTrafficFilters" mapstructure:"EthTrafficFilters"`
	// Identifies the N6 traffic routing requirement.
	TrafficRoutes  []RouteToLocation  `json:"trafficRoutes,omitempty" yaml:"trafficRoutes" bson:"trafficRoutes" mapstructure:"TrafficRoutes"`
	TempValidities []TemporalValidity `json:"tempValidities,omitempty" yaml:"tempValidities" bson:"tempValidities" mapstructure:"TempValidities"`
	// Identifies a geographic zone that the AF request applies only to the traffic of UE(s) located in this specific zone.
	ValidGeoZoneIds []string `json:"validGeoZoneIds,omitempty" yaml:"validGeoZoneIds" bson:"validGeoZoneIds" mapstructure:"ValidGeoZoneIds"`
	SuppFeat        string   `json:"suppFeat,omitempty" yaml:"suppFeat" bson:"suppFeat" mapstructure:"SuppFeat"`
}

package ngapType

// Need to import "github.com/free5gc/aper" if it uses "aper"

/* Sequence of = 35, FULL Name = struct DRBsToQosFlowsMappingList */
/* DRBsToQosFlowsMappingItem */
type DRBsToQosFlowsMappingList struct {
	List []DRBsToQosFlowsMappingItem `aper:"valueExt,sizeLB:1,sizeUB:32"`
}

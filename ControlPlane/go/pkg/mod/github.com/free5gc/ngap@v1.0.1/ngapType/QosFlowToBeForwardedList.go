package ngapType

// Need to import "github.com/free5gc/aper" if it uses "aper"

/* Sequence of = 35, FULL Name = struct QosFlowToBeForwardedList */
/* QosFlowToBeForwardedItem */
type QosFlowToBeForwardedList struct {
	List []QosFlowToBeForwardedItem `aper:"valueExt,sizeLB:1,sizeUB:64"`
}

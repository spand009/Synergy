package ngapType

// Need to import "github.com/free5gc/aper" if it uses "aper"

/* Sequence of = 35, FULL Name = struct PDUSessionResourceSetupListHOReq */
/* PDUSessionResourceSetupItemHOReq */
type PDUSessionResourceSetupListHOReq struct {
	List []PDUSessionResourceSetupItemHOReq `aper:"valueExt,sizeLB:1,sizeUB:256"`
}

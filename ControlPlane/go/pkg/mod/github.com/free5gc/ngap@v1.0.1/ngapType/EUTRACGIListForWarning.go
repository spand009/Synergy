package ngapType

// Need to import "github.com/free5gc/aper" if it uses "aper"

/* Sequence of = 35, FULL Name = struct EUTRA_CGIListForWarning */
/* EUTRACGI */
type EUTRACGIListForWarning struct {
	List []EUTRACGI `aper:"valueExt,sizeLB:1,sizeUB:65535"`
}

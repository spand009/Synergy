package ngapType

// Need to import "github.com/free5gc/aper" if it uses "aper"

/* Sequence of = 35, FULL Name = struct TAIListForPaging */
/* TAIListForPagingItem */
type TAIListForPaging struct {
	List []TAIListForPagingItem `aper:"valueExt,sizeLB:1,sizeUB:16"`
}

package ngapType

// Need to import "github.com/free5gc/aper" if it uses "aper"

/* Sequence of = 35, FULL Name = struct SupportedTAList */
/* SupportedTAItem */
type SupportedTAList struct {
	List []SupportedTAItem `aper:"valueExt,sizeLB:1,sizeUB:256"`
}

package ngapType

import "github.com/free5gc/aper"

// Need to import "github.com/free5gc/aper" if it uses "aper"

const (
	IMSVoiceSupportIndicatorPresentSupported    aper.Enumerated = 0
	IMSVoiceSupportIndicatorPresentNotSupported aper.Enumerated = 1
)

type IMSVoiceSupportIndicator struct {
	Value aper.Enumerated `aper:"valueExt,valueLB:0,valueUB:1"`
}

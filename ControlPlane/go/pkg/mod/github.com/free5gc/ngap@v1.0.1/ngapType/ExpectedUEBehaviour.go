package ngapType

// Need to import "github.com/free5gc/aper" if it uses "aper"

type ExpectedUEBehaviour struct {
	ExpectedUEActivityBehaviour *ExpectedUEActivityBehaviour                         `aper:"valueExt,optional"`
	ExpectedHOInterval          *ExpectedHOInterval                                  `aper:"optional"`
	ExpectedUEMobility          *ExpectedUEMobility                                  `aper:"optional"`
	ExpectedUEMovingTrajectory  *ExpectedUEMovingTrajectory                          `aper:"optional"`
	IEExtensions                *ProtocolExtensionContainerExpectedUEBehaviourExtIEs `aper:"optional"`
}

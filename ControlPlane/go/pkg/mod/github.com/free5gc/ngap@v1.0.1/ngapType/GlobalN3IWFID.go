package ngapType

// Need to import "github.com/free5gc/aper" if it uses "aper"

type GlobalN3IWFID struct {
	PLMNIdentity PLMNIdentity
	N3IWFID      N3IWFID                                        `aper:"valueLB:0,valueUB:1"`
	IEExtensions *ProtocolExtensionContainerGlobalN3IWFIDExtIEs `aper:"optional"`
}

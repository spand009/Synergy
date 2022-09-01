package ngapConvert

import (
	"github.com/free5gc/ngap/logger"
	"github.com/free5gc/ngap/ngapType"
	"github.com/free5gc/openapi/models"
	"encoding/hex"
	"strings"
)

func PlmnIdToModels(ngapPlmnId ngapType.PLMNIdentity) (modelsPlmnid models.PlmnId) {
	value := ngapPlmnId.Value
	hexString := strings.Split(hex.EncodeToString(value), "")
	modelsPlmnid.Mcc = hexString[1] + hexString[0] + hexString[3]
	if hexString[2] == "f" {
		modelsPlmnid.Mnc = hexString[5] + hexString[4]
	} else {
		modelsPlmnid.Mnc = hexString[2] + hexString[5] + hexString[4]
	}
	return
}
func PlmnIdToNgap(modelsPlmnid models.PlmnId) ngapType.PLMNIdentity {
	var hexString string
	mcc := strings.Split(modelsPlmnid.Mcc, "")
	mnc := strings.Split(modelsPlmnid.Mnc, "")
	if len(modelsPlmnid.Mnc) == 2 {
		hexString = mcc[1] + mcc[0] + "f" + mcc[2] + mnc[1] + mnc[0]
	} else {
		hexString = mcc[1] + mcc[0] + mnc[0] + mcc[2] + mnc[2] + mnc[1]
	}

	var ngapPlmnId ngapType.PLMNIdentity
	if plmnId, err := hex.DecodeString(hexString); err != nil {
		logger.NgapLog.Warnf("Decode plmn failed: %+v", err)
	} else {
		ngapPlmnId.Value = plmnId
	}
	return ngapPlmnId
}

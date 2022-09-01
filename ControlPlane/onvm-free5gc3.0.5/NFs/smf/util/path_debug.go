//+build debug

package util

import (
	"github.com/free5gc/path_util"
)

var (
	SmfLogPath           = path_util.Free5gcPath("free5gc/smfsslkey.log")
	SmfPemPath           = path_util.Free5gcPath("free5gc/support/TLS/_debug.pem")
	SmfKeyPath           = path_util.Free5gcPath("free5gc/support/TLS/_debug.key")
	DefaultSmfConfigPath = path_util.Free5gcPath("free5gc/config/smfcfg.yaml")
)

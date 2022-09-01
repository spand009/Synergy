package logger

import (
	"os"
	"time"

	formatter "github.com/antonfisher/nested-logrus-formatter"
	"github.com/sirupsen/logrus"

	"github.com/free5gc/logger_conf"
	"github.com/free5gc/logger_util"
)

var log *logrus.Logger

// Util3GPPLog : Log entry of util_3gpp
var Util3GPPLog *logrus.Entry

func init() {
	log = logrus.New()
	log.SetReportCaller(false)

	log.Formatter = &formatter.Formatter{
		TimestampFormat: time.RFC3339,
		TrimMessages:    true,
		NoFieldsSpace:   true,
		HideKeys:        true,
		FieldsOrder:     []string{"component", "category"},
	}

	free5gcLogHook, err := logger_util.NewFileHook(logger_conf.Free5gcLogFile, os.O_CREATE|os.O_APPEND|os.O_RDWR, 0666)
	if err == nil {
		log.Hooks.Add(free5gcLogHook)
	}

	selfLogHook, err := logger_util.NewFileHook(logger_conf.LibLogDir+"util_3gpp.log",
		os.O_CREATE|os.O_APPEND|os.O_RDWR, 0666)
	if err == nil {
		log.Hooks.Add(selfLogHook)
	}

	Util3GPPLog = log.WithFields(logrus.Fields{"component": "LIB", "category": "3GPP"})
}

// SetLogLevel : set the log level (panic|fatal|error|warn|info|debug|trace)
func SetLogLevel(level logrus.Level) {
	Util3GPPLog.Infoln("set log level :", level)
	log.SetLevel(level)
}

// SetReportCaller : Set whether shows the filePath and functionName on loggers
func SetReportCaller(bool bool) {
	Util3GPPLog.Infoln("set report call :", bool)
	log.SetReportCaller(bool)
}

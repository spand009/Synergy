package version_test

import (
	"testing"

	"github.com/stretchr/testify/assert"

	"github.com/free5gc/logger_util/version"
)

func TestVersion(t *testing.T) {
	assert.Equal(t, "2020-03-31-01", version.GetVersion())
}

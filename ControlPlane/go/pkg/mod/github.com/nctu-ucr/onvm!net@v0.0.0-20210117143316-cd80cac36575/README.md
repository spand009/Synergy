# onvmNet

### 1. Set env
The `$ONVM_HOME`, `$RTE_SDK`, `RTE_TARGET` must be setted.

### 2. Using Makefile to build
include onvmNet.mk in your makefile.

```Makefile
include $path_to_onvmNet/onvmNet.mk

all:
  CGO_LDFLAGS_ALLOW="-Wl,(--whole-archive|--no-whole-archive)" go build
```

### 3. Change onvmConfig.json in conn.c

Change `cmd2[]` in `conn.c` to assign your config file for openNetVM's nf config.

### 4. Create IP ID Mapping

Create a yaml file for IP and ServiceID mapping file.

Create file named `ipid.yaml` under the command you exec or set the env of IPIDConfig to the config path.


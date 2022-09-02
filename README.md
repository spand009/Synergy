# Synergy: A SmartNIC Accelerated 5G Dataplane and Monitor for Mobility Prediction

Paper to be attached when public.

The installations for the control plane and UPF appears below, respectively.

## Install Control Plane
```
# Automatically setup the Synergy experiment


read node_type
node_name=$(hostname)

homedir=$(eval echo "~$USER")
cd $homedir

case $node_type in
    "UERAN") # echo 'UERAN'
    echo "Download test-packet repository for MoonGen"
    git clone https://github.com/nctu-ucr/test-packet.git
    # run utlity script to modify gtp_packet.py
    echo "Modify pcap file path"
    sed -i 's#\/home\/chu52016#'$homedir'#g' $homedir/test-packet/gtp_packet.py
    echo "ATTENTION: the mac needs to be configured manually"

    # Generate GTP with test environment
    sudo apt install -y python3
    sudo apt install -y python3-pip
    sudo pip3 install scapy

    echo "Download MoonGen"
    git clone https://github.com/emmericp/MoonGen.git
    sudo apt-get install -y libtbb2 libnuma-dev python gcc make
    sudo apt-get install -y build-essential cmake linux-headers-`uname -r` pciutils libnuma-dev
    
    echo "Build MoonGen..."
    cd $homedir/MoonGen
    ./build.sh
    
    # Set up hugepages
    sudo ./setup-hugetlbfs.sh

    echo "ATTENTION: Interfaces need to shut down before bound to DPDK"
    echo "Please run `sudo ifconfig IF_NAME down`, then run `sudo ./bind-interfaces.sh`"
    ;;


    "5GC") # echo '5GC'
    echo "========= Download nctu-ucr/onvm-upf ========="
    git clone https://github.com/nctu-ucr/onvm-upf.git

    echo "========= Download nctu-ucr/logger_util ========="
    git clone https://github.com/nctu-ucr/logger_util.git

    echo "========= Download nctu-ucr/test-script3.0.5 ========="
    git clone https://github.com/nctu-ucr/test-script3.0.5.git

    echo "========= Download nctu-ucr/onvm-pfcp3.0.5 ========="
    git clone https://github.com/nctu-ucr/onvm-pfcp3.0.5.git

    echo "========= Download nctu-ucr/onvm-free5gc3.0.5 ========="
    git clone https://github.com/nctu-ucr/onvm-free5gc3.0.5.git

    echo "========= Check whether GO is installed ========="
    if command -v go >/dev/null 2>&1; then 
        echo 'exists go, remove the existing version and install Go 1.14.4:'
        # this assumes your current version of Go is in the default location
        sudo rm -rf /usr/local/go
        wget https://dl.google.com/go/go1.14.4.linux-amd64.tar.gz
        sudo tar -C /usr/local -zxvf go1.14.4.linux-amd64.tar.gz
    else 
        echo 'no exists go'
        wget https://dl.google.com/go/go1.14.4.linux-amd64.tar.gz
        sudo tar -C /usr/local -zxvf go1.14.4.linux-amd64.tar.gz
        mkdir -p ~/go/{bin,pkg,src}
        # The following assume that your shell is bash
        echo 'export GOPATH=$HOME/go' >> ~/.bashrc
        echo 'export GOROOT=/usr/local/go' >> ~/.bashrc
        echo 'export PATH=$PATH:$GOPATH/bin:$GOROOT/bin' >> ~/.bashrc
        echo 'export GO111MODULE=auto' >> ~/.bashrc
        source ~/.bashrc
    fi

    echo "========= Install control-plane supporting packages ========="
    sudo apt -y update
    sudo apt -y install mongodb wget git
    sudo systemctl start mongodb

    echo "========= Install user-plane supporting packages ========="
    sudo apt -y update
    sudo apt -y install git gcc g++ cmake autoconf libtool pkg-config libmnl-dev libyaml-dev
    go get -u github.com/sirupsen/logrus

    echo "========= Build onvm-upf ========="
    sudo apt-get install -y build-essential linux-headers-$(uname -r) git bc
    sudo apt-get install -y python3
    sudo apt-get install -y libnuma-devs
    
    cd $homedir/onvm-upf
    git checkout chu-upf
    git submodule sync
    git submodule update --init
    echo export ONVM_HOME=$(pwd) >> ~/.bashrc
    cd dpdk && echo export RTE_SDK=$(pwd) >> ~/.bashrc
    echo export RTE_TARGET=x86_64-native-linuxapp-gcc  >> ~/.bashrc
    echo export ONVM_NUM_HUGEPAGES=1024 >> ~/.bashrc
    source ~/.bashrc
    sudo sh -c "echo 0 > /proc/sys/kernel/randomize_va_space"
    cd ../scripts
    ./install.sh
    cd ../onvm
    make
    cd ../5gc/upf_c_complete
    make
    cd ../upf_u_complete
    make
    
    echo "========= Build onvm-free5GC3.0.5 ========="
    cd $homedir/onvm-free5gc3.0.5
    git submodule update --init
    echo "modify go.mod in each NFs"
    declare -a NFs=("amf" "ausf" "pcf" "udm" "udr" "smf" "nrf" "nssf")
    for nf in ${NFs[@]}
    do
        sed -i '$a\replace github.com/free5gc/pfcp => '$homedir'/onvm-pfcp3.0.5/' $homedir/onvm-free5gc3.0.5/NFs/$nf/go.mod
        sed -i '$a\replace github.com/free5gc/logger_util => '$homedir'/logger_util/' $homedir/onvm-free5gc3.0.5/NFs/$nf/go.mod
    done

    echo "Download go module in onvm-pfcp3.0.5"
    cd $homedir/onvm-pfcp3.0.5
    go mod download
    echo "Go to onvmNet repository"
    cd $homedir'/go/pkg/mod/github.com/nctu-ucr/onvmNet v0.0.0-20210117143316-cd80cac36575/'
    sudo chmod +w ./*
    cp ./ipid.yaml $homedir/onvm-free5gc3.0.5
    cp ./onvmConfig.json $homedir/
    echo "Modify conn.go"
    sed -i 's#\/root#'$homedir'#g' conn.go
    echo "Modify ipid.yaml"
    sed -i 's#ID:\ 2#ID:\ 4#g' $homedir/onvm-free5gc3.0.5/ipid.yaml
    sed -i 's#ID:\ 1#ID:\ 2#g' $homedir/onvm-free5gc3.0.5/ipid.yaml
    sed -i 's#ID:\ 4#ID:\ 1#g' $homedir/onvm-free5gc3.0.5/ipid.yaml
    echo "Modify conn.c"
    sed -i 's#\/root\/onvmNet#'$homedir'#g' conn.c

    echo "Build smf"
    make smf
    echo "Build amf"
    make amf
    echo "Build nssf"
    make nssf
    echo "Build pcf"
    make pcf
    echo "Build nrf"
    make nrf
    echo "Build ausf"
    make ausf
    echo "Build udm"
    make udm
    echo "Build udr"
    make udr
    ;;


    "DN") # echo 'DN'
    echo "Download ONVM-UPF for DN usage"
    sudo apt-get install -y build-essential linux-headers-$(uname -r) git bc
    sudo apt-get install -y python3
    sudo apt-get install -y libnuma-dev
    sudo apt-get update
    git clone https://github.com/nctu-ucr/onvm-upf.git
    cd onvm-upf
    git submodule sync
    git submodule update --init
    echo export ONVM_HOME=$(pwd) >> ~/.bashrc
    cd dpdk && echo export RTE_SDK=$(pwd) >> ~/.bashrc
    echo export RTE_TARGET=x86_64-native-linuxapp-gcc  >> ~/.bashrc
    echo export ONVM_NUM_HUGEPAGES=1024 >> ~/.bashrc
    source ~/.bashrc
    sudo sh -c "echo 0 > /proc/sys/kernel/randomize_va_space"

    echo "Install DPDK libraries"
    cd ../scripts
    ./install.sh

    echo "Build ONVM Manager"
    cd ../onvm
    make

    echo "Build basic monitor"
    cd ../examples/basic_monitor/
    make

    echo "ATTENTION: Interfaces need to shut down before bound to DPDK"
    echo "Please run `sudo ifconfig IF_NAME down`, then bind the interfaces manually"
    ;;


    *) echo 'Configuration is terminated. Please select one of UERAN | 5GC | DN'
    ;;
esac
exit 0

```

## Install Data Plane

```
# Make sure you set the device PCIe address based on your installation.

dpkg -l | grep nfp;
nfp-temp;
modinfo nfp;
rmmod nfp;
modprobe nfp nfp_dev_cpp=1 nfp_pf_netdev=0;
nfp-hwinfo;
nfp-flash -w /opt/netronome/flash/flash-nic.bin;
nfp-flash -w /opt/netronome/flash/flash-one.bin;

systemctl start nfp-sdk6-rte
systemctl status nfp-sdk6-rte

num_vfs=10
curr_vfs="$(cat /sys/bus/pci/devices/0000\:03\:00.0/sriov_numvfs)"
echo $curr_vfs

#check if they number of VF is greater than 0
if [ ${curr_vfs} -gt 0 ]
then
    echo 0 > /sys/bus/pci/devices/0000\:03\:00.0/sriov_numvfs
    echo $1 > /sys/bus/pci/devices/0000\:03\:00.0/sriov_numvfs
else
    echo $1 > /sys/bus/pci/devices/0000\:03\:00.0/sriov_numvfs
fi
echo "The number of VFs now are "
cat /sys/bus/pci/devices/0000\:03\:00.0/sriov_numvfs

cd SmartNIC
make clean
make run

# Start the thrift API
cd ..
python ThriftAPI/5G.py
```

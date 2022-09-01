#include <errno.h>
#include <getopt.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>
#include <unistd.h>

#include "onvm_nflib.h"
#include "onvm_pkt_helper.h"

#define NF_TAG "upf_c"

#include "upf_init.h"
#include "utlt_debug.h"
#include "utlt_network.h"
#include "upf_context.h"
#include "n4_onvm_pfcp_path.h"

#include "pfcp_path.h"


static Status parseArgs(int argc, char *argv[]);
static Status checkPermission();

int main(int argc, char *argv[]) {
    Status status, returnStatus = STATUS_OK;

    int arg_offset = 0;
    struct onvm_nf_local_ctx *nf_local_ctx;
    struct onvm_nf_function_table *nf_function_table;

    nf_local_ctx = onvm_nflib_init_nf_local_ctx();
    onvm_nflib_start_signal_handler(nf_local_ctx, NULL);

    nf_function_table = onvm_nflib_init_nf_function_table();
    nf_function_table->pkt_handler = packet_handler;
    nf_function_table->msg_handler = msg_handler;

    if ((arg_offset = onvm_nflib_init(argc, argv, NF_TAG, nf_local_ctx, nf_function_table)) < 0) {
        onvm_nflib_stop(nf_local_ctx);
        if (arg_offset == ONVM_SIGNAL_TERMINATION) {
            printf("Exiting due to user termination\n");
            return STATUS_ERROR;
        } else {
            rte_exit(EXIT_FAILURE, "Failed ONVM init\n");
        }
    }

    OnvmSetNfContext(nf_local_ctx);

    argc -= arg_offset;
    argv += arg_offset;

    UTLT_Assert(parseArgs(argc, argv) == STATUS_OK, return STATUS_ERROR, 
                "Error parsing args");

    if (checkPermission() != STATUS_OK) {
        return STATUS_ERROR;
    }

    status = UpfInit();
    UTLT_Assert(status == STATUS_OK, returnStatus = STATUS_ERROR,
                "UPF failed to initialize");

    onvm_nflib_run(nf_local_ctx);

    onvm_nflib_stop(nf_local_ctx);

    status = UpfTerm();
    UTLT_Assert(status == STATUS_OK, returnStatus = STATUS_ERROR,
                "UPF terminate error");
    return returnStatus;
}

static Status parseArgs(int argc, char *argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "f:h")) != -1) {
        switch (opt) {
            case 'f':
                UpfSetConfigPath(optarg);
                break;

            case 'h':
                printf("Usage: %s [-f CONFIG_PATH]", argv[0]);
                exit(0);
            
            case '?':
                UTLT_Error("Illigal option: %c", optopt); 
                return STATUS_ERROR;
        }
    }

    return STATUS_OK;
}

static Status checkPermission() {
    if (geteuid() != 0) {
        UTLT_Error("Please run UPF as root in order to enable route management "
                   "and communication with gtp5g kernel module.");
        return STATUS_ERROR;
    }
    return STATUS_OK;
}

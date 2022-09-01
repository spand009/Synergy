#include <stdio.h>
#include <string.h>
#include "_cgo_export.h"

#define NF_TAG "go-nf"
#define SERVICE_ID_DIGIT 10
#define LOCAL_EXPERIMENTAL_ETHER 0x88B5

static uint16_t packet_size = 64;
static uint8_t d_addr_bytes[RTE_ETHER_ADDR_LEN];

//typedef int GoInt;
//extern int Handler(struct rte_mbuf*, struct onvm_pkt_meta*, struct onvm_nf_local_ctx*);

int onvm_init(struct onvm_nf_local_ctx **nf_local_ctx) {
    int arg_offset;
    struct onvm_nf_function_table *nf_function_table;

    *nf_local_ctx = onvm_nflib_init_nf_local_ctx();
    onvm_nflib_start_signal_handler(*nf_local_ctx, NULL);

    nf_function_table = onvm_nflib_init_nf_function_table();
    nf_function_table->pkt_handler = &Handler;


#if 0
    char cmd0[] = "./go.sh";
    char cmd1[] = "-F";
    char cmd2[] = "/root/onvmNet/onvmConfig.json";
    char * cmd[] = {cmd0, cmd1, cmd2, NULL};
    if ((arg_offset = onvm_nflib_init(3, cmd, NF_TAG, *nf_local_ctx, nf_function_table)) < 0) {
#else
    char cmd0[] = "SMF";
    char cmd1[] = "-l";
    char cmd2[] = "0";
    char cmd3[] = "-n";
    char cmd4[] = "3";
    char cmd5[] = "--proc-type=secondary";
    char cmd6[] = "--";
    char cmd7[] = "-r";
    char cmd8[] = "3";
    char cmd9[] = "--";
    char * cmd[] = {cmd0, cmd1, cmd2, cmd3, cmd4, cmd5, cmd6, cmd7, cmd8, cmd9, NULL};
    if ((arg_offset = onvm_nflib_init(10, cmd, NF_TAG, *nf_local_ctx, nf_function_table)) < 0) {
#endif



    //char * cmd[2] = {"./go.sh", service_id_str};
    //char cmd0[] = "./go.sh";
    //char cmd1[] = "-F";
    //char cmd2[] = "/root/PANDA_5G/HOME/onvmConfig.json";
	//"/root/onvmNet/onvmConfig.json";
    //char * cmd[] = {cmd0, cmd1, cmd2, NULL};
    //if ((arg_offset = onvm_nflib_init(3, cmd, NF_TAG, *nf_local_ctx, nf_function_table)) < 0) {
        onvm_nflib_stop(*nf_local_ctx);
        if (arg_offset == ONVM_SIGNAL_TERMINATION) {
            printf("Exiting due to user termination\n");
            return 0;
        } else {
            rte_exit(EXIT_FAILURE, "Failed ONVM init\n");
        }
    }

    return 0;
}

void onvm_send_pkt(char * buff, int service_id, struct onvm_nf_local_ctx * ctx,int buff_length) {
    uint32_t i;
    uint32_t pkts_generated;
    struct rte_mempool *pktmbuf_pool;
  	
	pkts_generated = 0;
    pktmbuf_pool = rte_mempool_lookup(PKTMBUF_POOL_NAME);
    if (pktmbuf_pool == NULL) {
        onvm_nflib_stop(ctx);
        rte_exit(EXIT_FAILURE, "Cannot find mbuf pool!\n");
    }

    struct onvm_pkt_meta *pmeta;
    struct rte_ether_hdr *ehdr;

    struct rte_mbuf *pkt = rte_pktmbuf_alloc(pktmbuf_pool);
    if (pkt == NULL) {
        printf("Failed to allocate packets\n");
        return;
    }

    /*set up ether header and set new packet size*/
    ehdr = (struct rte_ether_hdr *)rte_pktmbuf_append(pkt, buff_length);

    /*using manager mac addr for source
     *using input string for dest addr
     */

    if (onvm_get_macaddr(0, &ehdr->s_addr) == -1) {
        onvm_get_fake_macaddr(&ehdr->s_addr);
    }

    for (i = 0; i < RTE_ETHER_ADDR_LEN; ++i) {
        ehdr->d_addr.addr_bytes[i] = d_addr_bytes[i];
    }

    ehdr->ether_type = LOCAL_EXPERIMENTAL_ETHER;

    // fill out the meta data of the packet
    pmeta = onvm_get_pkt_meta(pkt);
    pmeta->destination = service_id;
    pmeta->action = ONVM_NF_ACTION_TONF;
    //pmeta->flags = ONVM_SET_BIT(0, SPEED_TESTER_BIT);
    //pkt->hash.rss = i;
    pkt->hash.rss = 0;
    pkt->port = 0;
    pkt->data_len=buff_length;//???
    /* Copy the packet into the rte_mbuf data section */
    rte_memcpy(rte_pktmbuf_mtod(pkt, char *), buff, buff_length);
    pkts_generated = 1;
//    FILE *fp;
//	fp = fopen("/root/chuTest/dump.txt", "a");
	//fprintf(fp, "\n-----------------------\n fprintf... %d<->%d\n", count, port);
//	rte_pktmbuf_dump(fp, pkt, 1000);
//	fclose(fp);


    // send out the generated packet
    onvm_nflib_return_pkt(ctx->nf, pkt);

    /* Exit if packets were unexpectedly not created */
    if (pkts_generated == 0) {
        onvm_nflib_stop(ctx);
        rte_exit(EXIT_FAILURE, "Failed to create packets\n");
    }

}


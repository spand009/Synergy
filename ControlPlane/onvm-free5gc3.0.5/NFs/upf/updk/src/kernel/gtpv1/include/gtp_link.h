#ifndef __GTP_LINK_H__
#define __GTP_LINK_H__

#include <netinet/in.h>
#include <libmnl/libmnl.h>

#include "utlt_lib.h"
#include "utlt_debug.h"
#include "utlt_list.h"
#include "utlt_network.h"

#define GTP_V1_PORT 2152
#define GTP_PRIME_PORT 3386

typedef struct {
    struct mnl_socket *nl;
    int32_t genl_id;
    uint32_t ifidx;
} NetlinkInfo;

typedef struct {
    ListHead node;
    char ip[INET6_ADDRSTRLEN], ifname[MAX_IFNAME_STRLEN];
    Sock *sock;
} Gtpv1TunDevNode;

Status GtpLinkCreate(Gtpv1TunDevNode *node);
Status GtpLinkFree(Gtpv1TunDevNode *node);

Status NetlinkSockOpen(NetlinkInfo *info, const char *ifname, const char *family_name);
Status NetlinkSockClose(NetlinkInfo *info);

Status Gtpv1DevPoolInit();
Status Gtpv1DevPoolFinal();
Gtpv1TunDevNode *Gtpv1DevListAdd(ListHead *list, const char *ip, const char *ifname);
Status Gtpv1DevListFree(ListHead *list);

#endif /* __GTP_LINK_H__ */

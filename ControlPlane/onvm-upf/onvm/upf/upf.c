#include "upf_context.h"

#define __STDC_FORMAT_MACROS
#include <inttypes.h>

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <rte_cycles.h>
#include <rte_hash.h>
#include <rte_jhash.h>
#include <rte_lcore.h>
#include <rte_malloc.h>
#include <rte_memory.h>
#include <rte_memzone.h>

#ifdef RTE_MACHINE_CPUFLAG_SSE4_2
#include <rte_hash_crc.h>
#define DEFAULT_HASH_FUNC rte_hash_crc
#else
#include <rte_jhash.h>
#define DEFAULT_HASH_FUNC rte_jhash
#endif

#define SEID_TO_HASH_KEY(x) (DEFAULT_HASH_FUNC(&x, sizeof(uint64_t), 0))
#define TEID_TO_HASH_KEY(x) (DEFAULT_HASH_FUNC(&x, sizeof(uint32_t), 0))
#define UEIP_TO_HASH_KEY(x) (DEFAULT_HASH_FUNC(&x, sizeof(uint32_t), 0))

#define NO_FLAGS 0
#define MAX_NUM_OF_USERS 1024
#define MZ_TEID_TO_UPF_SESSION_MAP_INFO  "MProc_TeidToUpfSessionMap_info"
#define MZ_UE_IP_TO_UPF_SESSION_MAP_INFO "MProc_UeIpToUpfSessionMap_info"
#define MZ_PFCP_SESSION_TABLE_INFO "MProc_pfcp_session_table_info"

typedef struct {
  struct rte_hash* hash;
  char* data;
  int cnt;
  int entry_size;
} TeidToUpfSessionMap;

typedef struct {
  struct rte_hash* hash;
  char* data;
  int cnt;
  int entry_size;
} UeIpToUpfSessionMap;

typedef struct {
  struct rte_hash* hash;
  char* data;
  int cnt;
  int entry_size;
} UpfSessionPool;

TeidToUpfSessionMap *teid_upf_session_map = NULL;
TeidToUpfSessionMap **teid_upf_session_map_p = NULL;

UeIpToUpfSessionMap *ueip_upf_session_map = NULL;

UpfSessionPool *upf_session_table = NULL;

TeidToUpfSessionMap *teid_upf_session_map_create(void);

TeidToUpfSessionMap *teid_upf_session_map_create(void) {
    struct rte_hash *hash = NULL;
    struct rte_hash_parameters *hash_params;
    TeidToUpfSessionMap *ft;

    hash_params = (struct rte_hash_parameters *)rte_malloc(
            NULL, sizeof(struct rte_hash_parameters), 0);
    if (!hash_params) {
        return NULL;
    }

    char *name = rte_malloc(NULL, 64, 0);
    hash_params->entries = MAX_NUM_OF_USERS;
    hash_params->key_len = sizeof(uint32_t);
    hash_params->hash_func = rte_jhash;
    hash_params->hash_func_init_val = 0;
    hash_params->name = name;
    hash_params->socket_id = rte_socket_id();

    snprintf(name, 64, "teid_upf_session_map_%d-%" PRIu64, rte_lcore_id(),
            rte_get_tsc_cycles());

    hash = rte_hash_create(hash_params);
    if (!hash) {
        return NULL;
    }

    ft = (TeidToUpfSessionMap *)rte_calloc("teid_upf_session_map", 1,
            sizeof(TeidToUpfSessionMap), 0);
    if (!ft) {
        rte_hash_free(hash);
        return NULL;
    }

    ft->hash = hash;
    ft->cnt = MAX_NUM_OF_USERS;
    ft->entry_size = sizeof(int);
    /* Create data array for storing values */
    ft->data = rte_calloc("teid_upf_session_map_entry", MAX_NUM_OF_USERS, sizeof(int), 0);
    if (!ft->data) {
        rte_hash_free(hash);
        rte_free(ft);
        return NULL;
    }
    return ft;
}

UeIpToUpfSessionMap *ueip_upf_session_map_create(void);

UeIpToUpfSessionMap *ueip_upf_session_map_create(void) {
    struct rte_hash *hash = NULL;
    struct rte_hash_parameters *hash_params;
    UeIpToUpfSessionMap *ft;

    hash_params = (struct rte_hash_parameters *)rte_malloc(
            NULL, sizeof(struct rte_hash_parameters), 0);
    if (!hash_params) {
        return NULL;
    }

    char *name = rte_malloc(NULL, 64, 0);
    hash_params->entries = MAX_NUM_OF_USERS;
    hash_params->key_len = sizeof(uint32_t);
    hash_params->hash_func = rte_jhash;
    hash_params->hash_func_init_val = 0;
    hash_params->name = name;
    hash_params->socket_id = rte_socket_id();

    snprintf(name, 64, "ueip_upf_session_map_%d-%" PRIu64, rte_lcore_id(),
            rte_get_tsc_cycles());

    hash = rte_hash_create(hash_params);
    if (!hash) {
        return NULL;
    }

    ft = (UeIpToUpfSessionMap *)rte_calloc("ueip_upf_session_map", 1,
            sizeof(UeIpToUpfSessionMap), 0);
    if (!ft) {
        rte_hash_free(hash);
        return NULL;
    }

    ft->hash = hash;
    ft->cnt = MAX_NUM_OF_USERS;
    ft->entry_size = sizeof(int);
    /* Create data array for storing values */
    ft->data = rte_calloc("ueip_upf_session_map_entry", MAX_NUM_OF_USERS, sizeof(int), 0);
    if (!ft->data) {
        rte_hash_free(hash);
        rte_free(ft);
        return NULL;
    }
    return ft;
}

UpfSessionPool *upf_session_table_create(int cnt, int entry_size);

UpfSessionPool *upf_session_table_create(int cnt, int entry_size) {
    struct rte_hash *hash = NULL;
    struct rte_hash_parameters *hash_params;
    UpfSessionPool *ft;

    hash_params = (struct rte_hash_parameters *)rte_malloc(
            NULL, sizeof(struct rte_hash_parameters), 0);
    if (!hash_params) {
        return NULL;
    }

    char *name = rte_malloc(NULL, 64, 0);
    hash_params->entries = cnt;
    hash_params->key_len = sizeof(uint64_t);
    hash_params->hash_func = rte_jhash;
    hash_params->hash_func_init_val = 0;
    hash_params->name = name;
    hash_params->socket_id = rte_socket_id();

    snprintf(name, 64, "upf_session_%d-%" PRIu64, rte_lcore_id(),
            rte_get_tsc_cycles());

    if (rte_eal_process_type() == RTE_PROC_PRIMARY) {
        hash = rte_hash_create(hash_params);
    }

    if (!hash) {
        return NULL;
    }
    ft = (UpfSessionPool *)rte_calloc("upf_session_table", 1,
            sizeof(UpfSessionPool), 0);
    if (!ft) {
        rte_hash_free(hash);
        return NULL;
    }

    ft->hash = hash;
    ft->cnt = cnt;
    ft->entry_size = entry_size;
    /* Create data array for storing values */
    ft->data = rte_calloc("upf_session_table_entry", cnt, entry_size, 0);
    if (!ft->data) {
        rte_hash_free(hash);
        rte_free(ft);
        return NULL;
    }
    return ft;
}

int TeidToUpfSessionMapInit(void) {
    if (rte_eal_process_type() == RTE_PROC_PRIMARY) {
        const struct rte_memzone *mz_ftp;

        teid_upf_session_map = teid_upf_session_map_create();

        if (teid_upf_session_map == NULL) {
            rte_exit(EXIT_FAILURE, "Unable to teid_upf_session_map\n");
        }
        mz_ftp =
            rte_memzone_reserve(MZ_TEID_TO_UPF_SESSION_MAP_INFO, sizeof(TeidToUpfSessionMap *),
                    rte_socket_id(), NO_FLAGS);
        if (mz_ftp == NULL) {
            rte_exit(EXIT_FAILURE,
                    "Cannot reserve memory zone for flow table pointer\n");
        }
        memset(mz_ftp->addr, 0, sizeof(UpfSessionPool *));
        teid_upf_session_map_p = mz_ftp->addr;
        *teid_upf_session_map_p = teid_upf_session_map;
    } else {
        printf("%s called\n", __func__);
        const struct rte_memzone *mz_ftp;
        TeidToUpfSessionMap **ftp;

        mz_ftp = rte_memzone_lookup(MZ_TEID_TO_UPF_SESSION_MAP_INFO);
        if (mz_ftp == NULL) rte_exit(EXIT_FAILURE, "Cannot get table pointer\n");
        ftp = mz_ftp->addr;
        teid_upf_session_map = *ftp;

        if (teid_upf_session_map == NULL) {
            printf("session table NULL\n");
        }
        if (teid_upf_session_map != NULL && teid_upf_session_map->hash == NULL) {
            printf("session hash table NULL\n");
        }
    }
    return 0;
}

int UeIpToUpfSessionMapInit(void) {
    if (rte_eal_process_type() == RTE_PROC_PRIMARY) {
        const struct rte_memzone *mz_ftp;
        UeIpToUpfSessionMap **ueip_upf_session_map_p = NULL;

        ueip_upf_session_map = ueip_upf_session_map_create();

        if (ueip_upf_session_map == NULL) {
            rte_exit(EXIT_FAILURE, "Unable to ueip_upf_session_map\n");
        }
        mz_ftp =
            rte_memzone_reserve(MZ_UE_IP_TO_UPF_SESSION_MAP_INFO, sizeof(TeidToUpfSessionMap *),
                    rte_socket_id(), NO_FLAGS);
        if (mz_ftp == NULL) {
            rte_exit(EXIT_FAILURE,
                    "Cannot reserve memory zone for flow table pointer\n");
        }
        memset(mz_ftp->addr, 0, sizeof(UeIpToUpfSessionMap *));
        ueip_upf_session_map_p = mz_ftp->addr;
        *ueip_upf_session_map_p = ueip_upf_session_map;
    } else {
        printf("%s called\n", __func__);
        const struct rte_memzone *mz_ftp;
        UeIpToUpfSessionMap **ftp;

        mz_ftp = rte_memzone_lookup(MZ_UE_IP_TO_UPF_SESSION_MAP_INFO);
        if (mz_ftp == NULL) rte_exit(EXIT_FAILURE, "Cannot get table pointer\n");
        ftp = mz_ftp->addr;
        ueip_upf_session_map = *ftp;

        if (ueip_upf_session_map == NULL) {
            printf("session table NULL\n");
        }
        if (ueip_upf_session_map != NULL && ueip_upf_session_map->hash == NULL) {
            printf("session hash table NULL\n");
        }
    }
    return 0;
}

int UpfSessionPoolInit(void) {
    if (rte_eal_process_type() == RTE_PROC_PRIMARY) {
        const struct rte_memzone *mz_ftp;
        UpfSessionPool **sdn_ft_p = NULL;

        upf_session_table =
            upf_session_table_create(MAX_NUM_OF_USERS, sizeof(UpfSession));

        if (upf_session_table == NULL) {
            rte_exit(EXIT_FAILURE, "Unable to create flow table\n");
        }
        mz_ftp =
            rte_memzone_reserve(MZ_PFCP_SESSION_TABLE_INFO, sizeof(UpfSessionPool *),
                    rte_socket_id(), NO_FLAGS);
        if (mz_ftp == NULL) {
            rte_exit(EXIT_FAILURE,
                    "Cannot reserve memory zone for flow table pointer\n");
        }
        memset(mz_ftp->addr, 0, sizeof(UpfSessionPool *));
        sdn_ft_p = mz_ftp->addr;
        *sdn_ft_p = upf_session_table;
    } else {
        printf("%s called\n", __func__);
        const struct rte_memzone *mz_ftp;
        UpfSessionPool **ftp;

        mz_ftp = rte_memzone_lookup(MZ_PFCP_SESSION_TABLE_INFO);
        if (mz_ftp == NULL) rte_exit(EXIT_FAILURE, "Cannot get table pointer\n");
        ftp = mz_ftp->addr;
        upf_session_table = *ftp;

        if (upf_session_table == NULL) {
            printf("session table NULL\n");
        }
        if (upf_session_table != NULL && upf_session_table->hash == NULL) {
            printf("session hash table NULL\n");
        }
    }
    return 0;
}

void UpfSessionFree(UpfSession *session) {
    int32_t status = rte_hash_del_key_with_hash(upf_session_table->hash,
                                                (const void *)&session->upfSeid,
                                                session->hashKey);
    if (status < 0) {
        UTLT_Error("Error deleting a session");
    }
}

UpfSession *UpfGetSessionByIndex(int32_t idx) {
    return (UpfSession *) &upf_session_table
        ->data[idx * upf_session_table->entry_size];
}

UpfSession *UpfSessionFindBySeid(uint64_t seid) {
    uint32_t cal_hash = SEID_TO_HASH_KEY(seid);
    int32_t status = rte_hash_lookup_with_hash(upf_session_table->hash,
                                               (const void *)&seid, cal_hash);
    if (status < 0) {
        return NULL;
    }
    return UpfGetSessionByIndex(status);
}

UpfSession *UpfSessionAlloc(const uint64_t seid) {
    uint32_t cal_hash = SEID_TO_HASH_KEY(seid);
    int32_t status = rte_hash_add_key_with_hash(upf_session_table->hash,
                                                (const void *) &seid,
                                                cal_hash);
    if (status < 0) {
        return NULL;
    }
    UpfSession *session;
    session = UpfGetSessionByIndex(status);
    session->index = status;
    session->hashKey = cal_hash;
    session->upfSeid = seid;
    return session;
}

UpfSession *UpfSessionFindByUeIP(uint32_t ue_ip) {
    uint32_t cal_hash = UEIP_TO_HASH_KEY(ue_ip);
    int32_t status = rte_hash_lookup_with_hash(ueip_upf_session_map->hash,
                                               (const void *)&ue_ip,
                                               cal_hash);
    if (status < 0) {
        UTLT_Info("Not Found UpfSessionFindByUeIP[%u]", ue_ip);
        return NULL;
    }
    int idx = status * ueip_upf_session_map->entry_size;
    return UpfGetSessionByIndex(idx);
}

Status InsertUEIPtoSessionMap(const uint32_t ue_ip, UpfSession *session) {
    uint32_t cal_hash = UEIP_TO_HASH_KEY(ue_ip);
    int32_t status = rte_hash_lookup_with_hash(ueip_upf_session_map->hash,
                                               (const void *)&ue_ip,
                                               cal_hash);
    if (status >= 0) {
        UTLT_Error("UE IP Mapping already exists");
        return STATUS_ERROR;
    }
    status = rte_hash_add_key_with_hash_data(ueip_upf_session_map->hash,
                                             (const void *) &ue_ip,
                                             cal_hash,
                                             &session->index);
    return status == 0? STATUS_OK : STATUS_ERROR;
}

UpfSession *UpfSessionFindByTeid(uint32_t teid) {
    uint32_t cal_hash = TEID_TO_HASH_KEY(teid);
    int32_t status = rte_hash_lookup_with_hash(teid_upf_session_map->hash,
                                               (const void *)&teid,
                                               cal_hash);
    if (status < 0) {
        UTLT_Info("Not Found InsertTEIDtoSessionMap[%u]", teid);
        return NULL;
    }
    int idx = status * teid_upf_session_map->entry_size;
    return UpfGetSessionByIndex(idx);
}

Status InsertTEIDtoSessionMap(const uint32_t teid, UpfSession *session) {
    uint32_t cal_hash = TEID_TO_HASH_KEY(teid);
    int32_t status = rte_hash_lookup_with_hash(teid_upf_session_map->hash,
                                               (const void *)&teid,
                                               cal_hash);
    if (status >= 0) {
        return STATUS_ERROR;
    }
    status = rte_hash_add_key_with_hash_data(teid_upf_session_map->hash,
                                             (const void *) &teid,
                                             cal_hash,
                                             &session->index);
    return status == 0? STATUS_OK : STATUS_ERROR;
}

void UeIpToUpfSessionMapFree(const uint32_t ueip) {
    uint32_t cal_hash = TEID_TO_HASH_KEY(ueip);
    int32_t status = rte_hash_del_key_with_hash(ueip_upf_session_map->hash,
                                                (const void *)&ueip,
                                                cal_hash);
    if (status < 0) {
        UTLT_Error("Error deleting a UeIpToUpfSessionMapFree");
    }
}

void TeidToUpfSessionMapFree(const uint32_t teid) {
    uint32_t cal_hash = TEID_TO_HASH_KEY(teid);
    int32_t status = rte_hash_del_key_with_hash(teid_upf_session_map->hash,
                                                (const void *)&teid,
                                                cal_hash);
    if (status < 0) {
        UTLT_Error("Error deleting a TeidToUpfSessionMapFree");
    }
}

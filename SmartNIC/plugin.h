#include <nfp/mem_atomic.h>
#include <nfp_override.h>
#include <std/hash.h>
#include <nfp/me.h>
#define BUCKET_SIZE 1
#define EVICTION_BUCKET_SIZE 8
#define Test 1
#define Hotspot 1
#define LRU 1

#define x1 1                  //2^0
#define x2 x1, x1             //2^1
#define x4 x2, x2             //2^2
#define x8 x4, x4             //2^3
#define x16 x8, x8            //2^4
#define x32 x16, x16          //2^5
#define x64 x32, x32          //2^6
#define x128 x64, x64         //2^7
#define x256 x128, x128       //2^8
#define x512 x256, x256       //2^9
#define x1024 x512, x512      //2^10
#define x2048 x1024, x1024    //2^11
#define x4096 x2048, x2048    //2^12
#define x8192 x4096, x4096    //2^13
#define x16384 x8192, x8192   //2^14
#define x32768 x16384, x16384 //2^15
#define x655356 x32768, x32768 //2^16

#define STATE_TABLE_SIZE 0x7FFFF
#define EVICTION_BUFFER_SIZE STATE_TABLE_SIZE
#define RING_BUCKET_SIZE 0xFF
#define RING_TABLE_SIZE 0xFFF

#define TRACK_RING_BUFFER_EVICTION 1

#define MASK STATE_TABLE_SIZE
#define SEM_POOL_MASK 0xFFF

//#define HAS_EB 1
//#define HAS_FP 1
//#define Primary_LFU 1 //Default is LRU
#define EB_LFU 1      //Default is LRU

volatile __emem __export uint32_t global_semaphores[(STATE_TABLE_SIZE  & SEM_POOL_MASK) + 1] = {x4096};//{x32768};//{x4096};
volatile __emem __export uint32_t ring_buffer_sem[RING_TABLE_SIZE + 1] = {x4096};

void semaphore_down(volatile __declspec(mem addr40) void * addr) {
        unsigned int addr_hi, addr_lo;
        __declspec(read_write_reg) int xfer;
        SIGNAL_PAIR my_signal_pair;
        addr_hi = ((unsigned long long int)addr >> 8) & 0xff000000;
        addr_lo = (unsigned long long int)addr & 0xffffffff;
        do {
                xfer = 1;
                __asm {
            mem[test_subsat, xfer, addr_hi, <<8, addr_lo, 1],\
                sig_done[my_signal_pair];
            ctx_arb[my_signal_pair]
        }
            sleep(500);
        } while (xfer == 0);
}
void semaphore_up(volatile __declspec(mem addr40) void * addr) {
        unsigned int addr_hi, addr_lo;
        __declspec(read_write_reg) int xfer;
        addr_hi = ((unsigned long long int)addr >> 8) & 0xff000000;
        addr_lo = (unsigned long long int)addr & 0xffffffff;
    __asm {
        mem[incr, --, addr_hi, <<8, addr_lo, 1];
    }
}

typedef struct bucket_entry_info {
    uint32_t hit_count;
    uint32_t insertion_ts;
    uint64_t latest_ts;


} bucket_entry_info;

typedef struct bucket_entry {
    uint32_t key[4]; /* ip1, ip2, ports */
    bucket_entry_info bucket_entry_info_value;
}bucket_entry;

typedef struct bucket_list {
    struct bucket_entry entry[BUCKET_SIZE];
}bucket_list;

typedef struct eviction_list {
    struct bucket_entry entry[EVICTION_BUCKET_SIZE];
}eviction_list;

typedef struct ring_list {
    struct bucket_entry entry[RING_BUCKET_SIZE + 1];
}ring_list;

typedef struct ring_meta {
    uint32_t write_pointer;
    uint32_t read_pointer;
    uint32_t full;
    uint32_t tmp;
} ring_meta;

__shared __export __addr40 __emem bucket_list state_hashtable[STATE_TABLE_SIZE + 1];

#ifdef HAS_EB
__shared __export __addr40 __emem eviction_list eviction_buffer[EVICTION_BUFFER_SIZE + 1];
#endif

__shared __export __addr40 __emem ring_list ring_buffer[RING_TABLE_SIZE + 1];
__shared __export __addr40 __emem ring_meta ring[RING_TABLE_SIZE + 1];

__shared __export __addr40 __emem uint32_t write_overflow;

#ifdef TRACK_RING_BUFFER_EVICTION
__shared __export __addr40 __emem uint32_t hit;
__shared __export __addr40 __emem uint32_t eb_hit;
__shared __export __addr40 __emem uint32_t miss;
#define ring_buffer_eviction_rate_size 200
__shared __export __addr40 __emem uint32_t ring_buffer_evictions;
__shared __export __addr40 __emem uint32_t ring_buffer_final_count;
__shared __export __addr40 __emem uint64_t ring_buffer_evictions_start_ts;
__shared __export __addr40 __emem uint32_t first_packet;
__shared __export __addr40 __emem uint32_t ring_buffer_eviction_rate[ring_buffer_eviction_rate_size];
#endif

#ifdef HAS_FP
#define N_ME 12
#define N_ISL 5
#define N_TH 8
#define BASE_ISL 32
#define ISL_STRIDE (N_ME) * (N_TH)
#define RING_TABLE_SIZE_FP (ISL_STRIDE) * (N_ISL)//Number of ring buffer in the fast path
//#define FP_WHOLE 10
//#define FP_TH    2
#define RING_BUCKET_SIZE_FP 0xFFF

//The fast path is only intended for flow keys as it will only store a single packet
typedef struct bucket_entry_fp {
    uint32_t key[4]; /* ip1, ip2, ports protocol type*/
}bucket_entry_fp;

typedef struct ring_list_fp {
    struct bucket_entry_fp entry[RING_BUCKET_SIZE_FP + 1];
}ring_list_fp;

typedef struct ring_meta_fp {
    uint32_t write_pointer;
    uint32_t read_pointer;
    uint32_t full;
    uint32_t tmp;
} ring_meta_fp;

__shared __export __addr40 __emem uint32_t write_overflow_fp;

__declspec(ctm) uint32_t packet_counter = 0; //This is thread local
__declspec(ctm) uint32_t packet_counter_by_32 = 0;
__declspec(ctm) uint32_t bit_index = 0;
__declspec(ctm) uint32_t to_sample = 0;

//Import from the python code
__declspec(ctm) uint32_t sampling_bitvec_size = 100;
__declspec(ctm) uint32_t sampling_vector[4]   = { 4214017623,525517578,912322208,268435456 };

__declspec(ctm) uint32_t indirection[5][12]={{0,4,40,44,80,84,120,124,152,156,184,188},
{8,12,48,52,88,92,128,132,160,164,192,196},
{16,20,56,60,96,100,136,140,168,172,200,204},
{24,28,64,68,104,108,144,148,176,180,208,212},
{32,36,72,76,112,116,0,0,0,0,0,0}};
__shared __export __addr40 __emem ring_list_fp ring_buffer_fp[216]; 
__shared __export __addr40 __emem ring_meta_fp ring_fp[216];
#endif


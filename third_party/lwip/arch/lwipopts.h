#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

/* Operating System mode: 0 for NO_SYS (baremetal polling), 1 for OS */
#define NO_SYS                          1
#define MEM_ALIGNMENT                   4

#define MEM_SIZE                        (4 * 1024)
#define MEMP_NUM_PBUF                   8
#define MEMP_NUM_TCP_PCB                4
#define MEMP_NUM_TCP_PCB_LISTEN         2
#define MEMP_NUM_TCP_SEG                8
#define MEMP_NUM_SYS_TIMEOUT            5

#define PBUF_POOL_SIZE                  8
#define PBUF_POOL_BUFSIZE               512

#define LWIP_ARP                        1
#define LWIP_ETHERNET                   1
#define LWIP_RAW                        0
#define LWIP_IP                         1
#define LWIP_TCP                        1
#define LWIP_UDP                        1
#define LWIP_DHCP                       1
#define LWIP_DNS                        1

#define TCP_MSS                         536
#define TCP_WND                         (2 * TCP_MSS)
#define TCP_SND_BUF                     (2 * TCP_MSS)

#define CHECKSUM_GEN_IP                 1
#define CHECKSUM_GEN_UDP                1
#define CHECKSUM_GEN_TCP                1
#define CHECKSUM_CHECK_IP               1
#define CHECKSUM_CHECK_UDP              1
#define CHECKSUM_CHECK_TCP              1

#endif /* __LWIPOPTS_H__ */

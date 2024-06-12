/**
 * @file lwipopts.h
 * @author Ambroz Bizjak <ambrop7@gmail.com>
 * 
 * @section LICENSE
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the author nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef LWIP_CUSTOM_LWIPOPTS_H
#define LWIP_CUSTOM_LWIPOPTS_H

// Platform specific locking
#define SYS_LIGHTWEIGHT_PROT 0
#define NO_SYS 1

// Memory options
#define MEM_ALIGNMENT 4U
#define MEM_LIBC_MALLOC 1
#define MEMP_MEM_MALLOC 1

// Internal Memory Pool Sizes
#define MEMP_NUM_PBUF 1024
// #define MEMP_NUM_UDP_PCB 1024
#define MEMP_NUM_TCP_PCB 4096
#define MEMP_NUM_TCP_PCB_LISTEN 16
#define MEMP_NUM_TCP_SEG 8192
#define PBUF_POOL_SIZE 32

// ARP options
#define LWIP_ARP 1
#define ARP_QUEUEING 0

// IPv6 options
#define LWIP_IPV6 1
#define LWIP_IPV6_MLD 0
#define LWIP_IPV6_AUTOCONFIG 0
#ifdef __LP64__
#define IPV6_FRAG_COPYHEADER 1
#endif

// ICMP options
#define LWIP_ICMP 1

// RAW options
#define LWIP_RAW 0

// DHCP options
#define LWIP_DHCP 0

// AUTOIP options
#define LWIP_AUTOIP 0

// SNMP options
#define LWIP_SNMP 0

// IGMP options
#define LWIP_IGMP 0

// DNS options
#define LWIP_DNS 0

// UDP options
#define LWIP_UDP 0
#define LWIP_UDPLITE 0

// TCP options
#define LWIP_TCP 1
#define TCP_MSS 8191
#define TCP_WND (8 * TCP_MSS)
#define TCP_SND_BUF (8 * TCP_MSS)
#define TCP_SND_QUEUELEN ((128 * (TCP_SND_BUF) + (TCP_MSS - 1))/(TCP_MSS))

// Sequential layer options
#define LWIP_NETCONN 0

// Socket options
#define LWIP_SOCKET 0

// PPP options
#define PPP_SUPPORT 0

// Checksum options
#define CHECKSUM_CHECK_IP 0
#define CHECKSUM_CHECK_UDP 0
#define CHECKSUM_CHECK_TCP 0
#define CHECKSUM_CHECK_ICMP 0
#define CHECKSUM_CHECK_ICMP6 0
#define LWIP_CHECKSUM_ON_COPY 1


#define LWIP_TIMERS 1

#define IP_FORWARD 0
#define LWIP_CALLBACK_API 1
#define LWIP_NETIF_API 0
#define LWIP_NETIF_LOOPBACK 0
#define LWIP_HAVE_LOOPIF 0
#define LWIP_HAVE_SLIPIF 0

#define LWIP_PERF 0
#define LWIP_DONT_PROVIDE_BYTEORDER_FUNCTIONS

/*
#define LWIP_DEBUG 1
#define IP_DEBUG LWIP_DBG_ON
#define NETIF_DEBUG LWIP_DBG_ON
#define TCP_DEBUG LWIP_DBG_ON
#define TCP_INPUT_DEBUG LWIP_DBG_ON
#define TCP_OUTPUT_DEBUG LWIP_DBG_ON
*/

#endif

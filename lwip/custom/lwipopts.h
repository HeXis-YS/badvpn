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

// Infrastructure
// NO_SYS
#define NO_SYS 1
// Timers
#define LWIP_TIMERS 0
// Heap and memory pools
#define MEM_LIBC_MALLOC 1
#define MEMP_MEM_MALLOC 1
#define MEM_ALIGNMENT 4U
#define MEMP_OVERFLOW_CHECK 0
#define MEMP_SANITY_CHECK 0
// Internal memory pools
#define MEMP_NUM_PBUF 1024
#define MEMP_NUM_TCP_PCB 4096
#define MEMP_NUM_TCP_PCB_LISTEN 16
#define MEMP_NUM_TCP_SEG 8192
// Checksum
#define CHECKSUM_CHECK_IP 0
#define CHECKSUM_CHECK_TCP 0
#define CHECKSUM_CHECK_ICMP6 0
#define LWIP_CHECKSUM_ON_COPY 1


// IPv4
#define LWIP_IPV4 1
#define IP_FORWARD 0
#define IP_REASSEMBLY 0
#define IP_FRAG 0
// ARP
#define LWIP_ARP 0
// ICMP
#define LWIP_ICMP 0
// DHCP
#define LWIP_DHCP 0
// AUTOIP
#define LWIP_AUTOIP 0
// IGMP
#define LWIP_IGMP 0


// IPv6
#define LWIP_IPV6 1
#define LWIP_IPV6_AUTOCONFIG 0
#define LWIP_IPV6_FRAG 0
#define LWIP_IPV6_REASS 0
// ICMP6
#define LWIP_ICMP6 1
// Multicast listener discovery
#define LWIP_IPV6_MLD 0
// DHCPv6
#define LWIP_IPV6_DHCP6 0


// Callback-style APIs
#define LWIP_CALLBACK_API 1
// RAW
#define LWIP_RAW 0
// DNS
#define LWIP_DNS 0
// TCP
#define LWIP_TCP 1
#define TCP_MSS 8191
#define TCP_WND (8 * TCP_MSS)
#define TCP_SND_BUF (8 * TCP_MSS)
#define TCP_SND_QUEUELEN ((128 * (TCP_SND_BUF) + (TCP_MSS - 1))/(TCP_MSS))
// UDP
#define LWIP_UDP 0


// Thread-safe APIs
// Netconn
#define LWIP_NETCONN 0
// Sockets
#define LWIP_SOCKET 0


// PBUF
#define PBUF_POOL_SIZE 32


// NETIF
#define LWIP_NETIF_API 0
// Loopback interface
#define LWIP_HAVE_LOOPIF 0
#define LWIP_NETIF_LOOPBACK 0


// Debugging
// #define LWIP_DEBUG 1
// Assertion handling
#define LWIP_NOASSERT
// Performance
#define LWIP_PERF 0
// Statistics
#define LWIP_STATS 0
// Debug messages
// #define IP_DEBUG LWIP_DBG_ON
// #define NETIF_DEBUG LWIP_DBG_ON
// #define TCP_DEBUG LWIP_DBG_ON
// #define TCP_INPUT_DEBUG LWIP_DBG_ON
// #define TCP_OUTPUT_DEBUG LWIP_DBG_ON


// Platform specific locking
#define SYS_LIGHTWEIGHT_PROT 0
//
#define LWIP_DONT_PROVIDE_BYTEORDER_FUNCTIONS
// SNMP
#define LWIP_SNMP 0
// PPP
#define PPP_SUPPORT 0
//
#define LWIP_HAVE_SLIPIF 0

#endif

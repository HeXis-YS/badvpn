# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
#
LOCAL_PATH := $(call my-dir)
ROOT_PATH := $(LOCAL_PATH)

########################################################
## tun2socks
########################################################

include $(CLEAR_VARS)

LOCAL_CFLAGS := -std=gnu99
LOCAL_CFLAGS += -DBADVPN_THREAD_SAFE=0 -DBADVPN_LINUX -DBADVPN_BREACTOR_BADVPN -D_GNU_SOURCE
LOCAL_CFLAGS += -DBADVPN_USE_SIGNALFD -DBADVPN_USE_EPOLL
LOCAL_CFLAGS += -DBADVPN_LITTLE_ENDIAN
LOCAL_CFLAGS += -DNDEBUG -DANDROID
LOCAL_CFLAGS += -I

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/badvpn \
	$(LOCAL_PATH)/badvpn/lwip/custom \
	$(LOCAL_PATH)/badvpn/lwip/src/include \
	$(LOCAL_PATH)/badvpn/lwip/src/include/ipv4 \
	$(LOCAL_PATH)/badvpn/lwip/src/include/ipv6 \
	$(LOCAL_PATH)/libancillary

LOCAL_SRC_FILES := \
	badvpn/base/BLog.c \
	badvpn/base/BLog_syslog.c \
	badvpn/base/BPending.c \
	badvpn/flow/BufferWriter.c \
	badvpn/flow/PacketBuffer.c \
	badvpn/flow/PacketPassConnector.c \
	badvpn/flow/PacketPassFairQueue.c \
	badvpn/flow/PacketPassInterface.c \
	badvpn/flow/PacketProtoDecoder.c \
	badvpn/flow/PacketProtoEncoder.c \
	badvpn/flow/PacketProtoFlow.c \
	badvpn/flow/PacketRecvInterface.c \
	badvpn/flow/PacketStreamSender.c \
	badvpn/flow/SinglePacketBuffer.c \
	badvpn/flow/StreamPassInterface.c \
	badvpn/flow/StreamRecvInterface.c \
	badvpn/flowextra/PacketPassInactivityMonitor.c \
	badvpn/lwip/custom/sys.c \
	badvpn/lwip/src/core/def.c \
	badvpn/lwip/src/core/inet_chksum.c \
	badvpn/lwip/src/core/init.c \
	badvpn/lwip/src/core/ip.c \
	badvpn/lwip/src/core/ipv4/icmp.c \
	badvpn/lwip/src/core/ipv4/ip4.c \
	badvpn/lwip/src/core/ipv4/ip4_addr.c \
	badvpn/lwip/src/core/ipv4/ip4_frag.c \
	badvpn/lwip/src/core/ipv6/icmp6.c \
	badvpn/lwip/src/core/ipv6/ip6.c \
	badvpn/lwip/src/core/ipv6/ip6_addr.c \
	badvpn/lwip/src/core/ipv6/ip6_frag.c \
	badvpn/lwip/src/core/ipv6/nd6.c \
	badvpn/lwip/src/core/mem.c \
	badvpn/lwip/src/core/memp.c \
	badvpn/lwip/src/core/netif.c \
	badvpn/lwip/src/core/pbuf.c \
	badvpn/lwip/src/core/stats.c \
	badvpn/lwip/src/core/sys.c \
	badvpn/lwip/src/core/tcp.c \
	badvpn/lwip/src/core/tcp_in.c \
	badvpn/lwip/src/core/tcp_out.c \
	badvpn/lwip/src/core/timeouts.c \
	badvpn/lwip/src/core/udp.c \
	badvpn/socksclient/BSocksClient.c \
	badvpn/system/BConnection_common.c \
	badvpn/system/BConnection_unix.c \
	badvpn/system/BDatagram_common.c \
	badvpn/system/BDatagram_unix.c \
	badvpn/system/BNetwork.c \
	badvpn/system/BReactor_badvpn.c \
	badvpn/system/BSignal.c \
	badvpn/system/BTime.c \
	badvpn/system/BUnixSignal.c \
	badvpn/tun2socks/SocksUdpGwClient.c \
	badvpn/tun2socks/tun2socks.c \
	badvpn/tuntap/BTap.c \
	badvpn/udpgw_client/UdpGwClient.c \
	libancillary/fd_recv.c \
	libancillary/fd_send.c

LOCAL_MODULE := tun2socks

LOCAL_LDLIBS := -ldl -llog

include $(BUILD_SYSTEM)/build-executable.mk


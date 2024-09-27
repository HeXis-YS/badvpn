LOCAL_PATH := $(call my-dir)
ROOT_PATH := $(LOCAL_PATH)

########################################################
## tun2socks
########################################################

include $(CLEAR_VARS)

LOCAL_LDFLAGS := -Wno-unused-command-line-argument
LOCAL_LDFLAGS += -fPIE -Ofast -mcpu=cortex-a55+crypto+ssbs -mtune=cortex-a55 -flto=full -fno-common -fno-plt -fno-semantic-interposition -fcf-protection=none
LOCAL_LDFLAGS += -mllvm -polly -mllvm -polly-vectorizer=stripmine -mllvm -polly-ast-use-context -mllvm -polly-loopfusion-greedy -mllvm -polly-run-inliner -mllvm -polly-run-dce -mllvm -polly-2nd-level-tiling -mllvm -polly-pattern-matching-based-opts -mllvm -polly-position=before-vectorizer -mllvm -polly-invariant-load-hoisting
LOCAL_LDFLAGS += -ftls-model=initial-exec -fno-builtin-malloc
LOCAL_LDFLAGS += -fuse-ld=lld -s -Wl,-O3,--as-needed,--icf=all,-z,lazy,-z,norelro,-sort-common
# LOCAL_LDFLAGS += -static -Wl,-Bdynamic,-llog,-Bstatic,-ldl
LOCAL_LDFLAGS += -llog -ldl
LOCAL_LDFLAGS += -Wl,--gc-sections
# LOCAL_LDFLAGS += -fprofile-generate=/storage/emulated/0/Android/data/com.v2ray.ang/

LOCAL_CFLAGS := -std=gnu11 $(LOCAL_LDFLAGS)
LOCAL_CFLAGS += -DBADVPN_THREAD_SAFE=0 -DBADVPN_LINUX -DBADVPN_BREACTOR_BADVPN -D_GNU_SOURCE
LOCAL_CFLAGS += -DBADVPN_USE_SIGNALFD -DBADVPN_USE_EPOLL
LOCAL_CFLAGS += -DBADVPN_LITTLE_ENDIAN
LOCAL_CFLAGS += -DNDEBUG -DANDROID
LOCAL_CFLAGS += -DMI_MALLOC_OVERRIDE
LOCAL_CFLAGS += -I

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/badvpn \
	$(LOCAL_PATH)/badvpn/lwip/custom \
	$(LOCAL_PATH)/badvpn/lwip/src/include \
	$(LOCAL_PATH)/badvpn/lwip/src/include/ipv4 \
	$(LOCAL_PATH)/badvpn/lwip/src/include/ipv6 \
	$(LOCAL_PATH)/libancillary \
	$(LOCAL_PATH)/mimalloc/include

LOCAL_SRC_FILES := \
	badvpn/base/BLog.c \
	badvpn/base/BLog_syslog.c \
	badvpn/base/BPending.c \
	badvpn/flow/BufferWriter.c \
	badvpn/flow/PacketBuffer.c \
	badvpn/flow/PacketPassInterface.c \
	badvpn/flow/PacketRecvInterface.c \
	badvpn/flow/PacketStreamSender.c \
	badvpn/flow/SinglePacketBuffer.c \
	badvpn/flow/StreamPassInterface.c \
	badvpn/flow/StreamRecvInterface.c \
	badvpn/flowextra/PacketPassInactivityMonitor.c \
	badvpn/lwip/src/core/def.c \
	badvpn/lwip/src/core/inet_chksum.c \
	badvpn/lwip/src/core/init.c \
	badvpn/lwip/src/core/ip.c \
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
	badvpn/lwip/src/core/tcp.c \
	badvpn/lwip/src/core/tcp_in.c \
	badvpn/lwip/src/core/tcp_out.c \
	badvpn/lwip/src/core/timeouts.c \
	badvpn/socks_udp_client/SocksUdpClient.c \
	badvpn/socksclient/BSocksClient.c \
	badvpn/system/BConnection_common.c \
	badvpn/system/BConnection_unix.c \
	badvpn/system/BDatagram_unix.c \
	badvpn/system/BNetwork.c \
	badvpn/system/BReactor_badvpn.c \
	badvpn/system/BSignal.c \
	badvpn/system/BTime.c \
	badvpn/system/BUnixSignal.c \
	badvpn/tun2socks/tun2socks.c \
	badvpn/tuntap/BTap.c \
	libancillary/fd_recv.c \
	libancillary/fd_send.c \
	mimalloc/src/static.c

LOCAL_MODULE := tun2socks

include $(BUILD_SYSTEM)/build-executable.mk

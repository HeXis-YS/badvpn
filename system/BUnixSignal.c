/**
 * @file BUnixSignal.c
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

#include <inttypes.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

#include <sys/signalfd.h>

#include <misc/balloc.h>
#include <misc/nonblocking.h>
#include <base/BLog.h>

#include <system/BUnixSignal.h>

#include <generated/blog_channel_BUnixSignal.h>

#define BUNIXSIGNAL_MAX_SIGNALS 64

static void signalfd_handler (BUnixSignal *o, int events)
{
    DebugObject_Access(&o->d_obj);
    
    // read a signal
    struct signalfd_siginfo siginfo;
    int bytes = read(o->signalfd_fd, &siginfo, sizeof(siginfo));
    if (bytes < 0) {
        int error = errno;
        if (error == EAGAIN || error == EWOULDBLOCK) {
            return;
        }
        BLog(BLOG_ERROR, "read failed (%d)", error);
        return;
    }
    ASSERT_FORCE(bytes == sizeof(siginfo))
    
    // check signal
    if (siginfo.ssi_signo > INT_MAX) {
        BLog(BLOG_ERROR, "read returned out of int range signo (%"PRIu32")", siginfo.ssi_signo);
        return;
    }
    int signo = siginfo.ssi_signo;
    if (sigismember(&o->signals, signo) <= 0) {
        BLog(BLOG_ERROR, "read returned wrong signo (%d)", signo);
        return;
    }
    
    BLog(BLOG_DEBUG, "dispatching signal %d", signo);
    
    // call handler
    o->handler(o->user, signo);
    return;
}

int BUnixSignal_Init (BUnixSignal *o, BReactor *reactor, sigset_t signals, BUnixSignal_handler handler, void *user)
{
    // init arguments
    o->reactor = reactor;
    o->signals = signals;
    o->handler = handler;
    o->user = user;
    
    // init signalfd fd
    if ((o->signalfd_fd = signalfd(-1, &o->signals, 0)) < 0) {
        BLog(BLOG_ERROR, "signalfd failed");
        goto fail0;
    }
    
    // set non-blocking
    if (fcntl(o->signalfd_fd, F_SETFL, O_NONBLOCK) < 0) {
        BLog(BLOG_ERROR, "cannot set non-blocking");
        goto fail1;
    }
    
    // init signalfd BFileDescriptor
    BFileDescriptor_Init(&o->signalfd_bfd, o->signalfd_fd, (BFileDescriptor_handler)signalfd_handler, o);
    if (!BReactor_AddFileDescriptor(o->reactor, &o->signalfd_bfd)) {
        BLog(BLOG_ERROR, "BReactor_AddFileDescriptor failed");
        goto fail1;
    }
    BReactor_SetFileDescriptorEvents(o->reactor, &o->signalfd_bfd, BREACTOR_READ);
    
    // block signals
    if (pthread_sigmask(SIG_BLOCK, &o->signals, 0) != 0) {
        BLog(BLOG_ERROR, "pthread_sigmask block failed");
        goto fail2;
    }
    
    DebugObject_Init(&o->d_obj);
    
    return 1;
    
fail2:
    BReactor_RemoveFileDescriptor(o->reactor, &o->signalfd_bfd);
fail1:
    ASSERT_FORCE(close(o->signalfd_fd) == 0)    
fail0:
    return 0;
}

void BUnixSignal_Free (BUnixSignal *o, int unblock)
{
    ASSERT(unblock == 0 || unblock == 1)
    DebugObject_Free(&o->d_obj);
    
    if (unblock) {
        // unblock signals
        ASSERT_FORCE(pthread_sigmask(SIG_UNBLOCK, &o->signals, 0) == 0)
    }
    
    // free signalfd BFileDescriptor
    BReactor_RemoveFileDescriptor(o->reactor, &o->signalfd_bfd);
    
    // free signalfd fd
    ASSERT_FORCE(close(o->signalfd_fd) == 0)
}

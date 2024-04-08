#!/bin/bash
set -o errexit
set -o pipefail

# Set magic variables for current file & dir
__dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
__file="${__dir}/$(basename "${BASH_SOURCE[0]}")"
__base="$(basename ${__file} .sh)"

if [[ -z $NDK_HOME ]]; then
	if [[ -n $ANDROID_NDK_LATEST_HOME ]]; then
		NDK_HOME=$ANDROID_NDK_LATEST_HOME
	fi
fi
if [[ ! -d $NDK_HOME ]]; then
	echo "Android NDK: NDK_HOME not found. please set env \$NDK_HOME"
	exit 1
fi

TMPDIR=$(mktemp -d)
clear_tmp () {
	rm -rf $TMPDIR
}

trap 'echo -e "Aborted, error $? in command: $BASH_COMMAND"; trap ERR; clear_tmp; exit 1' ERR INT
install -m644 $__dir/tun2socks-android-cortex-a55.mk $TMPDIR/

pushd $TMPDIR
cp -r $__dir badvpn
git clone --depth=1 https://github.com/mhaberler/libancillary.git
git clone --depth=1 -b v2.1.2 https://github.com/microsoft/mimalloc.git
$NDK_HOME/ndk-build \
	NDK_PROJECT_PATH=. \
	APP_BUILD_SCRIPT=./tun2socks-android-cortex-a55.mk \
	APP_ABI=arm64-v8a \
	APP_PLATFORM=android-21 \
	NDK_LIBS_OUT=$TMPDIR/libs \
	NDK_OUT=$TMPDIR/tmp \
	APP_SHORT_COMMANDS=false LOCAL_SHORT_COMMANDS=false -B -j$(nproc)

install -v -D -m755 libs/arm64-v8a/tun2socks    $__dir/libtun2socks.so
popd

rm -rf $TMPDIR

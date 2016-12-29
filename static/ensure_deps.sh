#!/usr/bin/env bash

UTIL_LINUX_VERSION=2.29

UTIL_LINUX_URL=https://www.kernel.org/pub/linux/utils/util-linux/v$UTIL_LINUX_VERSION/util-linux-$UTIL_LINUX_VERSION.tar.gz


PLATFORM=$(uname -s)

case $PLATFORM in
  "Linux")
    RMDIR="rmdir -p --ignore-fail-on-non-empty"
  ;;

  "Darwin")
    RMDIR="rmdir -p"
  ;;

  *)
    echo "Unsupported platform: $PLATFORM" >&2
    exit 1
  ;;
esac

function rmStep() {
  rm -rf "$@"
  $RMDIR `dirname "$@"`
}

function err() {
  rmStep $SRC_DIR
  exit $1
}


DEPS="$(dirname $0)/../deps"

SRC_DIR=$DEPS/util-linux


if [ ! -d $SRC_DIR ]; then
  mkdir -p $SRC_DIR || exit 2

  curl -s -L $UTIL_LINUX_URL | tar xz -C $SRC_DIR --strip-components=1 || err 3


  # HACK `gyp` checks by default that there are no files with the same basename
  # due to limits on VisualStudio 2008 and OSX `make` command, and `node-gyp`
  # don't allow to override it, so I just simply rename the files and use the
  # new names on `util-linux.gyp` file.

  SRC=$SRC_DIR/libblkid/src

  mv $SRC/superblocks/minix.c $SRC/superblocks/minix_superblocks.c &&
  mv $SRC/topology/lvm.c      $SRC/topology/lvm_topology.c         || err 4
fi


if [ ! -d $SRC_DIR ]; then
  echo false
else
  echo true
fi

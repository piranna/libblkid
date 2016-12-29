#!/usr/bin/env bash

has_ldconfig() {
  hash ldconfig 2>/dev/null
}

has_system_lib() {
  local regex="lib$1.+(a|so|dylib)"

  # Add /sbin to path as ldconfig is located there on some systems - e.g. Debian
  # (and it still can be used by unprivileged users):
  PATH="$PATH:/sbin"
  export PATH
  # Try using ldconfig on linux systems
  if $(has_ldconfig); then
    # Use `for` because there would be several ones, but we are only interested
    # to know if there's at least one
    for _ in $(ldconfig -p 2>/dev/null | grep -E "$regex"); do
      return 0
    done
  fi

  # Try just checking common library locations
  for dir in /lib /usr/lib /usr/local/lib /opt/local/lib \
             /usr/lib/x86_64-linux-gnu /usr/lib/i386-linux-gnu; do
    test -d $dir && ls $dir | grep -E "$regex" && return 0
  done

  # Library not found
  return 1
}

has_system_headers() {
  # Try just checking common headers locations
  for dir in /include /usr/include /usr/local/include /opt/local/include; do
    test -d $dir && ls $dir | grep -E "$1" && return 0
  done

  # Headers not found
  return 1
}

has_library() {
  has_system_lib $1
  resutl1=$?

  has_system_headers $1
  resutl2=$?

  if [[ resutl1 -eq 0 && resutl2 -eq 0 ]]; then
    return 0
  fi

  return 1
}


case "$1" in
  blkid)
    has_library "blkid" > /dev/null
    result=$?
    ;;

  *)
    >&2 echo "Unknown library: $1"
    exit 1
esac


if test $result -eq 0; then
  echo "true"
else
  echo "false"
fi

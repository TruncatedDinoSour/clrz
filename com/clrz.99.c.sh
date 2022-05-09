#!/usr/bin/env sh

set -e

main() {
    CC="${CC:-gcc}"
    CFLAGS="${CFLAGS:--std=c99}"
    SRC="${SRC:-./src/clrz.99.c}"
    SFLAGS="${SFLAGS:--R .comment -R .GCC.command.line -R .note.gnu.gold-version -R .note.gnu.build-id -R .note.ABI-tag -R .note -R .gnu.version --strip-debug --strip-unneeded}"

    {
        echo ' * Compiling C code'
        echo "   Source file:           $SRC"
        echo "   C compiler:            $CC"
        echo "   C Compiler Flags:      $CFLAGS"
        echo "   Strip:                 ${STRIP:-No}"
        echo "   Strip flags:           ${SFLAGS}"
    } >&2

    set -x
    eval -- "$CC $SRC -o clrz $CFLAGS"
    [ "$STRIP" ] && eval -- "strip $SFLAGS clrz"
    set +x
}

main "$@"

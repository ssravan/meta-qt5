DEPENDS = "qt5-x11-free"

LICENSE = "LGPLv2.1"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/LGPL-2.1;md5=1a6d268fd218675ffea8be556788b780"

PR = "r0"

inherit qmake2

do_configure () {
    :
}

do_compile () {
    QTDIR="${QMAKESPEC}/../.." qmake2
    oe_runmake CC="${CC}" CXX="${CXX}"
}

do_install() {
    oe_runmake install DESTDIR="${D}"
}

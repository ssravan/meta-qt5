DEPENDS = "qt5-x11-free"

LICENSE = "LGPLv2.1"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/LGPL-2.1;md5=1a6d268fd218675ffea8be556788b780"

PR = "r2"

inherit qt5x11

name = "QtV8"
FILES_${PN} = "${libdir}/lib${name}.so.*"
FILES_${PN}-dev = "\
    ${libdir}/lib${name}.prl                        \
    ${libdir}/lib${name}.a                          \
    ${libdir}/lib${name}.la                         \
    ${libdir}/lib${name}.so                         \
    ${includedir}/${QT_DIR_NAME}/${name}            \
    ${libdir}/pkgconfig/${name}.pc                  \
"
FILES_${PN}-dbg = "${libdir}/.debug/lib${name}.so* ${exec_prefix}/src/debug/"

do_configure () {
    :
}


do_compile () {
    QTDIR="${QMAKESPEC}/../.." qmake2
    oe_runmake CC="${CC}" CXX="${CXX}"
}

do_install() {
    sed -i -e 's#$(INSTALL_ROOT)${STAGING_DIR}/${MACHINE}#$(INSTALL_ROOT)#g' \
        $(find . -name Makefile)
    oe_runmake install INSTALL_ROOT="${D}"
}

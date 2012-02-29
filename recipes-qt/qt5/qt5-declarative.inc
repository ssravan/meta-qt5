DEPENDS = "qt5-x11-free qt5-xmlpatterns qt5-jsbackend"

LICENSE = "LGPLv2.1"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/LGPL-2.1;md5=1a6d268fd218675ffea8be556788b780"

PR = "r1"

inherit qmake2

name = "QtDeclarative"
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
    oe_runmake install INSTALL_ROOT="${D}"
}

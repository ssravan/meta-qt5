DEPENDS = "qt5-x11-free qt5-xmlpatterns qt5-jsbackend"

LICENSE = "LGPLv2.1"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/LGPL-2.1;md5=1a6d268fd218675ffea8be556788b780"

PR = "r3"

inherit qt5x11

FILES_${PN}-dbg += "\
    ${exec_prefix}/src/debug                        \
    ${libdir}/${QT_DIR_NAME}/imports/*/.debug       \
    ${libdir}/${QT_DIR_NAME}/imports/*/*/.debug     \
    ${libdir}/${QT_DIR_NAME}/imports/*/*/*/.debug   \
    ${libdir}/${QT_DIR_NAME}/plugins/*/.debug       \
"

FILES_${PN} += "\
    ${libdir}/${QT_DIR_NAME}/imports                \
    ${libdir}/${QT_DIR_NAME}/plugins                \
"
FILES_${PN}-dev += "\
    ${libdir}/cmake                                 \
    ${datadir}/${QT_DIR_NAME}/mkspecs               \
"
do_configure () {
    :
}

do_compile () {
    QTDIR="${QMAKESPEC}/../.." qmake2
    oe_runmake CC="${CC}" CXX="${CXX}"
}

do_install() {
    sed -i                                                          \
        -e 's#$(INSTALL_ROOT)${STAGING_DIR}/${MACHINE}#$(INSTALL_ROOT)#g' \
        -e 's#$(INSTALL_ROOT)${STAGING_DIR}/${BUILD_SYS}#$(INSTALL_ROOT)#g' \
        $(find . -name Makefile)

    oe_runmake install INSTALL_ROOT="${D}"

    mkdir ${D}${libdir}/${QT_DIR_NAME}
    mkdir ${D}${includedir}/${QT_DIR_NAME}
    mv ${D}${includedir}/Qt* ${D}${includedir}/${QT_DIR_NAME}
    mv ${D}/usr/imports ${D}${libdir}/${QT_DIR_NAME}/imports
    mv ${D}/usr/plugins ${D}${libdir}/${QT_DIR_NAME}/plugins
}


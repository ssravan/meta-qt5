DEPENDS = "qt5-x11-free"

LICENSE = "LGPLv2.1"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/LGPL-2.1;md5=1a6d268fd218675ffea8be556788b780"

PR = "r4"

inherit qt5x11

PACKAGES += "${PN}-examples"

FILES_${PN}-dev += "\
    ${includedir}/${QT_DIR_NAME}/${name} \
    ${libdir}/*.prl \
    ${libdir}/cmake \
"
FILES_${PN}-dbg += "${exec_prefix}/src/debug/"
FILES_${PN}-examples += "/usr/local/qt5/examples"

do_configure () {
    :
}

do_compile () {
    QTDIR="${QMAKESPEC}/../.." qmake2
    oe_runmake
}

do_install() {
    oe_runmake install INSTALL_ROOT="${D}"
}

do_install_append() {
    rsync -av ${D}${STAGING_DIR_NATIVE}/ ${STAGING_DIR_NATIVE}
    rm -r ${D}${STAGING_DIR_NATIVE}

    rsync -av ${D}${STAGING_DIR_TARGET}/* ${D}
    rm -r ${D}${STAGING_DIR_TARGET}
}

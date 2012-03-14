DEPENDS = "qt5-x11-free qt5-xmlpatterns qt5-jsbackend"

LICENSE = "LGPLv2.1"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/LGPL-2.1;md5=1a6d268fd218675ffea8be556788b780"

PR = "r4"

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
    ${incdir}/${QT_DIR_NAME}                        \
    ${libdir}/*.prl                                 \
"

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

#    mkdir ${D}${libdir}/${QT_DIR_NAME}
#    mkdir ${D}${includedir}/${QT_DIR_NAME}
#    mv ${D}${includedir}/Qt* ${D}${includedir}/${QT_DIR_NAME}
#    mv ${D}/usr/imports ${D}${libdir}/${QT_DIR_NAME}/imports
#    mv ${D}/usr/plugins ${D}${libdir}/${QT_DIR_NAME}/plugins
}

DEPENDS = "qt5-x11-free qt5-xmlpatterns qt5-jsbackend"

LICENSE = "LGPLv2.1"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/LGPL-2.1;md5=1a6d268fd218675ffea8be556788b780"

PR = "r7"

inherit qt5x11

#SRC_URI += "file://qt5-declarative-plugin-installpath.patch"

PACKAGES += "${PN}-examples-dbg ${PN}-examples"

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
FILES_${PN}-examples += "/usr/local/${QT_DIR_NAME}/examples"
FILES_${PN}-examples-dbg += "\
    /usr/local/${QT_DIR_NAME}/examples/.debug \
    /usr/local/${QT_DIR_NAME}/examples/*/.debug \
    /usr/local/${QT_DIR_NAME}/examples/*/*/.debug \
    /usr/local/${QT_DIR_NAME}/examples/*/*/*/.debug \
    /usr/local/${QT_DIR_NAME}/examples/*/*/*/*/.debug \
    /usr/local/${QT_DIR_NAME}/examples/*/*/*/*/*/.debug \
    /usr/local/${QT_DIR_NAME}/examples/*/*/*/*/*/*/.debug \
"

do_configure () {
    :
}

do_compile () {
    QTDIR="${QMAKESPEC}/../.." qmake2

    # src/plugins/accessible will create a directory in $libdir during compilation.
    # Pass in INSTALL_ROOT to avoid messing up the host system
    oe_runmake INSTALL_ROOT="${D}"
}

do_install_prepend() {
    pushd lib/cmake
        for i in *; do
        m=${i/Qt5/}
        sed -i \
            -e "s#${STAGING_DIR_TARGET}${includedir}/${QT_DIR_NAME}/#\${_qt5${m}_install_prefix}/include/${QT_DIR_NAME}/#g" \
            ${i}/${i}Config.cmake
    done
    popd
}

do_install() {
    oe_runmake INSTALL_ROOT="${D}" install
}

do_install_append() {
    rsync -av ${D}${STAGING_DIR_NATIVE}/ ${STAGING_DIR_NATIVE}
    rm -r ${D}${STAGING_DIR_NATIVE}

    rsync -av ${D}${STAGING_DIR_TARGET}/* ${D}
    rm -r ${D}${STAGING_DIR_TARGET}
}

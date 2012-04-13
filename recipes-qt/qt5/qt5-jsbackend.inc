DEPENDS = "qt5-x11-free"

LICENSE = "LGPLv2.1"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/LGPL-2.1;md5=1a6d268fd218675ffea8be556788b780"

PR = "r6"

inherit qt5x11

SRC_URI += "file://qtjsbackend-novfpdetection.patch"

FILES_${PN}-dev += "\
    ${includedir}/${QT_DIR_NAME}            \
    ${libdir}/cmake                         \
    ${libdir}/*.prl                         \
"
FILES_${PN}-dbg += "${exec_prefix}/src/debug"

do_configure () {
    :
}


do_compile () {
    QTDIR=${QMAKESPEC}/../.. qmake2

    if ! grep -q 'config_test_hardfloat = yes' .qmake.cache; then
        die "Hardfloat detection failed!"
    fi

    oe_runmake
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
    oe_runmake install INSTALL_ROOT="${D}"
}

do_install_append() {
    rsync -av ${D}${STAGING_DIR_NATIVE}/ ${STAGING_DIR_NATIVE}
    rm -r ${D}${STAGING_DIR_NATIVE}

    rsync -av ${D}${STAGING_DIR_TARGET}/* ${D}
    rm -r ${D}${STAGING_DIR_TARGET}
}

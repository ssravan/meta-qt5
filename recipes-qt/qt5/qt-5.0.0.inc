LICENSE = "LGPLv2.1"
LIC_FILES_CHKSUM = "file://LICENSE.LGPL;md5=cc5963be04f8b19c3e3c46bc31f0f6e1"

FILESPATHS =. "${FILE_DIRNAME}/qt-${PV}:"

# hw: wtf??
FILESEXTRAPATHS =. "${FILE_DIRNAME}/qt-${PV}:"

SRCREV = "805d8959787ba03a35436e1235648d01bdfd91c7"
SRC_URI = "git://gitorious.org/qt/qtbase.git;protocol=git \
           file://g++-base.conf \
           file://gcc-base.conf \
           file://linux.conf"
S = "${WORKDIR}/git"

FILES_${QT_BASE_NAME}-tools_append = " ${bindir}/qml ${bindir}/qmlplugindump"
FILES_${QT_BASE_NAME}-tools-dbg_append = " ${bindir}/.debug/qml ${bindir}/.debug/qmlplugindump"

PACKAGES_append = " ${QT_BASE_NAME}-tests-dbg ${QT_BASE_NAME}-tests"
FILES_${QT_BASE_NAME}-tests-dbg = "/usr/tests/qt5/*/.debug"
FILES_${QT_BASE_NAME}-tests = "/usr/tests/qt5/*"

EXTRA_OEMAKE = " "

do_configure_prepend() {
    for pro in $(find ${S} -name "*.pro") ; do
        sed -i \
            -e 's:$$QT_BUILD_TREE/bin/lrelease:${OE_QMAKE_LRELEASE}:g' \
            -e 's:qtPrepareTool(LRELEASE, lrelease):LRELEASE = ${OE_QMAKE_LRELEASE}:g' $pro
    done

    sed -i s:SEDME:${S}: ${WORKDIR}/linux.conf
    sed -i \
    -e /QMAKE_MOC\ /d \
    -e /QMAKE_UIC\ /d \
    -e /QMAKE_RCC\ /d \
    ${S}/configure

    # Prefer g++ to ld
    unset LD
}

do_compile() {
    # Fixup missing wsegl header in some SGX SDKs
#    if ! [ -e ${STAGING_INCDIR}/wsegl.h ] ; then
#        cp src/3rdparty/powervr/wsegl.h src/plugins/gfxdrivers/powervr/QWSWSEGL/
#    fi

    unset CFLAGS CXXFLAGS

    oe_runmake ${EXTRA_ENV}
}

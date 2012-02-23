require qt5-native.inc
require qt5_arch.inc

DESCRIPTION = "SDK tools for Qt version 5.x"
DEPENDS = "zlib-nativesdk dbus-nativesdk libx11-nativesdk qt5-tools-native"
SECTION = "libs"
HOMEPAGE = "http://qt.nokia.com"
INC_PR = "r2"

inherit nativesdk qmake2

SRC_URI += "file://configure-lflags.patch \
            file://qmake-exists-check.patch \
            file://configure-paths.patch \
            file://qt-dbus-const.patch"

EXTRA_OECONF = "-opensource -confirm-license \
                -prefix ${prefix} \
                -nomake libs -nomake examples -nomake tests \
                -verbose -release -static \
                -platform ${TARGET_OS}-oe-g++ \
                -xplatform ${TARGET_OS}-oe-g++ \
                -arch ${@qt5_arch(d)} \
                ${@qt5_endian(d)} \
                -host-little-endian \
                -no-xcb -no-wayland \
                -I${STAGING_DIR_HOST}${SDKPATHNATIVE}/usr/include/dbus-1.0 \
                -I${STAGING_DIR_HOST}${SDKPATHNATIVE}/usr/lib/dbus-1.0/include"

# yank default -e, otherwise we get the following error:
# moc_qbuffer.cpp: No such file or directory
EXTRA_OEMAKE = " "

do_configure() {
    # prefer g++ over ld
    unset LD

    if [ ! -e mkspecs/${TARGET_OS}-oe-g++ ]; then
        pushd mkspecs
        ln -sf linux-g++ ${TARGET_OS}-oe-g++
        popd
    fi

    cp -f ${WORKDIR}/g++-base.conf mkspecs/common/g++-base.conf
    cp -f ${WORKDIR}/gcc-base.conf mkspecs/common/gcc-base.conf
    cp -f ${WORKDIR}/linux.conf mkspecs/common/

    # don't use host g++ even during configure
    sed -i -e "s#g++#${CXX}#" mkspecs/common/g++-base.conf
    sed -i -e "s#gcc#${CC}#" mkspecs/common/g++-base.conf

    # first launch configure to get qmake compiled for the nativesdk
    CC="${CC}" CXX="${CXX}" ./configure ${EXTRA_OECONF} || true

    # then backup the binary and start again with a qmake which can run on the build host
    mv bin/qmake bin/qmake_nativesdk
    if [ ! -e bin/qmake ]; then
        pushd bin
        ln -sf ${STAGING_BINDIR_NATIVE}/qmake2 qmake
        popd
    fi
    CC="${CC}" CXX="${CXX}" ./configure ${EXTRA_OECONF} \
        || die "Configuring qt failed. EXTRA_OECONF was ${EXTRA_OECONF}"
}

TOBUILD = "\
  src/tools/bootstrap \
  src/tools/moc \
  src/tools/uic \
  src/tools/rcc \
"

do_compile() {
    oe_runmake CC="${CC}" CXX="${CXX}"
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 bin/qmake_nativesdk ${D}${bindir}/qmake2
    for i in moc uic rcc; do
        install -m 0755 bin/${i} ${D}${bindir}/${i}5
    done

    (cd ${D}${bindir}; \
    ln -s qmake2 qmake; \
    for i in moc uic rcc; do \
        ln -s ${i}5 ${i}; \
    done)
}

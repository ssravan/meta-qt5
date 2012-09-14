DESCRIPTION = "SDK tools for Qt version 5.x"
DEPENDS = "nativesdk-zlib nativesdk-dbus nativesdk-libx11 qt5-tools-native"
SECTION = "libs"
HOMEPAGE = "http://qt.nokia.com"
INC_PR = "r6"

inherit nativesdk qmake2

require qt5_arch.inc
QT_ARCH := "${@qt5_arch(d)}"
QT_ENDIAN = "${@qt5_endian(d)}"

SRC_URI += "file://0004-no-qmake.patch"

QT_CONFIG_FLAGS += "\
    -reduce-relocations                         \
    -no-nis                                     \
    -release                                    \
    -no-rpath                                   \
    -no-xcb -no-opengl -no-eglfs		\
    -no-qpa-platform-guard			\
"

QT_DIR_NAME ?= "qt5"

# yank default -e, otherwise we get the following error:
# moc_qbuffer.cpp: No such file or directory
EXTRA_OEMAKE = " "

do_configure() {
    unset QMAKESPEC
    unset QTDIR
    unset LD
    unset CC
    unset CXX
    unset CFLAGS
    unset CXXFLAGS
    unset RANLIB
    unset OBJDUMP
    unset CCLD
    unset OE_QMAKE_UIC
    unset OE_QMAKE_MOC
    unset OE_QMAKE_RCC
    unset OE_QMAKE_QMAKE

    mkdir -p mkspecs/${TARGET_OS}-oe-g++
    cp -f ${WORKDIR}/qplatformdefs.h mkspecs/${TARGET_OS}-oe-g++
    bash ${WORKDIR}/qmake.conf.sh > mkspecs/${TARGET_OS}-oe-g++/qmake.conf

    mkdir -p mkspecs/build-oe-g++
    cp -f ${WORKDIR}/qplatformdefs.h mkspecs/build-oe-g++
    bash ${WORKDIR}/qmake-build.conf.sh > mkspecs/build-oe-g++/qmake.conf

    # Use qmake from qt5-native for building
    if [ ! -e bin/qmake ]; then
        ln -sf ${STAGING_BINDIR_NATIVE}/qmake2 bin/qmake
    fi

    ln -sf ${TARGET_OS}-oe-g++ mkspecs/default

    ./configure -v \
        -opensource -confirm-license \
        -prefix ${prefix} \
        -datadir ${datadir}/${QT_DIR_NAME} \
        -sysconfdir ${sysconfdir}/${QT_DIR_NAME} \
        -docdir ${docdir}/${QT_DIR_NAME} \
        -headerdir ${includedir}/${QT_DIR_NAME} \
        -plugindir ${libdir}/${QT_DIR_NAME}/plugins \
        -importdir ${libdir}/${QT_DIR_NAME}/imports \
        -translationdir ${datadir}/${QT_DIR_NAME}/translations \
        -platform ${TARGET_OS}-oe-g++              \
        -xplatform ${TARGET_OS}-oe-g++                 \
        ${QT_CONFIG_FLAGS} -no-fast
}

do_compile() {
    unset QMAKESPEC
    unset QTDIR
    unset LD
    unset CC
    unset CXX
    unset CFLAGS
    unset CXXFLAGS
    unset RANLIB
    unset OBJDUMP
    unset CCLD

    oe_runmake sub-src-qmake_all

    oe_runmake -C src/tools sub-tools-bootstrap-all
    for i in rcc moc uic; do
        oe_runmake -C src/tools sub-${i}
    done

    # rebuild qmake
    pushd qmake
    QMAKESPEC=../mkspecs/${TARGET_OS}-oe-g++ ../bin/qmake
    oe_runmake 
    popd
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 bin/qmake ${D}${bindir}/qmake2
    for i in moc uic rcc; do
        install -m 0755 bin/${i} ${D}${bindir}/${i}5
    done

    (cd ${D}${bindir}; \
    ln -s qmake2 qmake; \
    for i in moc uic rcc; do \
        ln -s ${i}5 ${i}; \
    done)
}

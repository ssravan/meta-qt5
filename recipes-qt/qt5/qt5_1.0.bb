# @@@LICENSE
#
#      Copyright (c) 2012 Hewlett-Packard Development Company, L.P.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# LICENSE@@@

DESCRIPTION = "Qt is a versatile cross-platform application framework"
# TODO: Change GPL-3.0 license to LICENSE.GPL3 once it gets in Qt Github repository
LICENSE = "LGPLv2.1 | GPLv3"
LIC_FILES_CHKSUM = \ 
                  " file://qtbase/LICENSE.LGPL;md5=cc5963be04f8b19c3e3c46bc31f0f6e1 \
                    file://qtbase/LGPL_EXCEPTION.txt;md5=411080a56ff917a5a1aa08c98acae354 \
		    file://${COMMON_LICENSE_DIR}/GPL-3.0;md5=c79ff39f19dfec6d293b95dea7b07891" 
SECTION = "webos/libs"
DEPENDS += "freetype jpeg libpng zlib glib-2.0 nyx-lib"

inherit autotools
inherit pkgconfig
SRCREV = "${AUTOREV}"

#WEBOS_GIT_TAG = "${WEBOS_SUBMISSION}"
#SRC_URI = "${OPENWEBOS_GIT_REPO}/qt;tag=${WEBOS_GIT_TAG};protocol=git"
SRC_URI = "git://github-mirror.palm.com/openwebos/Qt5.git;protocol=git"
 
S = "${WORKDIR}/git"
QTBASE = "${S}/qtbase"
PALM_BUILD_DIR = "${S}/../qt-build-${MACHINE}"

export LD = "i586-webos-linux-g++ --sysroot=${PKG_CONFIG_SYSROOT_DIR}"

do_unpack_append() {
        bb.build.exec_func('do_fetch_submodules', d)
}

do_fetch_submodules() {
    cd ${S}
    sed -i 's/gitorious.org/github-mirror.palm.com/g' .gitmodules
    perl init-repository --no-webkit -f 
}

QT_CONFIG_FLAGS = "-release -qpa -little-endian -glib\
                   -opensource -confirm-license -no-pch \
                   -reduce-relocations -reduce-exports -force-pkg-config \
                   -qt-zlib -qt-libpng -qt-libjpeg \ 
                   -no-opengl -no-avx -no-neon -no-rpath \
                   -no-cups -no-nis -no-cups -no-sql-odbc -no-sql-tds \
                   -no-accessibility -no-phonon-backend \
                   -no-javascript-jit -no-dbus -no-sql-sqlite -no-sql-psql -no-sql-mysql \
                   -no-gstreamer -no-audio-backend \
                   -nomake examples -nomake demos -no-sse2 -no-ssse3 \
                   -nomake tests -no-gtkstyle -nomake translations \
                   --bindir=${STAGING_BINDIR_NATIVE} --prefix=${STAGING_DIR_HOST} \
                   -make 'libs'"

do_configure_prepend() {
    # clear out the staging folder
    rm -fr ${STAGING_INCDIR}/Qt
    rm -fr ${STAGING_INCDIR}/QtCore
    rm -fr ${STAGING_INCDIR}/QtGui
    rm -fr ${STAGING_INCDIR}/QtNetwork
    rm -fr ${STAGING_INCDIR}/QtOpenGL
    rm -fr ${STAGING_INCDIR}/QtSql
    rm -fr ${STAGING_INCDIR}/QtTest
    rm -fr ${STAGING_INCDIR}/QtXml
    rm -f ${STAGING_LIBDIR}/libQt*

    # Exporting these variables here so that ./configure knows about them when parsing qmake.conf
    export STAGING_INCDIR="${STAGING_INCDIR}"
    export STAGING_LIBDIR="${STAGING_LIBDIR}"

    unset STRIP
    unset F77
    unset QMAKE_MKSPEC_PATH
    unset CC
    unset CPPFLAGS
    unset RANLIB
    unset CXX
    unset OBJCOPY
    unset CCLD
    unset CFLAGS
    unset TARGET_LDFLAGS
    unset LDFLAGS
    unset AS
    unset AR
    unset CPP
    unset TARGET_CPPFLAGS
    unset CXXFLAGS
    unset OBJDUMP
    unset LD
}

do_configure() {
    cd ${S}
    export PATH="$PWD/qtbase/bin:$PWD/qtrepotools/bin:$PATH"
    ./configure ${QT_CONFIG_FLAGS}
#    cd ${QTBASE}/src
    for GLFILE in `find  ${QTBASE}/src -name Makefile`
    do
        echo ${GLFILE}
        sed -i 's/-lGL//g' ${GLFILE}
    done
    # We want the shared libraries to have an SONAME records => remove the empty -Wl,-soname,
    # argument that qmake adds (why is it doing this?).
    find . -name Makefile | xargs sed -i -e 's/-Wl,-soname, //' -e 's/-Wl,-soname,$//'
}

do_compile() {
    cd ${S}
    make -j 4
}

do_install() {
    export STAGING_INCDIR="${STAGING_INCDIR}"
    export STAGING_LIBDIR="${STAGING_LIBDIR}"
    cd ${PALM_BUILD_DIR}

    install -d ${D}${libdir}
    oe_libinstall -C ${PALM_BUILD_DIR}/lib/ -so libQtCore ${D}${libdir}
    oe_libinstall -C ${PALM_BUILD_DIR}/lib/ -so libQtGui ${D}${libdir}
    oe_libinstall -C ${PALM_BUILD_DIR}/lib/ -so libQtNetwork ${D}${libdir}
    oe_libinstall -C ${PALM_BUILD_DIR}/lib/ -so libQtXml ${D}${libdir}

    install -d ${D}/usr/plugins
    install -d ${D}/usr/plugins/imageformats
    install -m 555 ${PALM_BUILD_DIR}/plugins/imageformats/*.so ${D}/usr/plugins/imageformats

    if [ "${MACHINE}" != "qemux86" ]; then
        oe_libinstall -C ${PALM_BUILD_DIR}/lib/ -so libQtOpenGL ${D}${libdir}
    fi
    export STAGING_INCDIR="${STAGING_INCDIR}"
    export STAGING_LIBDIR="${STAGING_LIBDIR}"
    cd ${PALM_BUILD_DIR}

    oe_runmake install
    install -m 644 ${S}/src/opengl/gl2paintengineex/qglcustomshaderstage_p.h ${STAGING_INCDIR}/QtOpenGL
}

do_install_append() {
    oe_libinstall -C ${PALM_BUILD_DIR}/lib/ -so libQtDeclarative ${D}${libdir}
    oe_libinstall -C ${PALM_BUILD_DIR}/lib/ -so libQtScript ${D}${libdir}
    oe_libinstall -C ${PALM_BUILD_DIR}/lib/ -so libQtSql ${D}${libdir}

    if [ "${MACHINE}" = "opal" -o "${MACHINE}" = "topaz" ]; then
        oe_libinstall -C ${PALM_BUILD_DIR}/plugins/platforms -so libqpalm ${D}${libdir}
#        oe_libinstall -C ${PALM_BUILD_DIR}/plugins/platforms -so libqwebos ${D}${libdir}

        install -d ${D}/usr/plugins/platforms
        install -m 555 ${PALM_BUILD_DIR}/plugins/platforms/*.so ${D}/usr/plugins/platforms/

        install -m 555 ${PALM_BUILD_DIR}/plugins/platforms/libqpalm.so ${STAGING_LIBDIR}/libqpalm.so
#        install -m 555 ${PALM_BUILD_DIR}/plugins/platforms/libqwebos.so ${STAGING_LIBDIR}/libqwebos.so

        install -d ${D}/usr/plugins/imports/Qt/labs/shaders
        install -m 555 ${PALM_BUILD_DIR}/imports/Qt/labs/shaders/* ${D}/usr/plugins/imports/Qt/labs/shaders/
    fi
}

FILES_${PN} += "/usr/plugins"
FILES_${PN}-dbg += "/usr/plugins/gfxdrivers/.debug"
FILES_${PN}-dbg += "/usr/plugins/imageformats/.debug"
FILES_${PN}-dbg += "/usr/plugins/platforms/.debug"
FILES_${PN}-dbg += "/usr/plugins/imageformats/.debug"
FILES_${PN}-dbg += "/usr/plugins/imports/Qt/labs/shaders/.debug"

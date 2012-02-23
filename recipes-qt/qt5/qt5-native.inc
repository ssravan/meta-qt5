DESCRIPTION = "Native version of Qt"
DEPENDS = "zlib-native dbus-native"
SECTION = "libs"
HOMEPAGE = "http://qt.nokia.com"
PROVIDES = "qt5-tools-native"

INC_PR = "r1"

inherit native

LICENSE = "LGPLv2.1"
LIC_FILES_CHKSUM = "file://LICENSE.LGPL;md5=cc5963be04f8b19c3e3c46bc31f0f6e1"

FILESEXTRAPATHS =. "${FILE_DIRNAME}/qt-${PV}:"

SRCREV = "805d8959787ba03a35436e1235648d01bdfd91c7"
SRC_URI = "git://gitorious.org/qt/qtbase.git;protocol=git \
           file://qt-config.patch \
           file://g++-base.conf \
           file://gcc-base.conf \
           file://linux.conf"
S = "${WORKDIR}/git"

# FIXME: enable shared build
EXTRA_OECONF = "-prefix ${prefix} \
                -opensource -confirm-license \
                -nomake examples -nomake tests -nomake demos \
                -L ${STAGING_LIBDIR_NATIVE} \
                -I ${STAGING_INCDIR_NATIVE} \
                -system-zlib -exceptions \
                -no-phonon-backend \
                -no-libjpeg -no-libpng \
                -no-cups -no-nas-sound -no-nis -no-openssl \
                -no-freetype -no-glib -no-iconv \
                -static \
                -verbose -release \
                -no-fast -silent -no-rpath"

# yank default -e, otherwise we get the following error:
# moc_qbuffer.cpp: No such file or directory
EXTRA_OEMAKE = " "

do_configure() {
  # prefer g++ over ld
	unset LD

  ./configure ${EXTRA_OECONF} || die "Configuring qt failed. EXTRA_OECONF was ${EXTRA_OECONF}"
}

do_compile() {
  oe_runmake CC="${CC}" CXX="${CXX}"
}

do_install() {
	install -d ${D}${bindir}/
	install -m 0755 bin/qmake ${D}${bindir}/qmake2
	for i in moc uic rcc ; do
		install -m 0755 bin/${i} ${D}${bindir}/${i}5
	done
    
	install -d ${D}${datadir}/qt5/
	cp -PfR mkspecs ${D}${datadir}/qt5/
	ln -sf linux-g++ ${D}${datadir}/qt5/mkspecs/${BUILD_OS}-oe-g++
	cp -f ${WORKDIR}/g++-base.conf ${D}${datadir}/qt5/mkspecs/common/g++-base.conf
	cp -f ${WORKDIR}/gcc-base.conf ${D}${datadir}/qt5/mkspecs/common/gcc-base.conf
	cp -f ${WORKDIR}/linux.conf ${D}${datadir}/qt5/mkspecs/common/

  oe_runmake install INSTALL_ROOT=${D}
}

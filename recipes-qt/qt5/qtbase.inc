DESCRIPTION = "Qt5 base libraries"
DEPENDS = "zlib-native dbus-native"
SECTION = "libs"
HOMEPAGE = "http://qt.nokia.com"
PROVIDES = "qt5-tools-native"

INC_PR = "r1"

inherit native

LICENSE = "LGPLv2.1"
LIC_FILES_CHKSUM = "file://LICENSE.LGPL;md5=cc5963be04f8b19c3e3c46bc31f0f6e1"

SRCREV = "805d8959787ba03a35436e1235648d01bdfd91c7"
SRC_URI = "git://gitorious.org/qt/qtbase.git;protocol=git \
             file://g++.conf \
             file://linux.conf"

S = "${WORKDIR}/git"

EXTRA_OECONF = "-prefix ${prefix} \
                -L ${STAGING_LIBDIR_NATIVE} \
                -I ${STAGING_INCDIR_NATIVE} \
                -host-little-endian \
                -system-libjpeg -system-zlib \
                -system-libpng \
                -no-accessibility \
                -no-cups \
                -no-nas-sound \
                -no-nis -no-openssl \
                -verbose -release \
                -no-freetype -no-glib -no-iconv \
                -exceptions \
                -no-fast -silent -no-rpath"

EXTRA_OEMAKE = " "

do_configure() {
	# prefer g++ to ld
	unset LD

	(echo o; echo yes) | ${S}/configure ${EXTRA_OECONF} || die "Configuring qt failed. EXTRA_OECONF was ${EXTRA_OECONF}"
}

TOBUILD = "\
  src/tools/moc \
  src/concurrent \
  src/corelib \
  src/sql \
  src/xml \
  src/network \
  src/tools/uic \
  src/tools/rcc \
  src/xmlpatterns \
  src/dbus \
  src/gui \
  src/testlib \
  src/tools/uic3 \
  tools/linguist/lrelease \
  tools/linguist/lupdate \
  tools/qdbus/qdbuscpp2xml \
  tools/qdbus/qdbusxml2cpp \
"

do_compile() {
	for i in ${TOBUILD}; do
		cd ${S}/$i && oe_runmake CC="${CC}" CXX="${CXX}"
	done
}

do_install() {
	install -d ${D}${bindir}/
	install -m 0755 bin/qmake ${D}${bindir}/qmake2
	for i in moc uic uic3 rcc lrelease lupdate qdbuscpp2xml qdbusxml2cpp; do
		install -m 0755 bin/${i} ${D}${bindir}/${i}4
	done
    
	install -d ${D}${datadir}/qt5/
	cp -PfR mkspecs ${D}${datadir}/qt5/
	ln -sf linux-g++ ${D}${datadir}/qt5/mkspecs/${BUILD_OS}-oe-g++
	if [ -f ${D}${datadir}/qt5/mkspecs/common/g++-unix.conf ] ; then
		cp -f ${WORKDIR}/g++.conf ${D}${datadir}/qt5/mkspecs/common/g++-unix.conf
	else
		cp -f ${WORKDIR}/g++.conf ${D}${datadir}/qt5/mkspecs/common/g++.conf
	fi
	cp -f ${WORKDIR}/linux.conf ${D}${datadir}/qt5/mkspecs/common/

	install -m 0644 tools/porting/src/q3porting.xml ${D}${datadir}/qt5/

	for i in ${TOBUILD}; do
		cd ${S}/$i && oe_runmake install INSTALL_ROOT=${D}
	done
}

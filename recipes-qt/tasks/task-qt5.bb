DESCRIPTION = "Qt5 Image Feed"
PR = "r1"
LICENSE = "MIT"

LIC_FILES_CHKSUM = "file://${COREBASE}/LICENSE;md5=3f40d7994397109285ec7b81fdeb3b58 \
                    file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

inherit task

PACKAGES += " \
	${PN}-base \
"

RDEPENDS_${PN}-base = " \
	qt5-x11-free \
	libqtcore5 \
	libqtgui5 \
"

#RDEPENDS_${PN}-base = " \
#	libqt-gui5 \
#	qt5-x11-free \
#	libqt-clucene5 \
#	libqt-core5 \
#	libqt-dbus5 \
#	libqt-gui5 \
#	libqt-help5 \
#	libqt-multimedia5 \
#	libqt-network5 \
#	libqt-script5 \
#	libqt-scripttools5 \
#	libqt-sql5 \
#	libqt-svg5 \
#	libqt-test5 \
#	libqt-webkit5 \
#	libqt-xml5 \
#        qt5--demos \
#        qt5--examples \
#        qt-demo-init \
#
#RRECOMMENDS_${PN}-base = " \
#	libqt-xmlpatterns5 \
#"


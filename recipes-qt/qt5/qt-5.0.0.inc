LICENSE = "LGPLv2.1"
LIC_FILES_CHKSUM = "file://LICENSE.LGPL;md5=cc5963be04f8b19c3e3c46bc31f0f6e1"

FILESPATHS =. "${FILE_DIRNAME}/qt-${PV}:"
FILESEXTRAPATHS =. "${FILE_DIRNAME}/qt-${PV}:"

SRCREV = "d370b365daff7d3fa9927559ddfbb17a2d5f3e29"
SRC_URI = "git://gitorious.org/qt/qtbase.git;protocol=git \
           file://hack-out-pg2-4.7.0.patch \
           file://0006-freetype-host-includes.patch \
           file://add_nostrip_for_debug_packages.diff \
           file://qmake.conf.sh \
           file://qmake-build.conf.sh \
           file://qplatformdefs.h \
           file://g++-base.conf \
           file://gcc-base.conf \
           file://linux.conf"

S = "${WORKDIR}/git"

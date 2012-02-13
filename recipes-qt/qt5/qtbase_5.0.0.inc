LICENSE = "LGPLv2.1"
LIC_FILES_CHKSUM = "file://LICENSE.LGPL;md5=cc5963be04f8b19c3e3c46bc31f0f6e1"

FILESEXTRAPATHS =. "${FILE_DIRNAME}/qtbase-${PV}:"

SRCREV = "805d8959787ba03a35436e1235648d01bdfd91c7"
SRC_URI = "git://gitorious.org/qt/qtbase.git;protocol=git \
           file://g++.conf \
           file://linux.conf"
S = "${WORKDIR}/git"

#require qtbase.inc
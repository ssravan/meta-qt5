require qt5-jsbackend.inc

SRCREV = "1a03bd56a5f1a10e901166d87fe52ca2c7a18a25"
SRC_URI = "git://gitorious.org/qt/qtjsbackend.git;protocol=git"
S = "${WORKDIR}/git"

SRC_URI += "file://disable-hardfloat-runtimeerror.patch"

PR_append = ".1"


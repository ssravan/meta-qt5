SRCREV = "70adcad251ae129c15e5146c54bb3e0c11ee728f"
SRC_URI += "git://gitorious.org/qt/qtjsbackend.git;protocol=git"
S = "${WORKDIR}/git"

SRC_URI += "file://disable-hardfloat-runtimeerror.patch"

require qt5-jsbackend.inc

PR_append = ".3"


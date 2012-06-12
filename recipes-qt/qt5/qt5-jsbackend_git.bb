SRCREV = "f5ec4d8aa8ae844a7d1675ba85f416c290b1b4ea"
SRC_URI += "git://gitorious.org/qt/qtjsbackend.git;protocol=git"
S = "${WORKDIR}/git"

SRC_URI += "\
    file://disable-hardfloat-runtimeerror.patch \
    file://macro-whitespace-jsbackend.patch \
"

require qt5-jsbackend.inc

PR_append = ".7"


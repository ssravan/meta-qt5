SRCREV = "2c1bc67598c55314c226c27530398a9a7ddbf1b7"
SRC_URI += "git://gitorious.org/qt/qtjsbackend.git;protocol=git"
S = "${WORKDIR}/git"

SRC_URI += "file://disable-hardfloat-runtimeerror.patch"

require qt5-jsbackend.inc

PR_append = ".4"


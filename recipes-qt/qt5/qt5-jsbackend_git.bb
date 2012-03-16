SRCREV = "cbcc6eb7bf80bc9ad4483996ccd6d719932e0319"
SRC_URI += "git://gitorious.org/qt/qtjsbackend.git;protocol=git"
S = "${WORKDIR}/git"

SRC_URI += "file://disable-hardfloat-runtimeerror.patch"

require qt5-jsbackend.inc

PR_append = ".2"


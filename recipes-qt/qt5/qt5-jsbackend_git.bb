SRCREV = "89c7e60ca70d0ff8f26f311fa92b8109d275f6f9"
SRC_URI += "git://gitorious.org/qt/qtjsbackend.git;protocol=git"
S = "${WORKDIR}/git"

require qt5-jsbackend.inc

PR_append = ".8"


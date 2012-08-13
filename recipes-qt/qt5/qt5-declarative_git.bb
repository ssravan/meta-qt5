require qt5-declarative.inc

SRCREV = "917a2cbc76a8433e550770b1414153ab16215381"
SRC_URI += "git://gitorious.org/qt/qtdeclarative.git;protocol=git"
S = "${WORKDIR}/git"

SRC_URI += "file://qt5-declarative-accessible-plugin-installpath.patch"

PR_append = ".7"

DEFAULT_PREFERENCE = "-1"

QT_CONFIG_FLAGS_append_armv6 = " -no-neon "

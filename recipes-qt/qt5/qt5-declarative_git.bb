require qt5-declarative.inc

SRCREV = "ca6d49e6b4096f5a9737c6aee04e9b22a781aba2"
SRC_URI += "git://gitorious.org/qt/qtdeclarative.git;protocol=git"
S = "${WORKDIR}/git"

PR_append = ".6"

DEFAULT_PREFERENCE = "-1"

QT_CONFIG_FLAGS_append_armv6 = " -no-neon "

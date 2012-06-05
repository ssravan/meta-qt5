require qt5-declarative.inc

SRCREV = "e9eca3ecf778097c034eb76e930c9a7e4e3e6194"
SRC_URI += "git://gitorious.org/qt/qtdeclarative.git;protocol=git"
S = "${WORKDIR}/git"

PR_append = ".5"

DEFAULT_PREFERENCE = "-1"

QT_CONFIG_FLAGS_append_armv6 = " -no-neon "

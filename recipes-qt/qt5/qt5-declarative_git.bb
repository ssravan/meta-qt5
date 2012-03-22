require qt5-declarative.inc

SRCREV = "58e064a5dff1289bff0d304ae8798b43d67587f7"
SRC_URI += "git://gitorious.org/qt/qtdeclarative.git;protocol=git"
S = "${WORKDIR}/git"

PR_append = ".2"

DEFAULT_PREFERENCE = "-1"

QT_CONFIG_FLAGS_append_armv6 = " -no-neon "

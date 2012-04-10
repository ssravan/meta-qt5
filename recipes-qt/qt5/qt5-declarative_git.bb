require qt5-declarative.inc

SRCREV = "df2adc4a45a94c332104ef4114a8d25da21f8c98"
SRC_URI += "git://gitorious.org/qt/qtdeclarative.git;protocol=git"
S = "${WORKDIR}/git"

PR_append = ".3"

DEFAULT_PREFERENCE = "-1"

QT_CONFIG_FLAGS_append_armv6 = " -no-neon "

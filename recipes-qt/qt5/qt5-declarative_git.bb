require qt5-declarative.inc

SRCREV = "39327bbe38d90cc4ec10c9dddc5722169f454d4f"
SRC_URI = "git://gitorious.org/qt/qtdeclarative.git;protocol=git"
S = "${WORKDIR}/git"

PR_append = ".1"

DEFAULT_PREFERENCE = "-1"

QT_CONFIG_FLAGS_append_armv6 = " -no-neon "

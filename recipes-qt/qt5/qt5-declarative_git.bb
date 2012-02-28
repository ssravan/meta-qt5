require qt5-declarative.inc

SRCREV = "9593df26c4a87130947dbdacf5ddb2f7a3412cbc"
SRC_URI = "git://gitorious.org/qt/qtdeclarative.git;protocol=git"
S = "${WORKDIR}/git"

PR_append = ".0"

DEFAULT_PREFERENCE = "-1"

QT_CONFIG_FLAGS_append_armv6 = " -no-neon "

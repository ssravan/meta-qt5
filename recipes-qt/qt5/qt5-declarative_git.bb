require qt5-declarative.inc

SRCREV = "5bbb2e195b2cee8dbea0715ebf6eef41f36a3100"
SRC_URI += "git://gitorious.org/qt/qtdeclarative.git;protocol=git"
S = "${WORKDIR}/git"

PR_append = ".4"

DEFAULT_PREFERENCE = "-1"

QT_CONFIG_FLAGS_append_armv6 = " -no-neon "

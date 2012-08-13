require qt5-xmlpatterns.inc

SRCREV = "ec2ad53d9b1b2abc435b593723441081811aebb4"
SRC_URI = "git://gitorious.org/qt/qtxmlpatterns.git;protocol=git"
S = "${WORKDIR}/git"

PR_append = ".6"

DEFAULT_PREFERENCE = "-1"


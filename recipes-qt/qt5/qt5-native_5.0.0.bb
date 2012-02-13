require qt5-native.inc

PR = "${INC_PR}.0"

DEFAULT_PREFERENCE = "-1"

# Find the mkspec configuration files in the right directory.
FILESEXTRAPATHS =. "${FILE_DIRNAME}/qt-${PV}:"

TOBUILD := "src/tools/bootstrap ${TOBUILD}"

DESCRIPTION = "Helper file for Qt base libraries"
INC_PR = "r1"

require qtbase_${PV}.inc
EXTRA_OECONF += "-nomake examples -nomake tests"

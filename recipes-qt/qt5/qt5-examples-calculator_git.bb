inherit qmake2

DEPENDS += "qt5-declarative"

LICENSE = "LGPLv2.1"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/LGPL-2.1;md5=1a6d268fd218675ffea8be556788b780"

SRCREV = "e9eca3ecf778097c034eb76e930c9a7e4e3e6194"
SRC_URI = "git://gitorious.org/qt/qtdeclarative.git;protocol=git"
S = "${WORKDIR}/git"

PR = "r3"

FILES_${PN} += "\
    /usr/local/qt5/examples/qtdeclarative/demos/calculator/calculator \
    /usr/local/qt5/examples/qtdeclarative/demos/calculator/*.qml \
    /usr/local/qt5/examples/qtdeclarative/demos/calculator/CalculatorCore \
"

FILES_${PN}-dbg += "/usr/local/qt5/examples/qtdeclarative/demos/calculator/.debug"
FILES_${PN}-dev += "/usr/local/qt5/examples/qtdeclarative/demos/calculator"

do_configure () {
    :
}

do_compile () {
    pushd examples/demos/calculator
    qmake2
    oe_runmake
    popd
}

do_install() {
    pushd examples/demos/calculator
    oe_runmake install INSTALL_ROOT="${D}"
    popd
}

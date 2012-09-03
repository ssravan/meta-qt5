inherit qmake2

DEPENDS += "qt5-declarative"

LICENSE = "LGPLv2.1"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/LGPL-2.1;md5=1a6d268fd218675ffea8be556788b780"

SRCREV = "917a2cbc76a8433e550770b1414153ab16215381"
SRC_URI = "git://gitorious.org/qt/qtdeclarative.git;protocol=git"
S = "${WORKDIR}/git"

PR = "r6"

FILES_${PN} += "\
    /usr/local/qt5/examples/qtdeclarative/demos/calqlatr/calqlatr \
    /usr/local/qt5/examples/qtdeclarative/demos/calqlatr/*.qml \
    /usr/local/qt5/examples/qtdeclarative/demos/calqlatr/content \
"

FILES_${PN}-dbg += "/usr/local/qt5/examples/qtdeclarative/demos/calqlatr/.debug"
FILES_${PN}-dev += "/usr/local/qt5/examples/qtdeclarative/demos/calqlatr"

do_configure () {
    :
}

do_compile () {
    pushd examples/demos/calqlatr
    qmake2
    oe_runmake
    popd
}

do_install() {
    pushd examples/demos/calqlatr
    oe_runmake install INSTALL_ROOT="${D}"
    popd
}

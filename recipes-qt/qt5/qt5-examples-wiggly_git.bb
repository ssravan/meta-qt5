inherit qmake2

require qt-5.0.0.inc

DEPENDS += "qt5-x11-free"

SRC_URI = "git://gitorious.org/qt/qtbase.git;protocol=git"

PR = "r2"

FILES_${PN} += "/usr/local/qt5/examples/qtbase/widgets/wiggly/wiggly"
FILES_${PN}-dbg += "/usr/local/qt5/examples/qtbase/widgets/wiggly/.debug"
FILES_${PN}-dev += "/usr/local/qt5/examples/qtbase/widgets/wiggly"

do_configure () {
    :
}

do_compile () {
    pushd examples/widgets/wiggly
    qmake2
    oe_runmake
    popd
}

do_install() {
    pushd examples/widgets/wiggly
    oe_runmake install INSTALL_ROOT="${D}"
    popd
}

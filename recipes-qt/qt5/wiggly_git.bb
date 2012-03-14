inherit qmake2

require qt-5.0.0.inc

SRC_URI = "git://gitorious.org/qt/qtbase.git;protocol=git"

PR = "r1"

FILES_${PN} += "/usr/local/qt5/examples/qtbase/widgets/wiggly/wiggly"

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

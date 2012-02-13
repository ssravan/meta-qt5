DEPENDS_prepend = "${@["qt5-x11-free ", ""][(d.getVar('BPN', True)[:12] == 'qt5-x11-free')]}"

inherit qmake2

QT_BASE_NAME = "qt5"
QT_DIR_NAME = "qt5"
QT_LIBINFIX = ""

# Qt uses atomic instructions not supported in thumb mode
ARM_INSTRUCTION_SET = "arm"

#
# QMake variables for Qt
#
inherit qmake_base

DEPENDS_prepend = "qt5-tools-native "

export QMAKESPEC = "${STAGING_DATADIR_NATIVE}/qt5/mkspecs/${TARGET_OS}-oe-g++"
export OE_QMAKE_UIC = "${STAGING_BINDIR_NATIVE}/uic5"
export OE_QMAKE_MOC = "${STAGING_BINDIR_NATIVE}/moc5"
export OE_QMAKE_RCC = "${STAGING_BINDIR_NATIVE}/rcc5"
export OE_QMAKE_QMAKE = "${STAGING_BINDIR_NATIVE}/qmake2"
export OE_QMAKE_LINK = "${CXX}"
export OE_QMAKE_CXXFLAGS = "${CXXFLAGS}"
export OE_QMAKE_INCDIR_QT = "${STAGING_INCDIR}/qt5"
export OE_QMAKE_LIBDIR_QT = "${STAGING_LIBDIR}"
export OE_QMAKE_LIBS_QT = "qt"
export OE_QMAKE_LIBS_X11 = "-lXext -lX11 -lm"
export OE_QMAKE_LIBS_X11SM = "-lSM -lICE"
export OE_QMAKE_LRELEASE = "${STAGING_BINDIR_NATIVE}/lrelease5"
export OE_QMAKE_LUPDATE = "${STAGING_BINDIR_NATIVE}/lupdate5"

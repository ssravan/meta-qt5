require qt5.inc

DESCRIPTION = "Qt is a cross-platform application framework"
HOMEPAGE = "http://qt.nokia.com"
SECTION = "x11/libs"

INC_PR = "r2"

DEPENDS += "virtual/libgl virtual/libx11 \
             fontconfig libxft libxext libxrender libxrandr libxcursor \
             libxcb xcb-util xcb-util-wm xcb-util-image xcb-util-keysyms"
RDEPENDS += "libx11-xcb libxcb xcb-util xcb-util-wm xcb-util-image xcb-util-keysyms"

QT_CONFIG_FLAGS += "-xcb -no-xinerama -no-xkb"
QT_BASE_LIB  ?= "libqt"

inherit qt5x11


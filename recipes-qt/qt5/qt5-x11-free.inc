DESCRIPTION = "Qt is a cross-platform application framework"
HOMEPAGE = "http://qt.nokia.com"
SECTION = "x11/libs"

INC_PR = "r4"

DEPENDS += "virtual/libx11 \
             fontconfig libxft libxext libxrender libxrandr libxcursor \
             libxcb xcb-util xcb-util-wm xcb-util-image xcb-util-keysyms"
RDEPENDS += "libx11-xcb libxcb xcb-util xcb-util-wm xcb-util-image xcb-util-keysyms"

QT_PLATFORMFLAGS = "-xcb -no-xinerama -no-xkb"
QT_PLATFORMFLAGS_armv7a = "-eglfs -opengl es2 -no-dbus"

QT_GLDEPENDS = "virtual/libgl"
QT_GLDEPENDS_armv7a = "virtual/egl"

require qt5.inc
inherit qt5x11


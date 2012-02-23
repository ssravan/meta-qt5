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

do_install_append() {
  # fix pkgconfig, libtool and prl files
  sed -i -e 's#I/usr/include#Iincludedir}#g' \ 
    -e 's#Iin#I${in#g' \
    ${D}${libdir}/*.la ${D}${libdir}/*.prl ${D}${libdir}/pkgconfig/*.pc

  # Qt abuses $includedir to point to its headers, which breaks pkgconfig sysroot, so
  # manually fix it up here:
  for pc in ${D}${libdir}/pkgconfig/*.pc ; do
    sed -i -e "s:prefix}include/${QT_BASE_NAME}/$(basename $pc .pc):prefix}/include:" \
      -e "s,Cflags: ,Cflags: -IP{includedir}/${QT_BASE_NAME}/$(basename $pc .pc) ," \
      -e 's:IP{:I${:g' $pc
  done
}

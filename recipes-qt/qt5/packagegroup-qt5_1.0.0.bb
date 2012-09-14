DESCRIPTION = "Qt5 packages for the nimbus distro"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/LICENSE;md5=3f40d7994397109285ec7b81fdeb3b58"
PR = "r0"

inherit packagegroup

RDEPENDS = "\
  qt5-libcore \
  qt5-libgui \
  qt5-libnetwork \
  qt5-libopengl \
  qt5-fonts \
  qt5-fonts-ttf-dejavu \
  qt5-fonts-ttf-vera \
  qt5-plugin-platforms-xcb \
  qt5-declarative \
  qt5-jsbackend \
  qt5-xmlpatterns \
"

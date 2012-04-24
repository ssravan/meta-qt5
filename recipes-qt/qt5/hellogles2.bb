DESCRIPTION = "Test application for OpenGL ES 2"
LICENSE = "unknown"
LIC_FILES_CHKSUM = "file://${PN}.c;endline=3;md5=c285c12ebbc688f86180e40b2e3246d7"
DEPENDS = "virtual/egl"
PROVIDES = "hellogles2"

PR = "r0"
S = "${WORKDIR}"

SRC_URI = "file://${PN}.c"

do_compile () {
    ${CC} ${CFLAGS} ${LDFLAGS} ${PN}.c -lGLESv2 -lEGL -lX11 -o ${PN} 
}

do_install () {
    mkdir -p "${D}${bindir}/"
    install -m 0755 "${S}/${PN}" "${D}${bindir}/"
}

FILES_${PN} = "${bindir}/${PN}"

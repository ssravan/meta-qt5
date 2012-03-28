inherit qmake2

PR_append = ".5"

DEPENDS += "freetype jpeg libpng zlib dbus openssl glib-2.0 gstreamer gst-plugins-base sqlite3"

require qt5_arch.inc
QT_ARCH := "${@qt5_arch(d)}"
QT_ENDIAN = "${@qt5_endian(d)}"

QT_GLFLAGS ?= ""
QT_BASE_LIB ?= "qt5-lib"

QT_CONFIG_FLAGS += "\
    -reduce-relocations                         \
    -shared -no-nas-sound -no-nis               \
    -release -separate-debug-info               \
    -system-libjpeg -system-libpng -system-zlib \
    -stl -no-rpath                              \
    ${QT_GLFLAGS}                               \
"

EXTRA_OEMAKE = ""

# Library packages
QT_LIB_NAMES = "QtCore QtDBus QtDesigner QtDesignerComponents QtGui QtWidgets QtHelp QtNetwork QtOpenGL QtScript QtScriptTools QtSql QtSvg QtTest QtUiTools QtWebKit QtXml QtOpenVG QtConcurrent QtPrintSupport QtPlatformSupport"

QT_EXTRA_LIBS = "pvrQWSWSEGL"

python __anonymous () {
    import bb

    lib_packages = []
    dev_packages = []
    dbg_packages = []

    for name in d.getVar("QT_LIB_NAMES", 1).split():
        pkg = d.getVar("QT_BASE_LIB", True) + name.lower().replace("qt", "").replace("_", "-")
       # NOTE: the headers for QtAssistantClient are different
        incname = name.replace("QtAssistantClient", "QtAssistant")
        d.setVar("FILES_%s" % pkg, "${libdir}/lib%(name)s${QT_LIBINFIX}.so.*" % locals())
        d.setVar("FILES_%s-dev" % pkg, """${libdir}/lib%(name)s${QT_LIBINFIX}.prl
                  ${libdir}/lib%(name)s${QT_LIBINFIX}.a
                  ${libdir}/lib%(name)s${QT_LIBINFIX}.la
                  ${libdir}/lib%(name)s${QT_LIBINFIX}.so
                  ${includedir}/${QT_DIR_NAME}/%(incname)s
                  ${libdir}/pkgconfig/%(name)s${QT_LIBINFIX}.pc""" % locals())
        d.setVar("FILES_%s-dbg" % pkg, "${libdir}/.debug/lib%(name)s${QT_LIBINFIX}.so*" % locals())
        d.setVar("RRECOMMENDS_%s-dbg" % pkg, "${PN}-dbg")
        lib_packages.append(pkg)
        dev_packages.append("%s-dev" % pkg)
        dbg_packages.append("%s-dbg" % pkg)

    for name in d.getVar("OTHER_PACKAGES", 1).split():
        dbg_packages.append("%s-dbg" % name)

    for name in d.getVar("QT_EXTRA_LIBS", 1).split():
        pkg = d.getVar("QT_BASE_LIB", True) + name.lower().replace("qt", "").replace("_", "-") + "5"
        d.setVar("FILES_%s" % pkg, "${libdir}/lib%(name)s.so.*" % locals())
        d.setVar("FILES_%s-dev" % pkg, """${libdir}/lib%(name)s.prl
                  ${libdir}/lib%(name)s.a
                  ${libdir}/lib%(name)s.la
                  ${libdir}/lib%(name)s.so
                  ${includedir}/${QT_DIR_NAME}/%(incname)s
                  ${libdir}/pkgconfig/%(name)s.pc""" % locals())
        d.setVar("FILES_%s-dbg" % pkg, "${libdir}/.debug/lib%(name)s.so*" % locals())
        d.setVar("RRECOMMENDS_%s-dbg" % pkg, "${PN}-dbg")
        lib_packages.append(pkg)
        dev_packages.append("%s-dev" % pkg)
        dbg_packages.append("%s-dbg" % pkg)

    d.setVar("LIB_PACKAGES", " ".join(lib_packages))
    d.setVar("DEV_PACKAGES", " ".join(dev_packages))
    d.setVar("DBG_PACKAGES", " ".join(dbg_packages))
}

OTHER_PACKAGES = "\
             ${QT_BASE_NAME}-tools \
             ${QT_BASE_NAME}-assistant \
             ${QT_BASE_NAME}-common \
             ${QT_BASE_NAME}-dbus \
             ${QT_BASE_NAME}-demos \
             ${QT_BASE_NAME}-designer \
             ${QT_BASE_NAME}-examples \
             ${QT_BASE_NAME}-fonts \
             ${QT_BASE_NAME}-fonts-ttf-vera \
             ${QT_BASE_NAME}-fonts-ttf-dejavu \
             ${QT_BASE_NAME}-fonts-pfa \
             ${QT_BASE_NAME}-fonts-pfb \
             ${QT_BASE_NAME}-fonts-qpf \
             ${QT_BASE_NAME}-linguist \
             ${QT_BASE_NAME}-makeqpf \
             ${QT_BASE_NAME}-mkspecs \
             ${QT_BASE_NAME}-pixeltool \
             ${QT_BASE_NAME}-qmlviewer \
             ${QT_BASE_NAME}-qml-plugins"

#We prepend so ${QT_BASE_NAME}-demos-doc comes before ${PN}-doc,so the packaging of FILES_ get done before.
PACKAGES =+ "${QT_BASE_NAME}-demos-doc"
PACKAGES += "${LIB_PACKAGES} ${DEV_PACKAGES} ${DBG_PACKAGES} ${OTHER_PACKAGES}"
PACKAGES_DYNAMIC = "${QT_BASE_NAME}-plugin-* ${QT_BASE_NAME}-translation-* ${QT_BASE_NAME}-phrasebook-* ${QT_BASE_NAME}-fonts-*"

ALLOW_EMPTY_${PN} = "1"
ALLOW_EMPTY_${QT_BASE_NAME}-fonts = "1"
FILES_${PN}     = ""
FILES_${PN}-dev += "${includedir}/${QT_DIR_NAME}/Qt ${libdir}/cmake"
FILES_${PN}-dbg += "${exec_prefix}/src/debug"
FILES_${QT_BASE_NAME}-demos-doc = "${docdir}/qtopia/qch/qt.qch"
RRECOMMENDS_${PN} = "${LIB_PACKAGES} ${OTHER_PACKAGES}"
RRECOMMENDS_${PN}-dev = "${DEV_PACKAGES}"
RRECOMMENDS_${PN}-dbg = "${DBG_PACKAGES}"
RRECOMMENDS_${QT_BASE_NAME}-fonts = " \
             ${QT_BASE_NAME}-fonts-ttf-vera \
             ${QT_BASE_NAME}-fonts-ttf-dejavu \
             ${QT_BASE_NAME}-fonts-pfa \
             ${QT_BASE_NAME}-fonts-pfb \
             ${QT_BASE_NAME}-fonts-qpf"
RRECOMMENDS_${QT_BASE_NAME}-demos += " \
            ${QT_BASE_NAME}-fonts \
            ${QT_BASE_NAME}-examples \
            ${QT_BASE_NAME}-plugin-sqldriver-sqlite \
            ${QT_BASE_NAME}-plugin-imageformat-jpeg \
            ${QT_BASE_NAME}-qml-plugins \
            ${QT_BASE_NAME}-assistant \
            ${QT_BASE_NAME}-demos-doc"
RRECOMMENDS_${QT_BASE_NAME}-examples += " \
            ${QT_BASE_NAME}-plugin-sqldriver-sqlite \
            ${QT_BASE_NAME}-plugin-imageformat-jpeg \
            ${QT_BASE_NAME}-qml-plugins"
RRECOMMENDS_${QT_BASE_NAME}-qmlviewer += " \
            ${QT_BASE_NAME}-qml-plugins"
RRECOMMENDS_${QT_BASE_NAME}-doc += " \
            ${QT_BASE_NAME}-demos-doc"

FILES_${QT_BASE_NAME}-tools                = "${bindir}/qttracereplay ${bindir}/qdoc* ${bindir}/moc ${bindir}/uic* ${bindir}/rcc"
FILES_${QT_BASE_NAME}-tools-dbg            = "${bindir}/.debug/qttracereplay ${bindir}/.debug/qdoc* ${bindir}/.debug/uic* ${bindir}/.debug/moc ${bindir}/.debug/rcc"
FILES_${QT_BASE_NAME}-assistant            = "${bindir}/*assistant* ${bindir}/qcollectiongenerator ${bindir}/qhelpconverter ${bindir}/qhelpgenerator"
FILES_${QT_BASE_NAME}-assistant-dbg        = "${bindir}/.debug/*assistant* ${bindir}/.debug/qcollectiongenerator ${bindir}/.debug/qhelpconverter ${bindir}/.debug/qhelpgenerator"
FILES_${QT_BASE_NAME}-common               = "${bindir}/qtconfig"
FILES_${QT_BASE_NAME}-common-dbg           = "${bindir}/.debug/qtconfig"
FILES_${QT_BASE_NAME}-dbus                 = "${bindir}/qdbus ${bindir}/qdbusxml2cpp ${bindir}/qdbuscpp2xml ${bindir}/qdbusviewer"
FILES_${QT_BASE_NAME}-dbus-dbg             = "${bindir}/.debug/qdbus ${bindir}/.debug/qdbusxml2cpp ${bindir}/.debug/qdbuscpp2xml ${bindir}/.debug/qdbusviewer"
FILES_${QT_BASE_NAME}-demos                = "${bindir}/qtdemo* ${bindir}/${QT_DIR_NAME}/demos/*"
FILES_${QT_BASE_NAME}-demos-dbg            = "${bindir}/.debug/qtdemo* ${bindir}/${QT_DIR_NAME}/demos/.debug/*  ${bindir}/${QT_DIR_NAME}/demos/*/.debug  ${bindir}/${QT_DIR_NAME}/demos/*/*/.debug  ${bindir}/${QT_DIR_NAME}/demos/*/*/*/.debug"
FILES_${QT_BASE_NAME}-designer             = "${bindir}/*designer*"
FILES_${QT_BASE_NAME}-designer-dbg         = "${bindir}/.debug/*designer*"
FILES_${QT_BASE_NAME}-examples             = "/usr/local/${QT_DIR_NAME}/examples"
FILES_${QT_BASE_NAME}-examples-dbg         = "/usr/local/${QT_DIR_NAME}/examples/.debug /usr/local/${QT_DIR_NAME}/examples/*/.debug /usr/local/${QT_DIR_NAME}/examples/*/*/.debug /usr/local/${QT_DIR_NAME}/examples/*/*/*/.debug /usr/local/${QT_DIR_NAME}/examples/*/*/*/*/.debug /usr/local/${QT_DIR_NAME}/examples/declarative/*/*/*/*/*/.debug/* /usr/local/${QT_DIR_NAME}/examples/declarative/*/*/*/*/.debug/*"
FILES_${QT_BASE_NAME}-fonts-ttf-vera       = "${libdir}/fonts/Vera*.ttf"
FILES_${QT_BASE_NAME}-fonts-ttf-dejavu     = "${libdir}/fonts/DejaVu*.ttf"
FILES_${QT_BASE_NAME}-fonts-pfa            = "${libdir}/fonts/*.pfa"
FILES_${QT_BASE_NAME}-fonts-pfb            = "${libdir}/fonts/*.pfb"
FILES_${QT_BASE_NAME}-fonts-qpf            = "${libdir}/fonts/*.qpf*"
FILES_${QT_BASE_NAME}-fonts                = "${libdir}/fonts/README ${libdir}/fonts/fontdir"
FILES_${QT_BASE_NAME}-linguist             = "${bindir}/*linguist* ${bindir}/lrelease ${bindir}/lupdate ${bindir}/lconvert ${bindir}/qm2ts"
FILES_${QT_BASE_NAME}-linguist-dbg         = "${bindir}/.debug/*linguist* ${bindir}/.debug/lrelease ${bindir}/.debug/lupdate ${bindir}/.debug/lconvert ${bindir}/.debug/qm2ts"
FILES_${QT_BASE_NAME}-pixeltool            = "${bindir}/pixeltool"
FILES_${QT_BASE_NAME}-pixeltool-dbg        = "${bindir}/.debug/pixeltool"
FILES_${QT_BASE_NAME}-qmlviewer            = "${bindir}/qmlviewer"
FILES_${QT_BASE_NAME}-qmlviewer-dbg        = "${bindir}/.debug/qmlviewer"
FILES_${QT_BASE_NAME}-makeqpf              = "${bindir}/makeqpf"
FILES_${QT_BASE_NAME}-makeqpf-dbg          = "${bindir}/.debug/makeqpf"
FILES_${QT_BASE_NAME}-mkspecs              = "${datadir}/${QT_DIR_NAME}/mkspecs"
FILES_${QT_BASE_NAME}-qml-plugins          = "${libdir}/${QT_DIR_NAME}/imports/* ${libdir}/${QT_DIR_NAME}/plugins/qmltooling/*"
FILES_${QT_BASE_NAME}-qml-plugins-dbg      = "${libdir}/${QT_DIR_NAME}/imports/*/*/*/.debug/* ${libdir}/${QT_DIR_NAME}/imports/*/.debug ${libdir}/${QT_DIR_NAME}/plugins/qmltooling/.debug"

do_configure() {
    unset QMAKESPEC
    unset QTDIR
    unset LD
    unset CC
    unset CXX
    unset CFLAGS
    unset CXXFLAGS
    unset RANLIB
    unset OBJDUMP
    unset CCLD
    unset OE_QMAKE_UIC
    unset OE_QMAKE_MOC
    unset OE_QMAKE_RCC
    unset OE_QMAKE_QMAKE

    mkdir -p mkspecs/${TARGET_OS}-oe-g++
    cp -f ${WORKDIR}/qplatformdefs.h mkspecs/${TARGET_OS}-oe-g++
    bash ${WORKDIR}/qmake.conf.sh > mkspecs/${TARGET_OS}-oe-g++/qmake.conf

    mkdir -p mkspecs/build-oe-g++
    cp -f ${WORKDIR}/qplatformdefs.h mkspecs/build-oe-g++
    bash ${WORKDIR}/qmake-build.conf.sh > mkspecs/build-oe-g++/qmake.conf

    ./configure -v \
        -opensource -confirm-license \
        -prefix ${prefix} \
        -hostprefix ${STAGING_DIR_NATIVE}${prefix} \
        -hostdatadir ${STAGING_DATADIR_NATIVE}/${QT_DIR_NAME} \
        -datadir ${datadir}/${QT_DIR_NAME} \
        -sysconfdir ${sysconfdir}/${QT_DIR_NAME} \
        -docdir ${docdir}/${QT_DIR_NAME} \
        -headerdir ${STAGING_DIR_TARGET}${includedir}/${QT_DIR_NAME} \
        -plugindir ${libdir}/${QT_DIR_NAME}/plugins \
        -importdir ${libdir}/${QT_DIR_NAME}/imports \
        -translationdir ${datadir}/${QT_DIR_NAME}/translations \
        -examplesdir /usr/local/${QT_DIR_NAME}/examples \
        -platform build-oe-g++ \
        -xplatform ${TARGET_OS}-oe-g++ \
        -arch ${QT_ARCH} \
        -nomake tests \
        ${QT_CONFIG_FLAGS} -no-fast
}

python populate_packages_prepend() {
        translation_dir = bb.data.expand('${datadir}/${QT_DIR_NAME}/translations/', d)
        translation_name = bb.data.expand('${QT_BASE_NAME}-translation-%s', d)
        import os;
        if os.path.exists("%s%s" % (bb.data.expand('${D}',d), translation_dir)):
            do_split_packages(d, translation_dir, '^(assistant|designer|linguist|qt|qtconfig|qvfb)_(.*)\.qm$', translation_name, '${PN} translation for %s', extra_depends='' )
        else:
            bb.note("The path does not exist:", bb.data.expand('${D}', d), translation_dir)
 
        phrasebook_dir = bb.data.expand('${datadir}/${QT_DIR_NAME}/phrasebooks/', d)
        phrasebook_name = bb.data.expand('${QT_BASE_NAME}-phrasebook-%s', d)
        if os.path.exists("%s%s" % (bb.data.expand('${D}',d), phrasebook_dir)):
                do_split_packages(d, phrasebook_dir, '^(.*)\.qph$', phrasebook_name, '${PN} phrasebook for %s', extra_depends='' )
        else:
                bb.note("The path does not exist:", bb.data.expand('${D}', d), phrasebook_dir)
 
        # Package all the plugins and their -dbg version and create a meta package
        def qtopia_split(path, name, glob):
                """
                Split the package into a normal and -dbg package and then add the
                new packages to the meta package.
                """
                plugin_dir = bb.data.expand('${libdir}/${QT_DIR_NAME}/plugins/%s/' % path, d)
                if not os.path.exists("%s%s" % (bb.data.expand('${D}',d), plugin_dir)):
                        bb.note("The path does not exist:", bb.data.expand('${D}', d), plugin_dir)
                        return
 
                plugin_name = bb.data.expand('${QT_BASE_NAME}-plugin-%s-%%s' % name, d)
                dev_packages = []
                dev_hook = lambda file,pkg,b,c,d:dev_packages.append((file,pkg))
                do_split_packages(d, plugin_dir, glob, plugin_name, '${PN} %s for %%s' % name, extra_depends='', hook=dev_hook)
                # Create a -dbg package as well
                plugin_dir_dbg = bb.data.expand('${libdir}/${QT_DIR_NAME}/plugins/%s/.debug' % path, d)
                packages = d.getVar('PACKAGES')
                for (file,package) in dev_packages:
                        packages = "%s %s-dbg" % (packages, package)
                        file_name = os.path.join(plugin_dir_dbg, os.path.basename(file))
                        d.setVar("FILES_%s-dbg" % package, file_name)
                        d.setVar("DESCRIPTION_%s-dbg" % package, "${PN} %s for %s" % (name, package))

                d.setVar('PACKAGES', packages)

        qtopia_split('accessible',    'accessible',    '^libq(.*)\.so$')
        qtopia_split('bearer',        'bearer',        '^libq(.*)bearer\.so$')
        qtopia_split('codecs',        'codec',         '^libq(.*)\.so$')
        qtopia_split('decorations',   'decoration',    '^libqdecoration(.*)\.so$')
        qtopia_split('designer',      'designer',      '^lib(.*)\.so$')
        qtopia_split('generic',       'generic',       '^libq(.*)\.so$')
        qtopia_split('gfxdrivers',    'gfxdriver',     '^libq(.*)\.so$')
        qtopia_split('graphicssystems','graphicssystems', '^libq(.*)\.so$')
        qtopia_split('mousedrivers',  'mousedriver',   '^libq(.*)mousedriver\.so$')
        qtopia_split('iconengines',   'iconengine',    '^libq(.*)\.so$')
        qtopia_split('imageformats',  'imageformat',   '^libq(.*)\.so$')
        qtopia_split('inputmethods',  'inputmethod',   '^libq(.*)\.so$')
        qtopia_split('platforms',     'platforms',     '^lib(.*)\.so$')
        qtopia_split('sqldrivers',    'sqldrivers',    '^libq(.*)\.so$')
        qtopia_split('script',        'script',        '^libqtscript(.*)\.so$')
        qtopia_split('styles',        'style',         '^libq(.*)\.so$')
        qtopia_split('phonon_backend','phonon-backend','^libphonon_(.*)\.so$')
}

do_compile() {
    unset QMAKESPEC
    unset QTDIR
    unset LD
    unset CC
    unset CXX
    unset CFLAGS
    unset CXXFLAGS
    unset RANLIB
    unset OBJDUMP
    unset CCLD

    oe_runmake
}

do_compile_prepend() {
    unset QMAKESPEC
    unset QTDIR
    unset LD
    unset CC
    unset CXX
    unset CFLAGS
    unset CXXFLAGS
    unset RANLIB
    unset OBJDUMP
    unset CCLD

    for i in bootstrap rcc moc uic; do
        oe_runmake -C src/tools/${i}
    done

    install -d ${STAGING_BINDIR_NATIVE}
    install -m 0755 bin/qmake ${STAGING_BINDIR_NATIVE}/qmake2
    for i in moc uic rcc ; do
        install -m 0755 bin/${i} ${STAGING_BINDIR_NATIVE}/${i}5
    done

    (cd ${STAGING_BINDIR_NATIVE}; \
    ln -sf qmake2 qmake; \
    for i in moc uic rcc; do \
        ln -sf ${i}5 ${i}; \
    done)
}

do_install() {
  	oe_runmake install INSTALL_ROOT=${D}
}

do_install_append() {
    rsync -av ${D}${STAGING_DIR_NATIVE}/ ${STAGING_DIR_NATIVE}
    rm -r ${D}${STAGING_DIR_NATIVE}

    rsync -av ${D}${STAGING_DIR_TARGET}/* ${D}
    rm -r ${D}${STAGING_DIR_TARGET}

    rsync -av lib/fonts ${D}${libdir}
}

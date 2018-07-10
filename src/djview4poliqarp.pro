# #####################################################################
# Automatically generated by qmake (2.01a) czw. sie 27 19:06:01 2009
# #####################################################################
TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += .
QT += network xml opengl widgets
CONFIG += c++11
RESOURCES = resources.qrc

TRANSLATIONS = i18n/pl.ts

win32 {
  RC_FILE = windows.rc
  MXE_TARGET=$$(MXE_TARGET)
  defined(MXE_TARGET, var) {
    # additional config for cross-compilation for Windows
    message(Cross compilation target: $$MXE_TARGET)
    QMAKE_LFLAGS += -static -static-libgcc -static-libstdc++
    QMAKE_LIBS += $$system($$MXE_TARGET-pkg-config ddjvuapi --libs)
    QMAKE_CFLAGS += $$system($$MXE_TARGET-pkg-config ddjvuapi --cflags)
    QMAKE_CXXFLAGS += $$system($$MXE_TARGET-pkg-config ddjvuapi --cflags)
  } else {
    # additional config for native compilation on Windows
    LIBS += "C:\Program Files (x86)\DjVuLibre\libdjvulibre.lib"
  }
}

macx {
  ICON = images/application.icns
  LIBS += /usr/local/lib/libdjvulibre.dylib
}

unix:!macx {
  LIBS = -ldjvulibre
  HGID = $$system(git rev-parse --short HEAD)
  DEFINES += HGID=\\\"$$HGID\\\"

  versiontarget.target = version.o
  versiontarget.depends = FORCE
  PRE_TARGETDEPS += version.o
  QMAKE_EXTRA_TARGETS += versiontarget
}

# Input
HEADERS += recentfiles.h \
	 mainwindow.h \
	 qdjvuwidget.h \
	 qdjvunet.h \
	 qdjvu.h \
	 messagedialog.h \
	 poliqarpwidget.h \
	 poliqarp.h \
	 djvulink.h \
	 preferencesdialog.h \
	 djvuitemlist.h \
	 version.h \
	 djvupreview.h \
	 djvuwidget.h \
	 logdialog.h \
	 replyparser.h \
	 poliqarpsettingsdialog.h \
	 helpdialog.h \
    aligneditemdelegate.h \
    textresultwidget.h \
    indexwidget.h \
    entryindexdialog.h \
    log.h \
    entry.h \
    history.h \
    indexmodel.h \
    entrylist.h \
    replacelineedit.h \
    replacements.h \
    replacetextedit.h
SOURCES += recentfiles.cpp \
	 mainwindow.cpp \
	 main.cpp \
	 qdjvuwidget.cpp \
	 qdjvunet.cpp \
	 qdjvu.cpp \
	 messagedialog.cpp \
	 poliqarpwidget.cpp \
	 poliqarp.cpp \
	 djvulink.cpp \
	 preferencesdialog.cpp \
	 djvuitemlist.cpp \
	 version.cpp \
	 djvupreview.cpp \
	 djvuwidget.cpp \
	 logdialog.cpp \
	 replyparser.cpp \
	 poliqarpsettingsdialog.cpp \
	 helpdialog.cpp \
    aligneditemdelegate.cpp \
    textresultwidget.cpp \
    indexwidget.cpp \
    entryindexdialog.cpp \
    log.cpp \
    entry.cpp \
    indexmodel.cpp \
    entrylist.cpp \
    replacelineedit.cpp \
    replacements.cpp \
    replacetextedit.cpp
FORMS = mainwindow.ui \
	 poliqarpwidget.ui \
	 preferencesdialog.ui \
	 logdialog.ui \
	 poliqarpsettingsdialog.ui \
	 helpdialog.ui \
    indexwidget.ui \
    entryindexdialog.ui


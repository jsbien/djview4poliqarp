# #####################################################################
# Automatically generated by qmake (2.01a) czw. sie 27 19:06:01 2009
# #####################################################################
TEMPLATE = app
TARGET =
DEPENDPATH += .
INCLUDEPATH += .
QT += network xml opengl

RESOURCES = resources.qrc
RC_FILE = windows.rc

TRANSLATIONS = i18n/pl.ts

win32:LIBS = /home/michal/programming/build/djvulibre-windows/libdjvulibre.dll.a
unix:LIBS = -ldjvulibre

unix:!macx  {

HGID = $$system(hg id -n)
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
    aligneditemdelegate.h
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
    aligneditemdelegate.cpp
FORMS = mainwindow.ui \
	 poliqarpwidget.ui \
	 preferencesdialog.ui \
	 logdialog.ui \
	 poliqarpsettingsdialog.ui \
	 helpdialog.ui


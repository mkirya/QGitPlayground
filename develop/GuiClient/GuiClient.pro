#-------------------------------------------------
#
# Project created by QtCreator 2011-08-16T12:29:22
#
#-------------------------------------------------

QT       += core gui

TARGET = GuiClient
TEMPLATE = app

INCLUDEPATH += .. ../libqgit2 ../libqgit2/src ../libqgit2/libgit2 ../libqgit2/libgit2/include ../libqgit2/libgit2/src

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libqgit2/release/ -llibqgit2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libqgit2/debug/ -llibqgit2
else:unix:!symbian: LIBS += -L$$OUT_PWD/../libqgit2/ -llibqgit2

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libqgit2/release/libqgit2.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libqgit2/debug/libqgit2.lib
else:unix:!symbian: {
    PRE_TARGETDEPS += $$OUT_PWD/../libqgit2/liblibqgit2.a
}

LIBS += -lz


SOURCES += main.cpp\
    MainWindow.cpp \
    RepositoryWidget.cpp

HEADERS += \
    MainWindow.h \
    RepositoryWidget.h

FORMS += \
    MainWindow.ui \
    RepositoryWidget.ui

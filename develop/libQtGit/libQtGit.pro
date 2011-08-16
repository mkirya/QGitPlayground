#-------------------------------------------------
#
# Project created by QtCreator 2011-08-16T15:45:47
#
#-------------------------------------------------

QT       -= gui

TARGET = libQtGit
TEMPLATE = lib
CONFIG += staticlib

SOURCES += LibQtGit.cpp \
    GitRepository.cpp

HEADERS += LibQtGit.h \
    GitRepository.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

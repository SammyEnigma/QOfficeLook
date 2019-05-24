#-------------------------------------------------
#
# Project created by QtCreator 2015-04-15T14:27:11
#
#-------------------------------------------------

QT       += widgets

CONFIG += app

CONFIG(app) {
    warning(App config)

    TEMPLATE = app

    QT += core gui
    DEFINES += QOFFICELOOK_TEST

    HEADERS       = qofficelook.h \
                    qofficelooktest.h \
                    ol_windowtitlebar.h \
                    ol_flatbutton.h \
                    ol_frame.h

    SOURCES       = main.cpp \
                    qofficelook.cpp \
                    qofficelooktest.cpp \
                    ol_windowtitlebar.cpp \
                    ol_flatbutton.cpp \
                    ol_frame.cpp

    win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/ -lQRibbon
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/ -lQRibbond
    else:unix: LIBS += -L$$PWD/../lib/ -lQRibbon

    INCLUDEPATH += $$PWD/../include
    DEPENDPATH += $$PWD/../include

    TARGET = qofficelooktest

} else {
    warning(Lib config)

    CONFIG(installd) {
        TARGET = QOfficeLookd
    } else {
        TARGET = QOfficeLook
    }
    TEMPLATE = lib

    DEFINES += QOFFICELOOK_LIBRARY

    SOURCES += qofficelook.cpp \
            ol_windowtitlebar.cpp \
            ol_flatbutton.cpp \
            ol_frame.cpp

    HEADERS += qofficelook.h\
            qofficelook_global.h \
            ol_windowtitlebar.h \
            ol_flatbutton.h \
            ol_frame.h

    target.path = ../lib
    INSTALLS += target

    header_files.files = $$HEADERS
    header_files.path = ../include
    INSTALLS += header_files

    mylib.CONFIG += no_check_exists
    mylib.files = release/QRibbonPlugin.lib release/QRibbonPlugin.dll
    mylib.path = ../lib
    INSTALLS += mylib

}

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    qofficelook.qrc

DISTFILES += \
    memorycheck.bat







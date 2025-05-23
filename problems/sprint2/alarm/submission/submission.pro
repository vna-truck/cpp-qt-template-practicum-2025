########
MOCK_LIB=../../../../mocks_library
########

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

isEmpty(MOCK_LIB) {
    MOCK_LIB=/tmp/practicum-qt-mocks
}

INCLUDEPATH += $$MOCK_LIB

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

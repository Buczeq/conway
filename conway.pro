
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = conway
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    zycie.cpp

HEADERS  += mainwindow.h \
    zycie.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    README.markdown

#-------------------------------------------------
#
# Project created by QtCreator 2018-06-11T12:47:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Builder
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    loginform.cpp \
    tableform.cpp \
    creategroupform.cpp \
    createuserform.cpp \
    importfilesform.cpp \
    createtenantform.cpp \
    createlogoform.cpp \
    createsecurityfilterform.cpp \
    createmenuform.cpp \
    creategroupscreenform.cpp \
    createscreeform.cpp \
    createdocfamilyform.cpp \
    createdocgroupsform.cpp

HEADERS += \
        mainwindow.h \
    loginform.h \
    tableform.h \
    creategroupform.h \
    createuserform.h \
    importfilesform.h \
    createtenantform.h \
    createlogoform.h \
    createsecurityfilterform.h \
    createmenuform.h \
    creategroupscreenform.h \
    createscreeform.h \
    createdocfamilyform.h \
    createdocgroupsform.h

FORMS += \
        mainwindow.ui \
    loginform.ui \
    tableform.ui \
    creategroupform.ui \
    createuserform.ui \
    importfilesform.ui \
    createtenantform.ui \
    createlogoform.ui \
    createsecurityfilterform.ui \
    createmenuform.ui \
    creategroupscreenform.ui \
    createscreeform.ui \
    createdocfamilyform.ui \
    createdocgroupsform.ui

RESOURCES += \
    res.qrc

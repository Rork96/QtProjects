QT += quick quickwidgets
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:{
    VERSION = 1.0.0
    QMAKE_TARGET_COMPANY = masterarrow
    QMAKE_TARGET_PRODUCT = System Care
    QMAKE_TARGET_DESCRIPTION = System
    QMAKE_TARGET_COPYRIGHT = masterarrow (masterarrows@gmail.com)
}

win32: RC_ICONS = $$PWD/pict/SystemCare.ico

TARGET = SystemCare

CONFIG(debug, debug|release) {
    # debug
} else {
    # release
    win32: {
        # Папка для release-версии программы
        DESTDIR = $${_PRO_FILE_PWD_}/win32
        # Запуск windeployqt для сборки всех библиотек
        QMAKE_POST_LINK += windeployqt $$PWD/win32/$$TARGET
    }
    unix: {
        # Папка для release-версии программы
        DESTDIR = $${_PRO_FILE_PWD_}/linux
        # Запуск linuxdeployqt для сборки всех библиотек
        QMAKE_POST_LINK += linuxdeployqt $$PWD/win32/$$TARGET
    }
}

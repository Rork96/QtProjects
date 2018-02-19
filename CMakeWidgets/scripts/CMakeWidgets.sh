#!/bin/sh
export LD_LIBRARY_PATH=`pwd`/lib
export QML_IMPORT_PATH=`pwd`/qml
export QML2_IMPORT_PATH=`pwd`/qml
export QT_QPA_PLATFORM_PLUGIN_PATH=`pwd`/plugins/platforms
./CMakeWidgets

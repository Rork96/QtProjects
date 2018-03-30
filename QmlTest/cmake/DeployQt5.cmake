if (WIN32)
    #set (FIX "")
    #set (TYPE "dll")
    #set (END "")
elseif (UNIX)
    #set (FIX "lib")
    #set (TYPE ".so")
    set (END ".so")
endif ()

set (FIX ${CMAKE_FIND_LIBRARY_PREFIXES})    #lib
set (TYPE ${CMAKE_FIND_LIBRARY_SUFFIXES})   #.dll

function(install_qt5_file srcPath fileName destPath)
    set(QT_PREFIX "")

    if(CMAKE_BUILD_TYPE STREQUAL Debug)
        set(QT_PREFIX "d")
    endif(CMAKE_BUILD_TYPE STREQUAL Debug)

    install(FILES "${srcPath}/${FIX}${fileName}${QT_PREFIX}.${TYPE}" DESTINATION ${destPath} COMPONENT Runtime)
endfunction(install_qt5_file)

function(install_qt5_lib DEST)
    set (FilesToInstall)
    foreach(Qt5Lib ${ARGN})
        get_target_property(Qt5LibLocation Qt5::${Qt5Lib} LOCATION_${CMAKE_BUILD_TYPE})
        set (FilesToInstall ${FilesToInstall} ${Qt5LibLocation})
    endforeach(Qt5Lib ${ARGN})
    install(FILES ${FilesToInstall} DESTINATION ${DEST})
endfunction(install_qt5_lib)

function(install_qt5_dbdrivers dest)
    foreach(driver ${ARGN})
        install_qt5_file(${_qt5Core_install_prefix}/plugins/sqldrivers ${FIX}${driver}${END}  ${dest}/sqldrivers)
    endforeach(driver)
endfunction(install_qt5_dbdrivers)

function(install_qt5_imageformats dest)
    foreach(imgformat ${ARGN})
        install_qt5_file(${_qt5Core_install_prefix}/plugins/imageformats ${FIX}${imgformat}{END}  ${dest}/imageformats)
    endforeach(imgformat)
endfunction(install_qt5_imageformats)

function(install_qt5_platform dest)
    if (WIN32)
        install_qt5_file(${_qt5Core_install_prefix}/plugins/platforms "qwindows" ${dest}/platforms)
    else ()
        install_qt5_file(${_qt5Core_install_prefix}/plugins/platforms "qxcb" ${dest}/platforms)
    endif ()

endfunction(install_qt5_platform)

function(install_qt5_qml_plugin_qtquick2 dest)
    install_qt5_file(${_qt5Core_install_prefix}/qml/QtQuick.2 ${FIX}"qtquick2plugin"${END} ${dest}/qml/QtQuick.2)
    install(FILES ${_qt5Core_install_prefix}/qml/QtQuick.2/qmldir DESTINATION ${dest}/qml/QtQuick.2)
endfunction(install_qt5_qml_plugin_qtquick2)

function(install_qt5_qml_plugin dest)
    foreach(plugin ${ARGN})
        if(${plugin} STREQUAL "QtQuick2")
            install_qt5_qml_plugin_qtquick2 (${dest})
        endif()
    endforeach(plugin)
endfunction(install_qt5_qml_plugin)

function(install_qt5_V8 dest)
    install_qt5_file(${_qt5Core_install_prefix}/bin Qt5V8 ${dest})
endfunction(install_qt5_V8)

function(install_qt5_icu dest)
    if (WIN32)
        install(FILES ${_qt5Core_install_prefix}/bin/libicudt58.dll
                      ${_qt5Core_install_prefix}/bin/libicuin58.dll
                      ${_qt5Core_install_prefix}/bin/libicuuc58.dll
                DESTINATION ${dest})
    elseif (UNIX)
        install(FILES ${_qt5Core_install_prefix}/lib/${FIX}icudata.so.56.1       #libicudata.so.56.1
                      ${_qt5Core_install_prefix}/lib/${FIX}icui18n.so.56.1       #libicui18n.so.56.1
                      ${_qt5Core_install_prefix}/lib/${FIX}icuuc.so.56.1         #libicuuc.so.56.1
                DESTINATION ${dest})
    endif()
endfunction(install_qt5_icu)

function(install_rt dest)
    if (WIN32)
        install(FILES ${_qt5Core_install_prefix}/bin/libgcc_s_seh-1.dll
                      ${_qt5Core_install_prefix}/bin/libstdc++-6.dll
                      ${_qt5Core_install_prefix}/bin/libwinpthread-1.dll
                      ${_qt5Core_install_prefix}/bin/libpcre2-16-0.dll
                      ${_qt5Core_install_prefix}/bin/zlib1.dll
                      ${_qt5Core_install_prefix}/bin/libfreetype-6.dll
                      ${_qt5Core_install_prefix}/bin/libharfbuzz-0.dll
                      ${_qt5Core_install_prefix}/bin/libbz2-1.dll
                      #${_qt5Core_install_prefix}/bin/libpng16-16.dll
                      ${_qt5Core_install_prefix}/bin/libglib-2.0-0.dll
                DESTINATION ${dest})
    elseif (UNIX)
        set (SYS_PATH "/usr/lib/x86_64-linux-gnu")
        set (S_PATH "/lib/x86_64-linux-gnu")
        install(FILES ${S_PATH}/libgcc_s.so.1
                      ${SYS_PATH}/libstdc++.so.6
                      ${S_PATH}/libpthread.so.0
                      ${S_PATH}/libz.so.1
                      ${S_PATH}/libc.so.6
                      ${SYS_PATH}/libGL.so.1
                      ${SYS_PATH}/libgthread-2.0.so.0
                      ${S_PATH}/libdl.so.2
                      #${S_PATH}/libpng16.so.0
                      ${S_PATH}/libglib-2.0.so.0
                DESTINATION ${dest})
    endif()
endfunction(install_rt)

function (system_install)
    # Install in system folder (for Linux)
    install (TARGETS ${PROJECT_NAME}
        EXPORT depends
        RUNTIME DESTINATION "opt/${PROJECT_NAME}"
        LIBRARY DESTINATION "opt/${PROJECT_NAME}/lib"
        ARCHIVE DESTINATION "opt/${PROJECT_NAME}/lib")

    install(FILES ${PROJECT_SOURCE_DIR}/pict/${PROJECT_NAME}.png
            DESTINATION "usr/share/pixmaps")
    install(FILES ${PROJECT_SOURCE_DIR}/scripts/${PROJECT_NAME}.desktop
            DESTINATION "usr/share/applications")
    install(FILES ${PROJECT_SOURCE_DIR}/scripts/${PROJECT_NAME}.sh
            DESTINATION "opt/${PROJECT_NAME}")
    install(FILES ${PROJECT_SOURCE_DIR}/scripts/qt.conf
            DESTINATION "opt/${PROJECT_NAME}")
endfunction ()

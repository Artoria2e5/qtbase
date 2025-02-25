# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

if(QT_FEATURE_action)
    add_subdirectory(qaction)
    add_subdirectory(qactiongroup)
endif()
add_subdirectory(qbackingstore)
add_subdirectory(qcursor)
add_subdirectory(qdrag)
add_subdirectory(qevent)
add_subdirectory(qfileopenevent)
add_subdirectory(qguichronotimer)
add_subdirectory(qguieventdispatcher)
add_subdirectory(qguitimer)
if(NOT ANDROID AND NOT WASM)
    add_subdirectory(qhighdpi)
endif()
add_subdirectory(qinputdevice)
add_subdirectory(qinputmethod)
add_subdirectory(qkeyevent)
add_subdirectory(qmouseevent)
add_subdirectory(qpalette)
add_subdirectory(qscreen)
add_subdirectory(qsurfaceformat)
add_subdirectory(qwindow)
if(QT_FEATURE_private_tests)
    add_subdirectory(qguiapplication)
endif()
add_subdirectory(qpixelformat)
add_subdirectory(qrasterwindow)
add_subdirectory(qaddpostroutine)
if(NOT UIKIT)
    add_subdirectory(qclipboard)
endif()
if(TARGET Qt::Network)
    add_subdirectory(qguieventloop)
endif()
if(QT_FEATURE_shortcut)
    add_subdirectory(qguimetatype)
    add_subdirectory(qguivariant)
    add_subdirectory(qkeysequence)
    add_subdirectory(qshortcut)
endif()
if(TARGET Qt::Widgets)
    add_subdirectory(qmouseevent_modal)
    add_subdirectory(qtouchevent)
endif()
if(QT_FEATURE_opengl)
    add_subdirectory(qopenglwindow)
endif()
if(TARGET Qt::Network AND WIN32)
    add_subdirectory(noqteventloop)
endif()

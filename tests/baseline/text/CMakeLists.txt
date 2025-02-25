# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

list(APPEND test_data "./data")

if(NOT QT_BUILD_STANDALONE_TESTS AND NOT QT_BUILDING_QT)
    cmake_minimum_required(VERSION 3.16)
    project(tst_baseline_text LANGUAGES CXX)
    find_package(Qt6BuildInternals REQUIRED COMPONENTS STANDALONE_TEST)
endif()

qt_internal_add_test(tst_baseline_text
    SOURCES
        ../shared/baselineprotocol.cpp ../shared/baselineprotocol.h ../shared/lookup3.cpp
        ../shared/qbaselinetest.cpp ../shared/qbaselinetest.h
        ../shared/qwidgetbaselinetest.cpp ../shared/qwidgetbaselinetest.h
        tst_baseline_text.cpp
    INCLUDE_DIRECTORIES
        ../shared
    LIBRARIES
        Qt::Gui
        Qt::Widgets
        Qt::WidgetsPrivate
        Qt::Network
    TESTDATA ${test_data}
)

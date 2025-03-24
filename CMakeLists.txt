cmake_minimum_required(VERSION 3.16)

project(mdfplot VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(TS_FILES mdfplot_zh_CN.ts)

set(QCP_SRC
    "qcp/qcustomplot.h"
    "qcp/qcustomplot.cpp"
)

set(PROJECT_UTILS
    "Signals.h"
    "Signals.cpp"
    "SignalReader.h"
    "SignalReader.cpp"
)

set(PROJECT_SOURCES
    "main.cpp"
    "MainWindow.cpp"
    "MainWindow.h"
    "MainWindow.ui"
    "SignalListModel.h"
    "SignalListModel.cpp"
    "SignalListView.h"
    "SignalListView.cpp"
    
    #${TS_FILES}
)

add_executable(${PROJECT_NAME}
    "main.cpp"
    ${PROJECT_SOURCES}
    ${PROJECT_UTILS}
    ${QCP_SRC}
)

# 链接Qt库
find_package(Qt5 REQUIRED COMPONENTS 
    Core
    Widgets 
    Gui
    PrintSupport
    LinguistTools
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt5::Core
    PRIVATE Qt5::Widgets
    PRIVATE Qt5::Gui
    PRIVATE Qt5::PrintSupport
)

# Mdflib库
message(STATUS "MDFLIB_ROOT: $ENV{MDFLIB_ROOT}")

include_directories(
    $ENV{MDFLIB_ROOT}/include
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE debug $ENV{MDFLIB_ROOT}/lib/mdfd.lib       # mdflibd.lib 
    PRIVATE optimized $ENV{MDFLIB_ROOT}/lib/mdf    # mdflib.lib
)

message(STATUS "VCPKG_ROOT: $ENV{VCPKG_ROOT}")

find_package(ZLIB REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE ZLIB::ZLIB)

find_package(expat CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE expat::expat)
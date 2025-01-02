cmake_minimum_required(VERSION 3.16)

project(mdfplot VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES mdfplot_zh_CN.ts)

set(PROJECT_SOURCES
        main.cpp
        MainWindow.cpp
        MainWindow.h
        MainWindow.ui
        ${TS_FILES}
)

qt_add_executable(mdfplot
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

target_link_libraries(mdfplot PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# 链接mdf库
target_include_directories(mdfplot PUBLIC "/usr/local/include")
target_link_libraries(mdfplot PRIVATE "/usr/local/lib/libmdf.a")

# 链接mdf依赖库
include("./script/zlib.cmake")
include("./script/expat.cmake")

target_compile_definitions(mdfplot PRIVATE xml_static)
target_link_libraries(mdfplot PRIVATE ${EXPAT_LIBRARIES})
target_link_libraries(mdfplot PRIVATE ${ZLIB_LIBRARIES})

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.mdfplot)
endif()
set_target_properties(mdfplot PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS mdfplot
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(mdfplot)
endif()

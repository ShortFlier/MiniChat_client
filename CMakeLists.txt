cmake_minimum_required(VERSION 3.16)

project(chat_client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS WebSockets)
find_package(Qt6 REQUIRED COMPONENTS Core)

set(PROJECT_SOURCES
        main.cpp
        loginwidget.cpp
        loginwidget.h
        loginwidget.ui
)


#将assets文件夹拷贝到exe同级目录下
file(COPY "./assets" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(chat_client
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        appimg.qrc
        loginscene.h loginscene.cpp
        registwidget.h registwidget.cpp registwidget.ui
        rgtcfmwidget.h rgtcfmwidget.cpp rgtcfmwidget.ui
        websocketconnect.h websocketconnect.cpp
        tempconnect.h tempconnect.cpp
        datahead.h datahead.cpp
        webdistb.h webdistb.cpp
        wapplication.h wapplication.cpp
        validconnect.h validconnect.cpp
        mainscene.h mainscene.cpp
        entity.h entity.cpp
        informationwidget.h informationwidget.cpp informationwidget.ui
        mainscene.ui
        personal.h personal.cpp personal.ui
        filemanager.h filemanager.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET chat_client APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(chat_client SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(chat_client
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(chat_client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(chat_client PRIVATE Qt6::WebSockets)
target_link_libraries(chat_client PRIVATE Qt6::Core)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.chat_client)
endif()
set_target_properties(chat_client PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS chat_client
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(chat_client)
endif()

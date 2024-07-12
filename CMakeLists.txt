cmake_minimum_required(VERSION 3.16)

project(FallGuysPing VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Widgets)

qt_standard_project_setup()

set(SOURCE_FILES
    src/FileWatcher.h
    src/FileWatcher.cpp
    src/FileChangeWorker.h
    src/FileChangeWorker.cpp
    src/Utils.h
    src/Utils.cpp
    src/Manager.h
    src/Manager.cpp
    src/PingWorker.h
    src/PingWorker.cpp
    src/Pinger.h
    src/Pinger.cpp
)

qt_add_executable(appFallGuysPing
    src/main.cpp
    qml.qrc
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appFallGuysPing PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appFallGuysPing
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    OUTPUT_NAME "FallGuysPing"
)

target_sources(appFallGuysPing PRIVATE
    ${SOURCE_FILES}
)

target_link_libraries(appFallGuysPing
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Widgets
    PRIVATE Iphlpapi
    PRIVATE Ws2_32
)

include(GNUInstallDirs)

install(TARGETS appFallGuysPing
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

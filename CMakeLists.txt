cmake_minimum_required(VERSION 3.24)

project(FallGuysPing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

include(FetchContent)

set(QT_DEFAULT_MAJOR_VERSION 6 CACHE STRING "Qt version to use, defaults to 6")
set(QAPPLICATION_CLASS QApplication CACHE STRING "Inheritance class for SingleApplication")

FetchContent_Declare(
    SingleApplication
    GIT_REPOSITORY https://github.com/itay-grudev/SingleApplication.git
    GIT_TAG        8c48163c4d3fbba603cfe8a5b94046c9dad71825
)

FetchContent_MakeAvailable(SingleApplication)

find_package(SingleApplication)
find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Widgets)

qt_standard_project_setup()

add_subdirectory(WinToast)

include_directories(src)

qt_add_executable(appFallGuysPing
    src/main.cpp
    assets.qrc
    assets/fallguysping.rc  # icon resource.
    assets/version.rc
)

qt_policy(SET QTP0001 NEW)

qt_add_qml_module(appFallGuysPing
    URI FallGuysPing
    VERSION 1.0

    QML_FILES
        qml/MainWindow.qml
        qml/PingTextWindow.qml
        qml/Sidebar.qml
        qml/Tab.qml
        qml/OverlayPage.qml
        qml/LabelSeparator.qml
        qml/AboutPage.qml
        qml/SquareRadioButton.qml
        qml/CusSwitch.qml
        qml/CornerSelect.qml
        qml/FusionSpinBox.qml
        qml/ColorPicker.qml
        qml/CustomComboBox.qml
        qml/CustomCheckBox.qml
        qml/AppPage.qml
        qml/CustomText.qml
        qml/OverviewPage.qml
        qml/PingBox.qml
        qml/ServerInfoRow.qml
        qml/ServerInfoTable.qml
        qml/ServerInfoProps.qml
        qml/PingDashboard.qml

    SOURCES
        src/DashedRectangle.h
        src/DashedRectangle.cpp
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
        src/TrayIcon.h
        src/TrayIcon.cpp
        src/Settings.h
        src/Settings.cpp
        src/TextCorner.h
        src/IPGeoLocator.h
        src/IPGeoLocator.cpp
        src/Registry.h
        src/Registry.cpp
        src/ToastHandler.h
        src/GeoData.h
        src/GeoData.cpp
        src/Stopwatch.h
        src/Stopwatch.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appFallGuysPing PROPERTIES
    WIN32_EXECUTABLE TRUE
    OUTPUT_NAME "FallGuysPing"
)

target_sources(appFallGuysPing PRIVATE
    ${SOURCE_FILES}
)

target_link_libraries(appFallGuysPing PRIVATE
    Qt6::Quick
    Qt6::Widgets
    WinToast
    Iphlpapi
    Ws2_32

    SingleApplication::SingleApplication
)

include(GNUInstallDirs)

install(TARGETS appFallGuysPing
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

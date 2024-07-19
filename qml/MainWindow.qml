import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: root

    objectName: "mainWindow"
    width: 650
    height: 430
    visible: false

    property color sidebarBgColor: "#e8e8e8"
    property color mainbarBgColor: "#fff"
    property color accentColor: "#017ad9"
    property color selectionColor: "#0078d4"
    property int transitionDuration: 150
    property string appVersion: "v1.0.0"
    property int activeView: sidebar.selectedView
    property var supportedFonts: ["Arial", "Consolas", "Courier", "Georgia", "Segoe UI", "Tahoma", "Times New Roman", "Trebuchet MS", "Verdana"]

    enum View {
        AppView,
        OverlayView,
        AboutView
    }

    Component.onCompleted: root.visible = !Manager.settings.startMinimized

    Pane {
        anchors.fill: parent
        focusPolicy: Qt.ClickFocus
    }

    onClosing: close => {
                   hide()
                   close.accepted = false
               }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            id: sidebarRect

            Layout.fillHeight: true
            Layout.preferredWidth: 175
            color: root.sidebarBgColor

            Sidebar {
                id: sidebar
                anchors.fill: parent
            }
        }

        // Separator
        Rectangle {
            Layout.fillHeight: true
            Layout.preferredWidth: 1
            color: "#e0e0e0"
        }

        Rectangle {
            id: mainbar
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: root.mainbarBgColor

            AppPage {
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.topMargin: 24
                anchors.leftMargin: 20

                visible: root.activeView === MainWindow.View.AppView
            }

            OverlayPage {
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.topMargin: 24
                anchors.leftMargin: 20

                visible: root.activeView === MainWindow.View.OverlayView
            }

            AboutPage {
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.topMargin: 32
                anchors.leftMargin: 28

                visible: root.activeView === MainWindow.View.AboutView
            }
        }
    }
}

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: root

    objectName: "mainWindow"
    width: 650
    height: 400
    visible: true

    property color sidebarBgColor: "#e8e8e8"
    property color mainbarBgColor: "#fff"
    property color accentColor: "#017ad9"
    property int transitionDuration: 150
    property string appVersion: "v1.0.0"
    property int activeView: sidebar.selectedView

    enum View {
        MainView,
        AboutView
    }

    // Hide the window instead of closing it when the close button is clicked
    // @disable-check M16
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

        Rectangle {
            id: mainbar
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: root.mainbarBgColor

            MainPage {
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.topMargin: 27
                anchors.leftMargin: 24

                visible: root.activeView === MainWindow.View.MainView
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

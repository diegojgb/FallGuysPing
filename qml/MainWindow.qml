import QtQuick
import QtQuick.Controls.Imagine
import QtQuick.Layouts

ApplicationWindow {
    id: root

    objectName: "mainWindow"
    width: 650
    height: 450
    visible: true
    palette: lightTheme

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

    Pane {
        anchors.fill: parent
        focusPolicy: Qt.ClickFocus
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

            MainPage {
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.topMargin: 24
                anchors.leftMargin: 20

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

    Palette {
        id: lightTheme
        alternateBase: "#fff"
        base: "#e6e6e6"
        button: "#eee"
        buttonText: "#000"
        dark: "#999"
        highlight: '#0078d4'
        highlightedText: "#fff"
        light: "#fff"
        mid: "#bbb"
        midlight: "#ccc"
        placeholderText: "#80000000"
        shadow: "#777"
        text: "#000"
        window: "#eee"
        windowText: "#000"
        accent: "#eee"

        disabled.text: '#737373'
    }
}

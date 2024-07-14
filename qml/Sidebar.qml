import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: control

    property int selectedView: MainWindow.View.MainView

    ColumnLayout {
        anchors.fill: parent

        Row {
            Layout.topMargin: 14
            Layout.leftMargin: 14
            spacing: 8

            Image {
                id: logo
                source: "qrc:/assets/ping-icon.png"
            }

            Label {
                height: parent.height
                verticalAlignment: Text.AlignVCenter
                text: "FallGuysPing"
                color: "#000"
                font.pointSize: 11.5
                font.weight: Font.DemiBold
            }
        }

        Tab {
            Layout.fillWidth: true
            Layout.preferredHeight: 30
            Layout.topMargin: 10
            Layout.leftMargin: 10
            Layout.rightMargin: 10
            text: 'Settings'
            selected: control.selectedView === MainWindow.View.MainView

            onClicked: control.selectedView = MainWindow.View.MainView
        }

        Tab {
            Layout.fillWidth: true
            Layout.preferredHeight: 30
            Layout.leftMargin: 10
            Layout.rightMargin: 10
            text: 'About'
            selected: control.selectedView === MainWindow.View.AboutView

            onClicked: control.selectedView = MainWindow.View.AboutView
        }

        Item {
            Layout.fillHeight: true
            Layout.preferredWidth: 1
        }
    }
}

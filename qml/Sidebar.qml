import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: control

    property int selectedView: MainWindow.View.AppView

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
            text: 'General'
            selected: control.selectedView === MainWindow.View.AppView

            onClicked: control.selectedView = MainWindow.View.AppView
        }

        Tab {
            Layout.fillWidth: true
            Layout.preferredHeight: 30
            Layout.leftMargin: 10
            Layout.rightMargin: 10
            text: 'Overlay'
            selected: control.selectedView === MainWindow.View.OverlayView

            onClicked: control.selectedView = MainWindow.View.OverlayView
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

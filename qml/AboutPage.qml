import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    spacing: 0

    Row {
        spacing: 10

        Image {
            source: 'qrc:/assets/ping-icon-big.png'
            anchors.verticalCenter: parent.verticalCenter
        }

        Column {
            Label {
                text: 'FallGuysPing'
                font.pointSize: 18
                font.weight: Font.DemiBold
            }
            Label {
                text: 'Version 1.1.0-dev.1'
                font.pointSize: 12
            }
        }
    }

    LabelSeparator {
        Layout.topMargin: 24
        text: 'Author info'
    }

    Label {
        Layout.leftMargin: 10
        Layout.topMargin: 10
        text: '© 2024 - Diego Gonzalez'
        font.pointSize: 10
        renderType: Text.NativeRendering
    }

    Label {
        Layout.leftMargin: 26
        text: 'Released: July 2024'
        font.pointSize: 10
        renderType: Text.NativeRendering
    }
}

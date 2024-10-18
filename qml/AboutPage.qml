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
                text: 'Version 1.1.0'
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
    }

    Label {
        Layout.leftMargin: 26
        text: 'Released: August 2024'
        font.pointSize: 10
    }

    Item {
        Layout.preferredWidth: 1
        Layout.fillHeight: true
    }

    Text {
        Layout.fillWidth: true
        Layout.bottomMargin: 20
        Layout.rightMargin: 30
        color: "#444"
        text: 'FallGuysPing uses <a href="https://ipinfo.io">ipinfo.io</a> IP geolocation web service, and <a href="https://ip2location.io">ip2location.io</a> as a backup.'
        font.pointSize: 9
        wrapMode: Text.WordWrap
        textFormat: Text.RichText
        onLinkActivated: function (url) {
            Qt.openUrlExternally(url)
        }
    }
}

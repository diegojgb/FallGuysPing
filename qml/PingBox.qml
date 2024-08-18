import QtQuick
import QtQuick.Layouts

Rectangle {
    id: control
    color: "#eee"

    property alias header: pingHeader.text
    property string ping
    property alias pingSize: pingNumber.font.pointSize

    Column {
        id: pingCol
        anchors.centerIn: parent

        Text {
            id: pingHeader
            font.pointSize: 10
            font.bold: true
            color: "#555"
            renderType: Text.QtRendering
        }

        Text {
            id: pingNumber
            anchors.horizontalCenter: parent.horizontalCenter
            font.weight: Font.DemiBold
            font.pointSize: 11
            text: control.ping + "ms"
            renderType: Text.QtRendering
        }
    }
}

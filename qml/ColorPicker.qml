import QtQuick
import Qt.labs.platform

Rectangle {
    id: control
    radius: width / 2
    border.color: "#888"
    border.width: 1
    color: control.pickedColor

    required property color pickedColor

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onClicked: colorDialog.open()
    }

    ColorDialog {
        id: colorDialog
        title: "Pick a Color"
        color: control.pickedColor
        onColorChanged: control.pickedColor = colorDialog.color
    }
}

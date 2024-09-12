import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import TextCorner 1.0

Item {
    id: control

    property color fillColor: root.sidebarBgColor

    Rectangle {
        anchors.fill: parent
        color: control.fillColor
        border.color: "#aaa"
        border.width: 1

        Text {
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter
            bottomPadding: 3
            text: "Overlay\nCorner"
            font.pointSize: 9
            font.weight: Font.DemiBold
        }

        SquareRadioButton {
            id: topLeftButton
            anchors.top: parent.top
            anchors.left: parent.left
            spacing: 0
            checked: Manager.settings.textCorner === TextCorner.TopLeft
            onClicked: Manager.settings.textCorner = TextCorner.TopLeft
        }

        SquareRadioButton {
            id: topRightButton
            anchors.top: parent.top
            anchors.right: parent.right
            spacing: 0
            checked: Manager.settings.textCorner === TextCorner.TopRight
            onClicked: Manager.settings.textCorner = TextCorner.TopRight
        }

        SquareRadioButton {
            id: bottomLeftButton
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            spacing: 0
            checked: Manager.settings.textCorner === TextCorner.BottomLeft
            onClicked: Manager.settings.textCorner = TextCorner.BottomLeft
        }

        SquareRadioButton {
            id: bottomRightButton
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            spacing: 0
            checked: Manager.settings.textCorner === TextCorner.BottomRight
            onClicked: Manager.settings.textCorner = TextCorner.BottomRight
        }
    }
}

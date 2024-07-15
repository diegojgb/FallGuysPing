import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import TextCorner 1.0

Rectangle {
    color: root.sidebarBgColor
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
        property int positionValue: TextCorner.TopLeft
        anchors.top: parent.top
        anchors.left: parent.left
        ButtonGroup.group: radioGroup
        spacing: 0
    }
    SquareRadioButton {
        id: topRightButton
        property int positionValue: TextCorner.TopRight
        anchors.top: parent.top
        anchors.right: parent.right
        ButtonGroup.group: radioGroup
        spacing: 0
    }
    SquareRadioButton {
        id: bottomLeftButton
        property int positionValue: TextCorner.BottomLeft
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        ButtonGroup.group: radioGroup
        spacing: 0
    }
    SquareRadioButton {
        id: bottomRightButton
        property int positionValue: TextCorner.BottomRight
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        ButtonGroup.group: radioGroup
        spacing: 0
    }
}

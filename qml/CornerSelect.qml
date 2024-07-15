import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import TextCorner 1.0

Item {
    id: control

    property int selectedValue: Manager.settings.textCorner
    property color fillColor: root.sidebarBgColor

    onSelectedValueChanged: Manager.settings.textCorner = control.selectedValue

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
            checked: control.selectedValue === TextCorner.TopLeft
            onClicked: control.selectedValue = TextCorner.TopLeft
        }
        SquareRadioButton {
            id: topRightButton
            anchors.top: parent.top
            anchors.right: parent.right
            spacing: 0
            checked: control.selectedValue === TextCorner.TopRight
            onClicked: control.selectedValue = TextCorner.TopRight
        }
        SquareRadioButton {
            id: bottomLeftButton
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            spacing: 0
            checked: control.selectedValue === TextCorner.BottomLeft
            onClicked: control.selectedValue = TextCorner.BottomLeft
        }
        SquareRadioButton {
            id: bottomRightButton
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            spacing: 0
            checked: control.selectedValue === TextCorner.BottomRight
            onClicked: control.selectedValue = TextCorner.BottomRight
        }
    }
}

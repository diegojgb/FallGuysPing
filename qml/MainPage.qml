import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import TextCorner 1.0

ColumnLayout {
    id: page

    property int textCorner: Manager.settings.textCorner

    onTextCornerChanged: {
        if (page.textCorner === TextCorner.Custom)
            radioGroup.checkState = Qt.Unchecked
    }

    Label {
        text: 'General settings'
        font.pointSize: 17

        Behavior on color {
            ColorAnimation {
                duration: root.transitionDuration
            }
        }
    }

    LabelSeparator {
        Layout.topMargin: 16
        text: 'App settings'
    }

    ColumnLayout {
        Layout.topMargin: 10
        Layout.leftMargin: 20
        spacing: 10

        CheckBox {
            text: "Start app minimized to the system tray."
        }

        CheckBox {
            text: "Sample option."
        }
    }

    LabelSeparator {
        Layout.topMargin: 16
        text: 'Text position'
    }

    ButtonGroup {
        id: radioGroup

        onClicked: button => {
                       Manager.settings.textCorner = button.positionValue
                   }
    }

    ColumnLayout {
        Layout.topMargin: 10
        Layout.leftMargin: 20

        RowLayout {

            Rectangle {
                Layout.preferredWidth: 145
                Layout.preferredHeight: 75
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

            CusSwitch {
                Layout.leftMargin: 15
                text: "Enable overlay dragging."
                checked: Manager.settings.draggableText

                onCheckedChanged: Manager.settings.draggableText = checked
            }
        }
    }
}

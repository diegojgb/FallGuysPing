import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Qt.labs.platform
import TextCorner 1.0

ColumnLayout {
    id: page

    property int textCorner: Manager.settings.textCorner

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

    ColumnLayout {
        Layout.topMargin: 10
        Layout.leftMargin: 20

        RowLayout {
            CornerSelect {
                Layout.preferredWidth: 145
                Layout.preferredHeight: 75
            }

            CusSwitch {
                Layout.leftMargin: 15
                text: "Enable overlay dragging."
                checked: Manager.settings.draggableText

                onCheckedChanged: Manager.settings.draggableText = checked
            }
        }
    }

    LabelSeparator {
        Layout.topMargin: 16
        text: 'Text format'
    }

    ColumnLayout {
        id: textFormatCol
        Layout.topMargin: 10
        Layout.leftMargin: 20

        RowLayout {
            id: textFormatFirstRow

            Text {
                Layout.alignment: Qt.AlignVCenter
                bottomPadding: 2
                font.pointSize: 10
                text: "Text size:"
            }

            FusionSpinBox {
                id: textSizeBox
                Layout.leftMargin: 5
                Layout.preferredWidth: 80
                value: Manager.settings.textSize

                onValueChanged: Manager.settings.textSize = textSizeBox.value
            }

            Text {
                Layout.leftMargin: 16
                Layout.alignment: Qt.AlignVCenter
                bottomPadding: 3
                font.pointSize: 10
                text: "Text color:"
            }

            Rectangle {
                id: colorPickerRect
                Layout.leftMargin: 3
                Layout.preferredWidth: 22
                Layout.preferredHeight: 22
                radius: width / 2
                border.color: "#888"
                border.width: 1
                color: Manager.settings.textColor

                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: colorDialog.open()
                }
            }

            ColorDialog {
                id: colorDialog
                title: "Pick a Color"
                color: Manager.settings.textColor

                onColorChanged: Manager.settings.textColor = colorDialog.color
            }
        }
    }
}

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
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
}

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    id: page

    Label {
        text: 'General settings'
        font.pointSize: 17

        Behavior on color {
            ColorAnimation {
                duration: root.transitionDuration
            }
        }
    }

    // App settings
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
    }
}

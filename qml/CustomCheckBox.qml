import QtQuick
import QtQuick.Controls.Imagine

CheckBox {
    id: control
    text: "CheckBox"
    checked: false
    spacing: 8

    property color checkedColor: root.accentColor
    property color uncheckedColor: Qt.darker(root.sidebarBgColor, 1.2)

    indicator: Rectangle {
        implicitWidth: 19
        implicitHeight: 19
        radius: 2

        color: {
            if (control.checked) {
                if (!control.enabled)
                    return Qt.lighter(control.uncheckedColor, 1.1)

                if (control.pressed)
                    return Qt.darker(control.checkedColor, 1.2)

                if (control.hovered)
                    return Qt.lighter(control.checkedColor, 1.2)

                return control.checkedColor
            }

            if (!control.enabled)
                return Qt.lighter(control.uncheckedColor, 1.1)

            if (control.pressed)
                return Qt.darker(control.uncheckedColor, 1.2)

            if (control.hovered)
                return Qt.lighter(control.uncheckedColor, 1.1)

            return control.uncheckedColor
        }

        Image {
            anchors.centerIn: parent
            source: 'qrc:/assets/checkmark.png'
            visible: control.checked
        }
    }

    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.6
        verticalAlignment: Text.AlignVCenter
        leftPadding: control.indicator.width + control.spacing
        renderType: Text.NativeRendering
    }
}

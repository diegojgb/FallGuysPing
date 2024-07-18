import QtQuick
import QtQuick.Controls

CheckBox {
    id: control
    text: "CheckBox"
    checked: false

    property color checkedColor: root.accentColor
    property color uncheckedColor: Qt.darker(root.sidebarBgColor, 1.2)

    indicator: Rectangle {
        implicitWidth: 19
        implicitHeight: 19
        radius: 2

        color: {
            if (control.checked) {
                if (control.pressed)
                    return Qt.darker(control.checkedColor, 1.2)

                if (control.hovered)
                    return Qt.lighter(control.checkedColor, 1.2)

                return control.checkedColor
            }

            if (control.pressed)
                return Qt.darker(control.uncheckedColor, 1.2)

            if (control.hovered)
                return Qt.lighter(control.uncheckedColor, 1.2)

            return control.uncheckedColor
        }

        Image {
            anchors.centerIn: parent
            source: 'qrc:/assets/checkmark.png'
            visible: control.checked
        }
    }
}

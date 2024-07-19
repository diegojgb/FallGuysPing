import QtQuick
import QtQuick.Controls.Imagine

RadioButton {
    id: control

    property color borderColor: "#aaa"
    property color bgColor: "#fff"
    property color checkSquareColor: root.accentColor

    indicator: Rectangle {
        implicitWidth: 20
        implicitHeight: 20
        color: control.down ? Qt.darker(bgColor, 1.07) : control.bgColor
        border.color: control.down ? Qt.darker(
                                         control.borderColor,
                                         1.3) : control.hovered ? Qt.darker(
                                                                      control.borderColor,
                                                                      1.2) : control.borderColor

        Rectangle {
            anchors.centerIn: parent
            width: 10
            height: 10
            color: control.down ? Qt.darker(control.checkSquareColor,
                                            1.2) : control.checkSquareColor

            visible: control.checked
        }
    }
}

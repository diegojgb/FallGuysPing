import QtQuick
import QtQuick.Controls.Fusion

SpinBox {
    id: control

    Keys.onEnterPressed: {
        control.focus = false
    }
}

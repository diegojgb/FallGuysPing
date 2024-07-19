import QtQuick
import QtQuick.Controls.Fusion

SpinBox {
    id: control

    palette: Palette {
        base: "#e6e6e6"
    }

    Keys.onEnterPressed: {
        control.focus = false
    }
}

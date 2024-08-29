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

    contentItem: TextInput {
        z: 2
        text: control.textFromValue(control.value, control.locale)

        font: control.font
        selectionColor: root.selectionColor
        selectedTextColor: "#fff"
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        readOnly: !control.editable
        validator: control.validator
        inputMethodHints: Qt.ImhFormattedNumbersOnly
    }
}

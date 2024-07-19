import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    id: page

    property int sectionTopMargin: 20

    Label {
        text: 'App settings'
        font.pointSize: 17
    }

    LabelSeparator {
        Layout.topMargin: 16
        text: 'General'
    }

    ColumnLayout {
        id: generalCol
        Layout.topMargin: 10
        Layout.leftMargin: 20
        spacing: 15

        CustomCheckBox {
            id: startMinBox
            text: "Start app minimized to the system tray"
            spacing: 8
            checked: Manager.settings.startMinimized
            onCheckedChanged: Manager.settings.startMinimized = checked
        }

        RowLayout {
            id: intervalRow

            FusionSpinBox {
                id: pingRateBox
                Layout.preferredWidth: 80
                stepSize: 1000
                from: 1000
                to: 604800000
                editable: true
                value: Manager.settings.pingInterval

                onValueChanged: {
                    Manager.settings.pingInterval = pingRateBox.value
                }

                textFromValue: function (value) {
                    return Number(value / 1000).toFixed(1)
                }

                valueFromText: function (text) {
                    return Number(text) * 1000
                }

                validator: DoubleValidator {
                    bottom: Math.min(pingRateBox.from, pingRateBox.to)
                    top: Math.max(pingRateBox.from, pingRateBox.to)
                    decimals: 1
                    notation: DoubleValidator.StandardNotation
                }
            }

            Text {
                Layout.leftMargin: 5
                Layout.alignment: Qt.AlignVCenter
                bottomPadding: 2
                text: "Ping interval (seconds)"
                renderType: Text.NativeRendering
            }
        }
    }
}
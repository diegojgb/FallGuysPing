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
        spacing: 10

        RowLayout {
            id: intervalRow

            Text {
                Layout.alignment: Qt.AlignVCenter
                bottomPadding: 2
                font.pointSize: 10
                text: "Ping interval (seconds):"
            }

            FusionSpinBox {
                id: pingRateBox
                Layout.leftMargin: 5
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
        }
    }
}

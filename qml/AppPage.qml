import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    id: page

    property int sectionTopMargin: 18

    Label {
        text: 'App settings'
        font.pointSize: 17
    }

    LabelSeparator {
        Layout.topMargin: page.sectionTopMargin
        text: 'General'
    }

    ColumnLayout {
        id: generalCol
        Layout.topMargin: 10
        Layout.leftMargin: 20
        spacing: 10

        CustomCheckBox {
            text: "Show server location in overlay"
            checked: Manager.settings.locationOverlayEnabled
            onCheckedChanged: Manager.settings.locationOverlayEnabled = checked
        }

        CustomCheckBox {
            text: "Display a notification with the server location upon connection"
            checked: Manager.settings.locationToastEnabled
            onCheckedChanged: Manager.settings.locationToastEnabled = checked
        }

        RowLayout {
            id: intervalRow
            Layout.topMargin: 3

            Text {
                Layout.alignment: Qt.AlignVCenter
                bottomPadding: 2
                text: "Ping interval (seconds):"
                renderType: Text.NativeRendering
            }

            FusionSpinBox {
                id: pingRateBox
                Layout.leftMargin: 4
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

    LabelSeparator {
        Layout.topMargin: page.sectionTopMargin
        text: 'Windows'
    }

    ColumnLayout {
        id: windowsCol
        Layout.topMargin: 10
        Layout.leftMargin: 20
        spacing: 10

        CustomCheckBox {
            id: startMinBox
            text: "Start app minimized to the system tray"
            checked: Manager.settings.startMinimized
            onCheckedChanged: Manager.settings.startMinimized = checked
        }

        CustomCheckBox {
            id: quitOnGameExit
            text: "Close app on game exit"
            checked: Manager.settings.quitOnGameExit
            onCheckedChanged: Manager.settings.quitOnGameExit = checked
        }
    }
}

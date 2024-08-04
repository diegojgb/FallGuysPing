import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Qt.labs.platform
import TextCorner 1.0

ColumnLayout {
    id: page

    property int textCorner: Manager.settings.textCorner
    property int sectionTopMargin: 22

    Label {
        text: 'Overlay formatting'
        font.pointSize: 17
    }

    CusSwitch {
        Layout.topMargin: page.sectionTopMargin
        text: "Always visible"
        checked: Manager.settings.alwaysVisible

        onCheckedChanged: Manager.settings.alwaysVisible = checked
    }

    LabelSeparator {
        Layout.topMargin: page.sectionTopMargin - 4
        text: 'Position'
    }

    ColumnLayout {
        id: textPositionCol
        Layout.topMargin: 10
        Layout.leftMargin: 20

        RowLayout {
            CornerSelect {
                Layout.preferredWidth: 145
                Layout.preferredHeight: 75
            }

            CusSwitch {
                Layout.leftMargin: 15
                text: "Enable overlay dragging"
                checked: Manager.settings.draggableText

                onCheckedChanged: Manager.settings.draggableText = checked
            }
        }
    }

    LabelSeparator {
        Layout.topMargin: page.sectionTopMargin
        text: 'Formatting'
    }

    ColumnLayout {
        id: textFormatCol
        Layout.topMargin: 12
        Layout.leftMargin: 20

        RowLayout {
            id: textFormatFirstRow

            Text {
                Layout.alignment: Qt.AlignVCenter
                bottomPadding: 2
                text: "Text size:"
                renderType: Text.NativeRendering
            }

            FusionSpinBox {
                id: textSizeBox
                Layout.leftMargin: 5
                Layout.preferredWidth: 80
                from: 1
                to: 1000
                editable: true
                value: Manager.settings.textSize

                onValueChanged: Manager.settings.textSize = textSizeBox.value
            }

            Text {
                Layout.leftMargin: 16
                Layout.alignment: Qt.AlignVCenter
                bottomPadding: 3
                text: "Text color:"
                renderType: Text.NativeRendering
            }

            ColorPicker {
                id: textColorPicker
                Layout.leftMargin: 3
                Layout.preferredWidth: 22
                Layout.preferredHeight: 22
                pickedColor: Manager.settings.textColor

                onPickedColorChanged: Manager.settings.textColor = textColorPicker.pickedColor
            }
        }

        RowLayout {
            id: textFormatSecondRow
            Layout.topMargin: 15
            spacing: 15

            CustomComboBox {
                id: fontFamilyBox
                model: root.supportedFonts
                popupHeight: 180
                currentIndex: fontFamilyBox.model.indexOf(
                                  Manager.settings.fontFamily)
                displayText: metrics.elidedText

                TextMetrics {
                    id: metrics
                    text: fontFamilyBox.currentText
                    elide: Qt.ElideRight
                    elideWidth: fontFamilyBox.width - 30
                }

                onCurrentTextChanged: Manager.settings.fontFamily = fontFamilyBox.currentText
            }

            CustomCheckBox {
                Layout.leftMargin: 5
                text: "Bold text"
                spacing: 6
                checked: Manager.settings.boldText
                onCheckedChanged: Manager.settings.boldText = checked
            }

            CustomCheckBox {
                text: "Outlined text"
                checked: Manager.settings.textOutline
                onCheckedChanged: Manager.settings.textOutline = checked
            }
        }
    }
}

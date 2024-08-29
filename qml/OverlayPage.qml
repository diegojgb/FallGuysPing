import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Qt.labs.platform
import TextCorner 1.0

Flickable {
    anchors.fill: parent
    ScrollBar.vertical: ScrollBar {}
    boundsBehavior: Flickable.StopAtBounds
    contentHeight: page.height + page.anchors.topMargin + bottomPadding

    property int bottomPadding: 45

    ColumnLayout {
        id: page
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 24
        anchors.leftMargin: 20

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
            onToggled: Manager.settings.alwaysVisible = checked
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
                    onToggled: Manager.settings.draggableText = checked
                }
            }
        }

        LabelSeparator {
            Layout.topMargin: page.sectionTopMargin
            text: 'Text'
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
                    onToggled: Manager.settings.boldText = checked
                }

                CustomCheckBox {
                    text: "Outlined text"
                    checked: Manager.settings.textOutline
                    onToggled: Manager.settings.textOutline = checked
                }
            }
        }

        LabelSeparator {
            Layout.topMargin: page.sectionTopMargin
            text: 'Background'
        }

        ColumnLayout {
            id: backgroundCol
            Layout.topMargin: 10
            Layout.leftMargin: 20

            CusSwitch {
                text: "Show background"
                checked: Manager.settings.bgEnabled
                onToggled: Manager.settings.bgEnabled = checked
            }

            RowLayout {
                Layout.topMargin: 10

                Text {
                    Layout.alignment: Qt.AlignVCenter
                    bottomPadding: 2
                    text: "Padding:"
                }

                FusionSpinBox {
                    Layout.leftMargin: 5
                    Layout.preferredWidth: 80
                    from: 0
                    to: 1000
                    editable: true
                    value: Manager.settings.bgPadding

                    onValueChanged: Manager.settings.bgPadding = value
                }

                Text {
                    Layout.leftMargin: 16
                    Layout.alignment: Qt.AlignVCenter
                    bottomPadding: 3
                    text: "Color:"
                }

                ColorPicker {
                    Layout.leftMargin: 3
                    Layout.preferredWidth: 22
                    Layout.preferredHeight: 22
                    pickedColor: Manager.settings.bgColor

                    onPickedColorChanged: Manager.settings.bgColor = pickedColor
                }
            }
        }
    }
}

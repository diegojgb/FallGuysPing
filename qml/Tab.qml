import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

TabButton {
    id: control

    property alias contentAnchors: content.anchors
    property alias selected: control.checked
    property alias truncated: text.truncated
    property bool enabled
    property color textColor: "#000"

    signal rightClicked

    font.pointSize: 10

    background: Rectangle {
        id: background
        anchors.fill: parent
        radius: 4

        color: {
            if (control.hovered) {
                return "#bdbdbd"
            } else if (control.selected) {
                return "#cecece"
            } else {
                return root.sidebarBgColor
            }
        }

        Behavior on color {
            ColorAnimation {
                duration: root.transitionDuration
            }
        }

        Rectangle {
            anchors.verticalCenter: parent.verticalCenter
            height: 16
            width: 3
            radius: 10
            color: root.accentColor
            visible: control.selected
        }
    }

    contentItem: Item {
        anchors.fill: background

        RowLayout {
            id: content
            spacing: 5
            anchors.fill: parent
            anchors.bottomMargin: 4

            Text {
                id: text
                Layout.fillWidth: true
                Layout.leftMargin: 12
                topPadding: 2
                text: control.text
                font: control.font
                color: control.textColor
                elide: Text.ElideRight
                maximumLineCount: 1
                renderType: Text.QtRendering
            }
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        cursorShape: Qt.PointingHandCursor
        hoverEnabled: true

        onClicked: mouse => {
                       if (mouse.button === Qt.LeftButton) {
                           control.clicked()
                       } else if (mouse.button === Qt.RightButton) {
                           control.rightClicked()
                       }
                   }
    }
}

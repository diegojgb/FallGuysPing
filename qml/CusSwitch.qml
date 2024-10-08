import QtQuick
import QtQuick.Controls.Fusion

// Extracted from TaoQuick library
Switch {
    id: cusSwitch

    property color backgroundColor_on: root.accentColor
    property color indicatorColor_on: "#ffffff"

    property color backgroundColor_on_disable: Qt.darker(backgroundColor_on,
                                                         1.2)
    property color indicatorColor_on_disable: "#b6bdc5"

    property color backgroundColor_off: Qt.darker(root.sidebarBgColor, 1.3)
    property color indicatorColor_off: "#ffffff"

    property color backgroundColor_off_disable: "#919191"
    property color indicatorColor_off_disable: "#b6bdc5"

    spacing: 10
    padding: 0

    indicator: Rectangle {
        id: indicatorRect
        implicitWidth: 36
        implicitHeight: 20
        x: cusSwitch.leftPadding
        y: (parent.height - height) / 2
        radius: height / 2
        color: cusSwitch.enabled ? backgroundColor_off : backgroundColor_off_disable
        antialiasing: true
        smooth: true

        Rectangle {
            id: backgroundRect
            height: parent.height
            radius: parent.radius
            width: barRect.x + barRect.width - 1
            color: cusSwitch.enabled ? backgroundColor_on : backgroundColor_on_disable
            antialiasing: true
            smooth: true
        }

        Rectangle {
            id: barRect
            x: cusSwitch.checked ? parent.width - width : 0
            antialiasing: true
            smooth: true

            Behavior on x {
                NumberAnimation {
                    duration: 80
                }
            }

            height: parent.height
            width: height
            radius: width / 2
            color: cusSwitch.enabled ? (cusSwitch.checked ? indicatorColor_on : indicatorColor_off) : (cusSwitch.checked ? indicatorColor_on_disable : indicatorColor_off_disable)
            border.width: 1
            border.color: cusSwitch.checked ? backgroundColor_on : backgroundColor_off
        }
    }

    contentItem: Text {
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        elide: Text.ElideRight
        leftPadding: cusSwitch.indicator.width + cusSwitch.spacing
        bottomPadding: 2
        text: cusSwitch.text
        font: cusSwitch.font
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor

        onDoubleClicked: mouse => {
                             mouse.accepted = false
                         }
        onPositionChanged: mouse => {
                               mouse.accepted = false
                           }
        onPressed: mouse => {
                       mouse.accepted = false
                   }
        onPressAndHold: mouse => {
                            mouse.accepted = false
                        }
        onClicked: mouse => {
                       mouse.accepted = false
                   }
        onReleased: mouse => {
                        mouse.accepted = false
                    }
        onWheel: wheel => {
                     wheel.accepted = false
                 }
    }
}

import QtQuick
import QtQuick.Controls
import FallGuysPing

Window {
    id: root

    property int staticFlags: Qt.FramelessWindowHint | Qt.WA_TranslucentBackground
                              | Qt.WindowStaysOnTopHint
    property bool transparentInput: !Manager.settings.draggableText
    property bool draggable: Manager.settings.draggableText

    flags: transparentInput ? (staticFlags | Qt.WindowTransparentForInput) : staticFlags
    color: "#00000000"
    visible: true
    height: pingText.height
    width: pingText.width

    // x: Screen.width - pingText.width
    // y: 0
    DashedRectangle {
        anchors.fill: parent
        borderColor: "#aaa"
        visible: dragArea.containsMouse
    }

    Text {
        id: pingText
        text: Manager.pinger.latestPing
        color: "#fff"
        font.bold: true
        font.pointSize: 14
        rightPadding: 12
        leftPadding: 12
        bottomPadding: 3
        renderType: Text.NativeRendering
    }

    MouseArea {
        id: dragArea
        // cursorShape: pressed ? Qt.ClosedHandCursor : Qt.OpenHandCursor
        anchors.fill: parent
        hoverEnabled: true
        enabled: root.draggable

        property point clickPos: "1,1"

        onPressed: mouse => {
                       clickPos = Qt.point(mouse.x, mouse.y)
                   }

        onPositionChanged: mouse => {
                               if (dragArea.pressed) {
                                   var delta = Qt.point(mouse.x - clickPos.x,
                                                        mouse.y - clickPos.y)
                                   root.x += delta.x
                                   root.y += delta.y
                               }
                           }
    }
}

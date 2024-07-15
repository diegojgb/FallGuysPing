import QtQuick
import QtQuick.Controls
import FallGuysPing
import TextCorner 1.0

Window {
    id: root

    property int staticFlags: Qt.FramelessWindowHint | Qt.WA_TranslucentBackground
                              | Qt.WindowStaysOnTopHint
    property bool transparentInput: !Manager.settings.draggableText
    property bool draggable: Manager.settings.draggableText
    property int textCorner: Manager.settings.textCorner

    flags: transparentInput ? (staticFlags | Qt.WindowTransparentForInput) : staticFlags
    color: "#00000000"
    visible: false
    height: pingText.height
    width: pingText.width

    Component.onCompleted: {
        root.x = calcX(root.textCorner)
        root.y = calcY(root.textCorner)
        root.visible = true
    }

    onTextCornerChanged: {
        root.x = calcX(root.textCorner)
        root.y = calcY(root.textCorner)
    }

    function calcY(corner) {
        if (corner === TextCorner.TopLeft || corner === TextCorner.TopRight)
            return -4

        if (corner === TextCorner.BottomLeft
                || corner === TextCorner.BottomRight)
            return Screen.height - pingText.height + 4

        return root.y
    }

    function calcX(corner) {
        if (corner === TextCorner.TopLeft || corner === TextCorner.BottomLeft)
            return -pingText.leftPadding + 3

        if (corner === TextCorner.TopRight || corner === TextCorner.BottomRight)
            return Screen.width - pingText.width + pingText.rightPadding - 3

        return root.y
    }

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

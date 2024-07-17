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
    property int textPadding: 12

    flags: transparentInput ? (staticFlags | Qt.WindowTransparentForInput) : staticFlags
    color: "#00000000"
    visible: false
    height: pingText.height
    width: pingText.width

    Component.onCompleted: {
        root.bindXY(root.textCorner)
        root.visible = true
    }

    onTextCornerChanged: {
        if (root.textCorner === TextCorner.Custom)
            return

        root.bindXY(root.textCorner)
    }

    function bindXY(corner) {
        bindX(corner)
        bindY(corner)
    }

    function bindX(corner) {
        if (corner === TextCorner.TopLeft || corner === TextCorner.BottomLeft)
            root.x = Qt.binding(function () {
                return -pingText.leftPadding + 3
            })

        if (corner === TextCorner.TopRight || corner === TextCorner.BottomRight)
            root.x = Qt.binding(function () {
                return Screen.width - pingText.width + pingText.rightPadding - 3
            })
    }

    function bindY(corner) {
        if (corner === TextCorner.TopLeft || corner === TextCorner.TopRight)
            root.y = -8

        if (corner === TextCorner.BottomLeft
                || corner === TextCorner.BottomRight)
            root.y = Qt.binding(function () {
                return Screen.height - pingText.height + 10
            })
    }

    DashedRectangle {
        anchors.fill: parent
        borderColor: "#aaa"
        visible: dragArea.containsMouse
    }

    TextMetrics {
        id: textMetrics
        font: pingText.font
        text: "0123456789"
    }

    FontMetrics {
        id: fontMetrics
        font: pingText.font
    }

    Text {
        id: pingText

        property int prevTextLen
        property int prevWidth

        text: Manager.pinger.latestPing
        color: Manager.settings.textColor
        font.pointSize: Manager.settings.textSize
        style: Manager.settings.textOutline ? Text.Outline : Text.Normal
        font.bold: Manager.settings.boldText
        font.family: Manager.settings.fontFamily

        rightPadding: root.textPadding
        leftPadding: root.textPadding
        topPadding: textMetrics.tightBoundingRect.height - fontMetrics.ascent + root.textPadding
        bottomPadding: -fontMetrics.descent + root.textPadding
        renderType: Text.NativeRendering

        Component.onCompleted: {
            pingText.prevWidth = pingText.width
            pingText.prevTextLen = pingText.text.length
        }

        onTextChanged: {
            if (root.textCorner !== TextCorner.Custom)
                return

            var middleLine = Screen.width / 2
            if (root.x <= middleLine)
                return

            if (pingText.text.length !== pingText.prevTextLen) {
                var newSpace = pingText.width - pingText.prevWidth
                root.x = root.x - newSpace

                pingText.prevTextLen = pingText.text.length
                pingText.prevWidth = pingText.width
            }
        }
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

                                   Manager.settings.textCorner = TextCorner.Custom
                               }
                           }
    }
}

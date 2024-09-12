import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
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
    height: overlayBox.height + root.textPadding * 2
    width: overlayBox.width + root.textPadding * 2

    Component.onCompleted: {
        if (root.textCorner === TextCorner.Custom) {
            var savedPoint = Manager.settings.getSavedPosition()
            root.x = savedPoint.x - root.width
            root.y = savedPoint.y
        } else {
            root.bindXY(root.textCorner)
        }

        root.visible = Qt.binding(function () {
            return Manager.settings.alwaysVisible || Manager.isGameActive
        })
    }

    // For testing purposes.
    // Timer {
    //     property int i: 0

    //     interval: 2000
    //     running: true
    //     repeat: true
    //     onTriggered: {
    //         pingText.text += i.toString()
    //         i += 1
    //     }
    // }

    // Timer {
    //     interval: 3000
    //     running: true
    //     repeat: true
    //     onTriggered: {
    //         pingText.text = pingText.text.substring(0, pingText.text.length - 1)
    //     }
    // }
    Component.onDestruction: {
        if (root.textCorner === TextCorner.Custom) {
            var x = root.x + root.width
            Manager.settings.savePosition(Qt.point(x, root.y))
        }
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
                return -root.textPadding + 4
            })

        if (corner === TextCorner.TopRight || corner === TextCorner.BottomRight)
            root.x = Qt.binding(function () {
                return Screen.width - overlayBox.width - root.textPadding - 4
            })
    }

    function bindY(corner) {
        if (corner === TextCorner.TopLeft || corner === TextCorner.TopRight)
            root.y = -root.textPadding - 4

        if (corner === TextCorner.BottomLeft
                || corner === TextCorner.BottomRight)
            root.y = Qt.binding(function () {
                return Screen.height - overlayBox.height - root.textPadding
            })
    }

    DashedRectangle {
        anchors.fill: parent
        borderColor: "#aaa"
        visible: dragArea.containsMouse
    }

    Rectangle {
        height: overlayBox.height
        width: overlayBox.width + fontMetrics.descent * 2

        anchors.horizontalCenter: parent.horizontalCenter
        y: (parent.height - height) / 2 + fontMetrics.descent * 0.2

        visible: Manager.settings.bgEnabled
        color: Manager.settings.bgColor
    }

    FontMetrics {
        id: fontMetrics
        font: pingText.font
    }

    RowLayout {
        id: overlayBox
        spacing: 7
        anchors.centerIn: parent

        property int prevWidth
        property bool infoVisible: Manager.settings.locationOverlayEnabled
                                   && Manager.geoLocator.country !== ""

        Component.onCompleted: {
            overlayBox.prevWidth = overlayBox.width
        }

        onWidthChanged: {
            if (root.textCorner !== TextCorner.Custom)
                return

            var middleLine = Screen.width / 2
            if (root.x <= middleLine)
                return

            if (overlayBox.width !== overlayBox.prevWidth) {
                var newSpace = overlayBox.width - overlayBox.prevWidth
                root.x = root.x - newSpace

                overlayBox.prevWidth = overlayBox.width
            }
        }

        CustomText {
            id: serverText
            text: Manager.geoLocator.serverRegion
                  === "" ? Manager.geoLocator.country : Manager.geoLocator.serverRegion
            visible: overlayBox.infoVisible
        }

        CustomText {
            text: "·"
            visible: overlayBox.infoVisible
        }

        CustomText {
            id: regionText
            text: {
                if (Manager.geoLocator.country === "United States"
                        || Manager.geoLocator.serverRegion === "")
                    return Manager.geoLocator.region
                else
                    return Manager.geoLocator.country
            }
            visible: overlayBox.infoVisible
        }

        CustomText {
            text: "·"
            visible: overlayBox.infoVisible
        }

        CustomText {
            id: pingText

            text: Manager.pinger.latestPing

            property int prevTextLen
            property int prevWidth

            Component.onCompleted: {
                pingText.prevWidth = pingText.width
                pingText.prevTextLen = pingText.text.length
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

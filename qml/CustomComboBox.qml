import QtQuick
import QtQuick.Controls.Basic

ComboBox {
    id: control
    model: ["First", "Second", "Third"]

    property int popupHeight: 0

    delegate: ItemDelegate {
        id: itemDelegate

        width: control.width
        height: 28

        contentItem: Text {
            text: modelData
            font: control.font
            color: itemDelegate.hovered ? "#fff" : "#000"
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
            anchors.left: parent.left
            leftPadding: 8
        }

        highlighted: control.highlightedIndex === index

        background: Rectangle {
            color: itemDelegate.hovered ? root.accentColor : "#ebebeb"
        }
    }

    indicator: Item {
        id: canvasItem

        anchors.right: control.right
        anchors.rightMargin: 18
        anchors.verticalCenter: control.verticalCenter

        property color indicatorColor: "#606060"

        Canvas {
            id: lightCanvas

            width: 8
            height: 4
            contextType: "2d"
            anchors.verticalCenter: parent.verticalCenter

            onPaint: {
                context.reset()
                context.moveTo(0, 0)
                context.lineTo(width, 0)
                context.lineTo(width / 2, height)
                context.closePath()
                context.fillStyle = parent.indicatorColor
                context.fill()
            }
        }
    }

    contentItem: Text {
        leftPadding: 8
        bottomPadding: 2
        rightPadding: control.indicator.width + control.spacing

        text: control.displayText
        font: control.font
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        id: background

        implicitWidth: 128
        implicitHeight: 27
        color: root.sidebarBgColor
        border.color: "#ababab"
        border.width: 1
        radius: 2
    }

    onPressedChanged: background.color = pressed ? "#c3c3c3" : root.sidebarBgColor

    popup: Popup {
        id: popup

        y: control.height - 1
        width: control.width
        implicitHeight: control.popupHeight ? control.popupHeight : contentItem.implicitHeight
        padding: 1

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight + 2 // Don't know why, but had to add that 2 pixel correction when using a custom background for the delegateItems.
            model: control.popup.visible ? control.delegateModel : null
            currentIndex: control.highlightedIndex

            ScrollBar.vertical: ScrollBar {
                policy: ScrollBar.AlwaysOn
            }
        }

        background: Rectangle {
            border.color: '#aaa'
            radius: 2
        }

        onVisibleChanged: background.color = visible ? "#c3c3c3" : root.sidebarBgColor
    }
}

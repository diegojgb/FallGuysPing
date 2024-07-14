import QtQuick

Window {
    id: pingTextWindow

    property int staticFlags: Qt.FramelessWindowHint | Qt.WA_TranslucentBackground
                              | Qt.WindowStaysOnTopHint
    property bool transparentInput: true

    flags: transparentInput ? (staticFlags | Qt.WindowTransparentForInput) : staticFlags

    color: "#00000000"
    visible: true
    height: pingText.height
    width: pingText.width
    x: Screen.width - pingText.width
    y: 0

    Text {
        id: pingText
        text: Manager.pinger.latestPing
        color: "#fff"
        font.bold: true
        font.pointSize: 14
        topPadding: -3
        rightPadding: 3
        renderType: Text.NativeRendering
    }
}

import QtQuick

Window {
    id: pingTextWindow

    flags: Qt.FramelessWindowHint | Qt.WA_TranslucentBackground
           | Qt.WindowStaysOnTopHint | Qt.WindowTransparentForInput
    color: "#00000000"
    x: 0
    y: 0
    width: 100
    height: 100
    visible: true

    Text {
        id: pingText
        text: Manager.pinger.latestPing
        color: "#fff"
        font.bold: true
        font.pointSize: 14
        topPadding: -3
        leftPadding: 3
        renderType: Text.NativeRendering
    }
}

import QtQuick

Text {
    id: control
    color: Manager.settings.textColor
    font.pointSize: Manager.settings.textSize
    style: Manager.settings.textOutline ? Text.Outline : Text.Normal
    font.bold: Manager.settings.boldText
    font.family: Manager.settings.fontFamily

    // rightPadding: root.textPadding
    // leftPadding: root.textPadding
    // topPadding: textMetrics.tightBoundingRect.height - fontMetrics.ascent + root.textPadding
    // bottomPadding: -fontMetrics.descent + root.textPadding

    // TextMetrics {
    //     id: textMetrics
    //     font: control.font
    //     text: control.text
    // }

    // FontMetrics {
    //     id: fontMetrics
    //     font: control.font
    // }
}

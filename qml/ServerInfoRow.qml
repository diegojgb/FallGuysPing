import QtQuick

Rectangle {
    id: control
    width: parent.width
    height: control.props.rowHeight
    color: control.useMainColor ? control.props.mainColor : control.props.alternateColor
    border.width: 1
    border.color: control.props.borderColor

    required property ServerInfoProps props
    property alias labelText: labelItem.text
    property alias valueText: valueItem.text
    property alias selectable: valueItem.selectByMouse
    property bool useMainColor: true

    Text {
        id: labelItem
        anchors.left: parent.left
        anchors.leftMargin: control.props.rowLeftMargin
        anchors.verticalCenter: parent.verticalCenter
        font.pointSize: control.props.fontSize
        font.weight: Font.DemiBold
    }

    TextEdit {
        id: valueItem
        anchors.left: borderRect.right
        anchors.leftMargin: 6
        height: parent.height
        readOnly: true
        selectByMouse: true
        font.pointSize: control.props.fontSize
        verticalAlignment: Text.AlignVCenter
    }

    Rectangle {
        id: borderRect
        anchors.left: parent.left
        anchors.leftMargin: control.props.borderleftMargin
        height: parent.height
        width: 1
        color: control.props.borderColor
    }
}

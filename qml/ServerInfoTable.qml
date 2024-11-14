import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Column {
    id: control
    spacing: -1

    property ServerInfoProps props: ServerInfoProps {}
    property bool locationActive: Manager.geoLocator.active

    Rectangle {
        color: control.props.alternateColor
        width: parent.width
        height: 40
        border.width: 1
        border.color: control.props.borderColor
        topLeftRadius: control.props.radius
        topRightRadius: control.props.radius

        RowLayout {
            anchors.fill: parent
            spacing: 0

            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true

                Image {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    source: control.locationActive ? 'qrc:/assets/flags/%1.png'.arg(
                                                         Manager.geoLocator.countryCode.toLowerCase(
                                                             )) : ""
                }
            }

            Text {
                Layout.preferredWidth: control.width - control.props.borderleftMargin
                Layout.alignment: Qt.AlignRight
                Layout.fillHeight: true
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: control.locationActive ? Manager.geoLocator.serverRegion
                                               === "" ? "?" : Manager.geoLocator.serverRegion : "-"
                font.pointSize: 13
                font.weight: Font.DemiBold
            }
        }

        Rectangle {
            anchors.left: parent.left
            anchors.leftMargin: control.props.borderleftMargin
            height: parent.height
            width: 1
            color: control.props.borderColor
        }
    }

    ServerInfoRow {
        props: control.props
        useMainColor: true
        labelText: "IP addr."
        valueText: control.locationActive ? Manager.ip : "-"
    }

    ServerInfoRow {
        props: control.props
        useMainColor: false
        labelText: "Country"
        valueText: control.locationActive ? Manager.geoLocator.country : "-"
    }

    ServerInfoRow {
        props: control.props
        useMainColor: true
        labelText: "Region"
        valueText: control.locationActive ? Manager.geoLocator.region : "-"
    }

    ServerInfoRow {
        props: control.props
        useMainColor: false
        labelText: "City"
        valueText: control.locationActive ? Manager.geoLocator.city : "-"
    }

    ServerInfoRow {
        props: control.props
        useMainColor: true
        labelText: "Time"
        valueText: control.locationActive ? Manager.stopwatch.elapsedTime : "-"
        selectable: false
        bottomLeftRadius: control.props.radius
        bottomRightRadius: control.props.radius
    }
}

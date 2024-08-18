import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    implicitWidth: pingItem.width
    implicitHeight: pingItem.height
    radius: 6
    border.width: 1
    border.color: "#ccc"
    color: "transparent"

    ColumnLayout {
        id: pingItem
        height: 150
        spacing: pingItem.cusSpacing
        z: -1

        property int cusSpacing: 2
        property int radius: 6
        property int padding: 20
        property int boxWidth: Math.max(minBox.implicitWidth,
                                        avgBox.implicitWidth,
                                        maxBox.implicitWidth,
                                        avg10Box.implicitWidth,
                                        56) + pingItem.padding

        PingBox {
            id: pingBox
            Layout.fillHeight: true
            Layout.preferredWidth: pingItem.boxWidth * 2
            pingSize: 16
            header: "Ping"
            ping: Manager.pinger.latestPing
            topLeftRadius: serverInfo.props.radius
            topRightRadius: serverInfo.props.radius
        }

        RowLayout {
            Layout.fillHeight: true
            Layout.maximumWidth: pingItem.boxWidth * 2
            spacing: pingItem.cusSpacing

            PingBox {
                id: minBox
                Layout.fillHeight: true
                Layout.fillWidth: true
                header: "Avg"
                ping: Manager.pinger.avgPing
            }

            PingBox {
                id: avgBox
                Layout.fillHeight: true
                Layout.fillWidth: true
                header: "Avg(10)"
                ping: Manager.pinger.avg10Ping
            }
        }

        RowLayout {
            Layout.fillHeight: true
            Layout.maximumWidth: pingItem.boxWidth * 2
            spacing: pingItem.cusSpacing

            PingBox {
                id: maxBox
                Layout.fillHeight: true
                Layout.fillWidth: true
                header: "Min"
                ping: Manager.pinger.minPing
                bottomLeftRadius: serverInfo.props.radius
            }

            PingBox {
                id: avg10Box
                Layout.fillHeight: true
                Layout.fillWidth: true
                header: "Max"
                ping: Manager.pinger.maxPing
                bottomRightRadius: serverInfo.props.radius
            }
        }
    }
}

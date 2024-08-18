import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.qmlmodels

ColumnLayout {
    id: page

    Label {
        text: 'Current server'
        font.pointSize: 17
    }

    RowLayout {
        id: mainRow
        Layout.topMargin: 15
        spacing: 10

        ServerInfoTable {
            id: serverInfo
            Layout.alignment: Qt.AlignTop
            Layout.preferredWidth: page.width - pingDashboard.width
                                   - page.anchors.leftMargin - mainRow.spacing
        }

        PingDashboard {
            id: pingDashboard
        }
    }

    // Label {
    //     Layout.topMargin: 10
    //     text: 'History'
    //     font.pointSize: 15
    //     font.weight: Font.DemiBold
    // }

    // Item {
    //     id: table
    //     Layout.topMargin: 10
    //     Layout.preferredWidth: tableView.contentWidth
    //     Layout.preferredHeight: tableView.contentHeight + horizontalHeader.height

    //     property color gridLineColor: "#ccc"
    //     property color cellBgColor: "#eee"
    //     property color headerBgColor: "#333"
    //     property color headerTextColor: "#fff"

    //     HorizontalHeaderView {
    //         id: horizontalHeader
    //         anchors.left: tableView.left
    //         anchors.top: parent.top
    //         syncView: tableView
    //         height: 20
    //         clip: true
    //         model: ["Server", "Avg", "Location", "IP"]
    //         interactive: false

    //         delegate: Rectangle {
    //             implicitHeight: 20
    //             implicitWidth: 50
    //             border.width: 1
    //             border.color: table.gridLineColor
    //             color: table.headerBgColor

    //             Text {
    //                 text: modelData
    //                 anchors.fill: parent
    //                 color: table.headerTextColor
    //                 horizontalAlignment: Text.AlignHCenter
    //                 verticalAlignment: Text.AlignVCenter
    //                 textFormat: Text.PlainText
    //             }
    //         }
    //     }

    //     TableView {
    //         id: tableView
    //         anchors.left: parent.left
    //         anchors.top: horizontalHeader.bottom
    //         anchors.right: parent.right
    //         anchors.bottom: parent.bottom
    //         clip: true

    //         columnSpacing: -1
    //         rowSpacing: -1

    //         property var columnWidths: [100, 50, 200, 90]
    //         property int rowCount: model.rowCount

    //         function getColumnWidth(column) {
    //             return tableView.columnWidths[column]
    //         }

    //         model: TableModel {
    //             TableModelColumn {
    //                 display: "Server"
    //             }
    //             TableModelColumn {
    //                 display: "Avg"
    //             }
    //             TableModelColumn {
    //                 display: "Location"
    //             }
    //             TableModelColumn {
    //                 display: "IP"
    //             }

    //             rows: [{
    //                     "Server": "South America",
    //                     "Avg": "135ms",
    //                     "Location": "Brazil, Sao Paulo, Rio de Janeiro",
    //                     "IP": "63.251.114.36"
    //                 }, {
    //                     "Server": "India and the Middle East",
    //                     "Avg": "132ms",
    //                     "Location": "Brazil, Sao Paulo, Rio de Janeiro",
    //                     "IP": "63.251.114.36"
    //                 }, {
    //                     "Server": "South America",
    //                     "Avg": "137ms",
    //                     "Location": "Brazil, Sao Paulo, Rio de Janeiro",
    //                     "IP": "63.251.114.36"
    //                 }]
    //         }

    //         delegate: Rectangle {
    //             id: delegate
    //             implicitWidth: tableView.getColumnWidth(
    //                                Math.floor(model.index / tableView.rowCount))
    //             implicitHeight: Math.max(20, cellText.contentHeight)
    //             color: table.cellBgColor
    //             border.color: table.gridLineColor
    //             border.width: 1

    //             TextEdit {
    //                 id: cellText
    //                 anchors.fill: parent
    //                 horizontalAlignment: TextEdit.AlignLeft
    //                 verticalAlignment: TextEdit.AlignVCenter
    //                 leftPadding: 5
    //                 wrapMode: TextEdit.Wrap
    //                 readOnly: true
    //                 clip: true
    //                 text: model.display
    //             }
    //         }
    //     }
    // }
}

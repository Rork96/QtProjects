import QtQuick 2.0

Item { // ToolsArea
    anchors.fill: parent

    Rectangle {
        anchors.fill: parent
        color: "transparent"

        Row {
            anchors.fill: parent
            spacing: 25

            Column {
                width: parent.width/4 -parent.spacing/3
                spacing: 20

                SimpleItem {
                    width: parent.width
                    anchors.margins: 15
                    text: qsTr("Uninstaller")
                    source: "qrc:/pict/info.png"
                    imageWidth: 32
//                    onMouseClicked: aboutDlg.open()
                }

                SimpleItem {
                    width: parent.width
                    anchors.margins: 15
                    text: qsTr("Uninstaller")
                    source: "qrc:/pict/info.png"
                    imageWidth: 32
//                    onMouseClicked: aboutDlg.open()
                }

                SimpleItem {
                    width: parent.width
                    anchors.margins: 15
                    text: qsTr("Uninstaller")
                    source: "qrc:/pict/info.png"
                    imageWidth: 32
//                    onMouseClicked: aboutDlg.open()
                }
            }

            Column {
                width: parent.width/4 -parent.spacing/3
                spacing: 10

                SimpleItem {

                }
                SimpleItem {

                }
                SimpleItem {

                }
            }

            Column {
                width: parent.width/4 -parent.spacing/3
                spacing: 10

                SimpleItem {

                }
                SimpleItem {

                }
                SimpleItem {

                }
            }

            Column {
                width: parent.width/4 -parent.spacing/3
                spacing: 10

                SimpleItem {

                }
                SimpleItem {

                }
                SimpleItem {

                }
            }
        }
    }
}

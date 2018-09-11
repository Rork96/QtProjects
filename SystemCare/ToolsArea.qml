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
                    text: qsTr("Booster")
                    source: "qrc:/pict/info.png"
                    imageWidth: 32
//                    onMouseClicked: aboutDlg.open()
                }

                SimpleItem {
                    width: parent.width
                    anchors.margins: 15
                    text: qsTr("Defrag")
                    source: "qrc:/pict/info.png"
                    imageWidth: 32
//                    onMouseClicked: aboutDlg.open()
                }

                SimpleItem {
                    width: parent.width
                    anchors.margins: 15
                    text: qsTr("Malware Fighter")
                    source: "qrc:/pict/info.png"
                    imageWidth: 32
//                    onMouseClicked: aboutDlg.open()
                }
            }

            Column {
                width: parent.width/4 -parent.spacing/3
                spacing: 20

                SimpleItem {
                    width: parent.width
                    anchors.margins: 15
                    text: qsTr("Менеджер по запуску")
                    source: "qrc:/pict/info.png"
                    imageWidth: 32
//                    onMouseClicked: aboutDlg.open()
                }

                SimpleItem {
                    width: parent.width
                    anchors.margins: 15
                    text: qsTr("Оперативная память")
                    source: "qrc:/pict/info.png"
                    imageWidth: 32
//                    onMouseClicked: aboutDlg.open()
                }

                SimpleItem {
                    width: parent.width
                    anchors.margins: 15
                    text: qsTr("Интернет ускоритель")
                    source: "qrc:/pict/info.png"
                    imageWidth: 32
//                    onMouseClicked: aboutDlg.open()
                }

                SimpleItem {
                    width: parent.width
                    anchors.margins: 15
                    text: qsTr("Автовыключение")
                    source: "qrc:/pict/info.png"
                    imageWidth: 32
//                    onMouseClicked: aboutDlg.open()
                }

                SimpleItem {
                    width: parent.width
                    anchors.margins: 15
                    text: qsTr("Деактиватор программ")
                    source: "qrc:/pict/info.png"
                    imageWidth: 32
//                    onMouseClicked: aboutDlg.open()
                }
            }

            Column {
                width: parent.width/4 -parent.spacing/3
                spacing: 20

                SimpleItem {
                    width: parent.width
                    anchors.margins: 15
                    text: qsTr("Ремонт системы")
                    source: "qrc:/pict/info.png"
                    imageWidth: 32
//                    onMouseClicked: aboutDlg.open()
                }

                SimpleItem {
                    width: parent.width
                    anchors.margins: 15
                    text: qsTr("Доктор диска")
                    source: "qrc:/pict/info.png"
                    imageWidth: 32
//                    onMouseClicked: aboutDlg.open()
                }

                SimpleItem {
                    width: parent.width
                    anchors.margins: 15
                    text: qsTr("Восстановление после удаления")
                    source: "qrc:/pict/info.png"
                    imageWidth: 32
//                    onMouseClicked: aboutDlg.open()
                }

                SimpleItem {
                    width: parent.width
                    anchors.margins: 15
                    text: qsTr("Уничтожитель файлов")
                    source: "qrc:/pict/info.png"
                    imageWidth: 32
//                    onMouseClicked: aboutDlg.open()
                }

                SimpleItem {
                    width: parent.width
                    anchors.margins: 15
                    text: qsTr("Программы по умолчанию")
                    source: "qrc:/pict/info.png"
                    imageWidth: 32
//                    onMouseClicked: aboutDlg.open()
                }
            }

            Column {
                width: parent.width/4 -parent.spacing/3
                spacing: 20

                SimpleItem {
                    width: parent.width
                    anchors.margins: 15
                    text: qsTr("Очистка реестра")
                    source: "qrc:/pict/info.png"
                    imageWidth: 32
//                    onMouseClicked: aboutDlg.open()
                }

                SimpleItem {
                    width: parent.width
                    anchors.margins: 15
                    text: qsTr("Очистка диска")
                    source: "qrc:/pict/info.png"
                    imageWidth: 32
//                    onMouseClicked: aboutDlg.open()
                }

                SimpleItem {
                    width: parent.width
                    anchors.margins: 15
                    text: qsTr("Поиск больших файлов")
                    source: "qrc:/pict/info.png"
                    imageWidth: 32
//                    onMouseClicked: aboutDlg.open()
                }

                SimpleItem {
                    width: parent.width
                    anchors.margins: 15
                    text: qsTr("Поиск пустых папок")
                    source: "qrc:/pict/info.png"
                    imageWidth: 32
//                    onMouseClicked: aboutDlg.open()
                }

                SimpleItem {
                    width: parent.width
                    anchors.margins: 15
                    text: qsTr("Битые ярлыки")
                    source: "qrc:/pict/info.png"
                    imageWidth: 32
//                    onMouseClicked: aboutDlg.open()
                }
            }
        }
    }
}

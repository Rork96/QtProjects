import QtQuick 2.0

Item { // ToolsArea
    anchors.fill: parent

    Rectangle {
        id: mainRect
        anchors.fill: parent
        color: "transparent"

        Row {
            anchors.right: mainRect.right
            anchors.bottom: mainRect.bottom
            width: mainRect.width - 30
            height: mainRect.height - 50
            spacing: 30

            Rectangle {
                id: rect
                width: mainRect.width/4 - parent.spacing/3 - 25
                height: mainRect.height - 50
                color: "white"
                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: "transparent"
                    }
                    GradientStop {
                        position: 0.5
                        color: Qt.darker("grey")
                    }
                    GradientStop {
                        position: 1.00
                        color: "transparent"
                    }
                }

                Column {
                    id: mainColumn
                    width: parent.width/4 - parent.spacing/3
                    spacing: 40

                    Text {
                        text: "Продукция"
                        font.pixelSize: 20
                        color: "white"
                        opacity: 0.7
                    }

                    SimpleItem {
                        id: uninstItem
                        width: parent.width
                        anchors.margins: 15
                        text: qsTr("Uninstaller")
                        fontSize: 20
                        source: "qrc:/pict/uninstall.png"
                        imageWidth: 36
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Booster")
                        fontSize: uninstItem.fontSize
                        source: "qrc:/pict/boost.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Defrag")
                        fontSize: uninstItem.fontSize
                        source: "qrc:/pict/defrag.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Malware Fighter")
                        fontSize: uninstItem.fontSize
                        source: "qrc:/pict/defend.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }
                }
            }

            Rectangle {
                width: rect.width
                height: rect.height
                color: "white"
                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: "transparent"
                    }
                    GradientStop {
                        position: 0.5
                        color: Qt.darker("grey")
                    }
                    GradientStop {
                        position: 1.00
                        color: "transparent"
                    }
                }

                Column {
                    width: mainColumn.width
                    spacing: mainColumn.spacing

                    Text {
                        text: "Оптимизация системы"
                        font.pixelSize: 20
                        color: "white"
                        opacity: 0.7
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Менеджер по запуску")
                        fontSize: uninstItem.fontSize
                        source: "qrc:/pict/flash.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Оперативная память")
                        fontSize: uninstItem.fontSize
                        source: "qrc:/pict/memory.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Интернет ускоритель")
                        fontSize: uninstItem.fontSize
                        source: "qrc:/pict/globe.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Автовыключение")
                        fontSize: uninstItem.fontSize
                        source: "qrc:/pict/power_off.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Деактиватор программ")
                        fontSize: uninstItem.fontSize
                        source: "qrc:/pict/window.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }
                }
            }

            Rectangle {
                width: rect.width
                height: rect.height
                color: "white"
                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: "transparent"
                    }
                    GradientStop {
                        position: 0.5
                        color: Qt.darker("grey")
                    }
                    GradientStop {
                        position: 1.00
                        color: "transparent"
                    }
                }

                Column {
                    width: mainColumn.width
                    spacing: mainColumn.spacing

                    Text {
                        text: "Безопасность и ремонт"
                        font.pixelSize: 20
                        color: "white"
                        opacity: 0.7
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Ремонт системы")
                        fontSize: uninstItem.fontSize
                        source: "qrc:/pict/repair.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Доктор диска")
                        fontSize: uninstItem.fontSize
                        source: "qrc:/pict/hard_disk.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Восстанов. после удаления")
                        fontSize: uninstItem.fontSize
                        source: "qrc:/pict/backup.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Уничтожитель файлов")
                        fontSize: uninstItem.fontSize
                        source: "qrc:/pict/shredder.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Программы по умолчанию")
                        fontSize: uninstItem.fontSize
                        source: "qrc:/pict/adjust.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }
                }
            }

            Rectangle {
                width: rect.width
                height: rect.height
                color: "white"
                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: "transparent"
                    }
                    GradientStop {
                        position: 0.5
                        color: Qt.darker("grey")
                    }
                    GradientStop {
                        position: 1.00
                        color: "transparent"
                    }
                }

                Column {
                    width: mainColumn.width
                    spacing: mainColumn.spacing

                    Text {
                        text: "Очистка системы"
                        font.pixelSize: 20
                        color: "white"
                        opacity: 0.7
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Очистка реестра")
                        fontSize: uninstItem.fontSize
                        source: "qrc:/pict/defragment.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Очистка диска")
                        fontSize: uninstItem.fontSize
                        source: "qrc:/pict/disk_clean.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Поиск больших файлов")
                        fontSize: uninstItem.fontSize
                        source: "qrc:/pict/filereplace.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Поиск пустых папок")
                        fontSize: uninstItem.fontSize
                        source: "qrc:/pict/folder_search.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Битые ярлыки")
                        fontSize: uninstItem.fontSize
                        source: "qrc:/pict/label.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }
                }
            }
        }
    }
}

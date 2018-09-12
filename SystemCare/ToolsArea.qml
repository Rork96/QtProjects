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
                    spacing: 35

                    Text {
                        text: "Продукция"
                        font.pixelSize: 18
                        color: "white"
                        opacity: 0.7
                    }

                    SimpleItem {
                        id: uninstItem
                        width: parent.width
                        anchors.margins: 15
                        text: qsTr("Uninstaller")
                        source: "qrc:/pict/info.png"
                        imageWidth: 42
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Booster")
                        source: "qrc:/pict/info.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Defrag")
                        source: "qrc:/pict/info.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Malware Fighter")
                        source: "qrc:/pict/info.png"
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
                        font.pixelSize: 18
                        color: "white"
                        opacity: 0.7
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Менеджер по запуску")
                        source: "qrc:/pict/info.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Оперативная память")
                        source: "qrc:/pict/info.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Интернет ускоритель")
                        source: "qrc:/pict/info.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Автовыключение")
                        source: "qrc:/pict/info.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Деактиватор программ")
                        source: "qrc:/pict/info.png"
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
                        font.pixelSize: 18
                        color: "white"
                        opacity: 0.7
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Ремонт системы")
                        source: "qrc:/pict/info.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Доктор диска")
                        source: "qrc:/pict/info.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Восстановл. после удаления")
                        source: "qrc:/pict/info.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Уничтожитель файлов")
                        source: "qrc:/pict/info.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Программы по умолчанию")
                        source: "qrc:/pict/info.png"
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
                        font.pixelSize: 18
                        color: "white"
                        opacity: 0.7
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Очистка реестра")
                        source: "qrc:/pict/info.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Очистка диска")
                        source: "qrc:/pict/info.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Поиск больших файлов")
                        source: "qrc:/pict/info.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Поиск пустых папок")
                        source: "qrc:/pict/info.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    SimpleItem {
                        width: parent.width
                        anchors.margins: uninstItem.anchors.margins
                        text: qsTr("Битые ярлыки")
                        source: "qrc:/pict/info.png"
                        imageWidth: uninstItem.imageWidth
                        onMouseClicked: console.log(text)
                    }
                }
            }
        }
    }
}

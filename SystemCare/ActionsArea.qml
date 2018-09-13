import QtQuick 2.0
import QtQuick.Controls 2.2

Item { // ActionsArea
    anchors.fill: parent

    Flickable {
        width: parent.width
        height: parent.height - 0.1
        clip: true
        contentWidth: parent.width;
        contentHeight: parent.height
        ScrollBar.vertical: ScrollBar { }

        Rectangle {
            x: 0
            y: 50
            height: parent.height - y
            width: parent.width
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "transparent"
                }
                GradientStop {
                    position: 0.2
                    color: Qt.darker("blue", 4.0)
                }
                GradientStop {
                    position: 0.8
                    color: Qt.darker("blue", 4.0)
                }
                GradientStop {
                    position: 1.00
                    color: "transparent"
                }
            }

            Column {
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.width - 20
                spacing: 10

                Text {
                    text: "Безопасность и производительность"
                    font.pixelSize: 20
                    color: "white"
                    opacity: 0.7
                }

                Grid {
                    rows: 4
                    columns: 4
                    spacing: 15
                    width: parent.width

                    SimpleItem {
                        id: driverUpdate
                        width: parent.width/3
                        text: qsTr("Программа обновления драйверов")
                        fontSize: 18
                        source: "qrc:/pict/warning.png"
                        imageWidth: 28
                        onMouseClicked: console.log(text)
                    }

                    Column {
                        width: driverUpdate.width + 80

                        Text {
                            text: "Рекомендуем: Установите Booster"
                            font.pixelSize: 16
                            color: "white"
                            opacity: 0.7
                        }

                        Text {
                            text: "Обновление устаревших драйверов и установка отсутствующих"
                            font.pixelSize: 14
                            color: "white"
                            opacity: 0.5
                        }
                    }

                    TextLink {
                        onMouseClick: console.log(text)
                    }

                    TextLink {
                        text: "\t\tПолучить сейчас"
                        color: "orange"
                        onMouseClick: console.log(text)
                    }

                    SimpleItem {
                        width: driverUpdate.width
                        text: qsTr("Защита от шпионского ПО")
                        fontSize: driverUpdate.fontSize
                        source: driverUpdate.source
                        imageWidth: driverUpdate.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    Column {
                        width: driverUpdate.width + 80

                        Text {
                            text: "Рекомендуем: Установите Malware Fighter"
                            font.pixelSize: 16
                            color: "white"
                            opacity: 0.7
                        }

                        Text {
                            text: "Получите лудшую защиту от шпионских программ"
                            font.pixelSize: 14
                            color: "white"
                            opacity: 0.5
                        }
                    }

                    TextLink {
                        onMouseClick: console.log(text)
                    }

                    TextLink {
                        text: "\t\tПолучить сейчас"
                        color: "orange"
                        onMouseClick: console.log(text)
                    }

                    SimpleItem {
                        width: driverUpdate.width
                        text: qsTr("Деинсталятор программ")
                        fontSize: driverUpdate.fontSize
                        source: driverUpdate.source
                        imageWidth: driverUpdate.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    Column {
                        width: driverUpdate.width + 80

                        Text {
                            text: "Рекомендуем: Установите Uninstaller"
                            font.pixelSize: 16
                            color: "white"
                            opacity: 0.7
                        }

                        Text {
                            text: "Удаление нежелательных программ, панелей инструментов и плагинов"
                            font.pixelSize: 14
                            color: "white"
                            opacity: 0.5
                        }
                    }

                    TextLink {
                        onMouseClick: console.log(text)
                    }

                    TextLink {
                        text: "\t\tПолучить сейчас"
                        color: "orange"
                        onMouseClick: console.log(text)
                    }

                    SimpleItem {
                        width: driverUpdate.width
                        text: qsTr("Инструмент резервного копирования")
                        fontSize: driverUpdate.fontSize
                        source: driverUpdate.source
                        imageWidth: driverUpdate.imageWidth
                        onMouseClicked: console.log(text)
                    }

                    Column {
                        width: driverUpdate.width + 80

                        Text {
                            text: "Рекомендуем: Установите Backupper Standard"
                            font.pixelSize: 16
                            color: "white"
                            opacity: 0.7
                        }

                        Text {
                            text: "Програмное обеспечение резервного копирования для защиты данных"
                            font.pixelSize: 14
                            color: "white"
                            opacity: 0.5
                        }
                    }

                    TextLink {
                        onMouseClick: console.log(text)
                    }

                    TextLink {
                        text: "\t\tПолучить сейчас"
                        color: "orange"
                        onMouseClick: console.log(text)
                    }
                }

                Text {
                    text: "Обновление ПО"
                    font.pixelSize: 20
                    color: "white"
                    opacity: 0.7
                }
            }
        }
    }
}

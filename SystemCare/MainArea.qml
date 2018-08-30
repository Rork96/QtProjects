import QtQuick 2.10
import QtQuick.Controls 2.2

Item {  // ClientArea
    anchors.fill: parent

    Rectangle {
        anchors.fill: parent
        color: "transparent"

        Rectangle {
            id: rectangle
            x: parent.width/2 - width/2
            y: height/2.5
            width: 200
            height: 200
            radius: 100
            color: "transparent"
            border.color: "#1313af"
            border.width: 5

            Text {
                anchors.centerIn: parent
                text: qsTr("ПУСК")
                font.pixelSize: 48
                color: "white"
            }

            SequentialAnimation {   // Animation at onClick
                id: animation
                NumberAnimation {
                    target: rectangle
                    properties: "opacity"
                    from: 1.0
                    to: 0.5
                    duration: 80
                }

                NumberAnimation {
                    target: rectangle
                    properties: "opacity"
                    from: 0.5
                    to: 0.8
                    duration: 80
                }
            }

            states: [   // Change scale dependent on the mouse behavior (entered or exited rect)
                State {
                    name: "Entered"
                    PropertyChanges {
                        target: rectangle
                        scale: 1.3
                    }
                },
                State {
                    name: "Exited"
                    PropertyChanges {
                        target: rectangle
                        scale: 1.0
                    }
                }
            ]

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onEntered: rectangle.state = "Entered"
                onExited: rectangle.state = "Exited"
                onClicked: {
                    // Start animation
                    animation.running = true
                    console.log("MainArea")
                }
            }

            Behavior on scale {
                NumberAnimation {
                    duration: 900
                    easing.type: Easing.OutBounce
                }
            }
        }

        Row {
            anchors.left: items.left
            anchors.bottom: items.top
            width: parent.width
            height: 60

            CheckBox {
                id: selectAll
                checked: true
                text: "<font color=\"white\">Выбрать все</font>"
                font.pixelSize: 16
            }
        }

        Row {
            id: items
            x: spacing
            y: parent.height - height
            width: parent.width
            height: 200
            spacing: 40

            Column {
                width: parent.width/4 - spacing
                height: 40
                spacing: 20

                CheckBox {
                    checked: true
                    text: "<font color=\"white\">Оптимизация загрузки</font>"
                    font.pixelSize: 16
                    onCheckStateChanged: {
                        if (checkState===true)
                            text: "<font color=\"grey\">Оптимизация загрузки</font>"
                        else
                            text: "<font color=\"white\">Оптимизация загрузки</font>"
                    }
                }

                CheckBox {
                    checked: true
                    text: "<font color=\"white\">Очистка реестра</font>"
                    font.pixelSize: 16
                }

                CheckBox {
                    checked: true
                    text: "<font color=\"white\">Дефрагм. реестра</font>"
                    font.pixelSize: 16
                }
            }

            Column {
                width: parent.width/4 - spacing
                height: 40
                spacing: 20

                CheckBox {
                    checked: true
                    text: "<font color=\"white\">Очистка конфиденц.</font>"
                    font.pixelSize: 16
                }

                CheckBox {
                    checked: true
                    text: "<font color=\"white\">Удал. шпионского ПО</font>"
                    font.pixelSize: 16
                }

                CheckBox {
                    checked: true
                    text: "<font color=\"white\">Укрепление безопасности</font>"
                    font.pixelSize: 16
                }
            }

            Column {
                width: parent.width/4 - spacing
                height: 40
                spacing: 20

                CheckBox {
                    checked: true
                    text: "<font color=\"white\">Удаление мусора</font>"
                    font.pixelSize: 16
                }

                CheckBox {
                    checked: true
                    text: "<font color=\"white\">Интернет ускорение</font>"
                    font.pixelSize: 16
                }

                CheckBox {
                    checked: true
                    text: "<font color=\"white\">Ремонт уязвимости</font>"
                    font.pixelSize: 16
                }

            }

            Column {
                width: parent.width/4 - spacing
                height: 40
                spacing: 20

                CheckBox {
                    checked: true
                    text: "<font color=\"white\">Ремонт ярлыков</font>"
                    font.pixelSize: 16
                }

                CheckBox {
                    checked: true
                    text: "<font color=\"white\">Оптимизация системы</font>"
                    font.pixelSize: 16
                }

                CheckBox {
                    checked: true
                    text: "<font color=\"white\">Оптимизация диска</font>"
                    font.pixelSize: 16
                }

            }
        }
    }
}

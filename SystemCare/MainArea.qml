import QtQuick 2.10
import QtQuick.Controls 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {  // ClientArea
    anchors.fill: parent

    property int controlsChecked: 12
    property bool check: false

    Rectangle {
        anchors.fill: parent
        color: "transparent"

        Rectangle {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: firstRow.top
            color: "transparent"

            Rectangle {
                id: rectangle
                anchors.centerIn: parent
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
        }

        Row {
            id: firstRow
            anchors.left: items.left
            anchors.bottom: items.top
            width: parent.width
            height: 60

            ControlBox {
                caption: qsTr("Выбрать все")
                checked: controlsChecked===12 ? false : true    // Reversed in ControlBox.qml
                onClicked: {
                    if (!check) check = true
                    else check = false
                }
            }
        }

        Row {
            id: items
            x: spacing
            y: parent.height - height
            width: parent.width
            height: 150
            spacing: 40

            Column {
                width: parent.width/4 - spacing
                height: 40
                spacing: 20

                ControlBox {
                    /* Checked by default */
                    caption: qsTr("Оптимизация загрузки")
                    checked: check
                    onClicked: !checked ? controlsChecked++ : controlsChecked--
                }

                ControlBox {
                    caption: qsTr("Очистка реестра")
                    checked: check
                    onClicked: !checked ? controlsChecked++ : controlsChecked--
                }

                ControlBox {
                    caption: qsTr("Дефрагм. реестра")
                    checked: check
                    onClicked: !checked ? controlsChecked++ : controlsChecked--
                }
            }

            Column {
                width: parent.width/4 - spacing
                height: 40
                spacing: 20

                ControlBox {
                    caption: qsTr("Очистка конфиденц.")
                    checked: check
                    onClicked: !checked ? controlsChecked++ : controlsChecked--
                }

                ControlBox {
                    caption: qsTr("Удал. шпионского ПО")
                    checked: check
                    onClicked: !checked ? controlsChecked++ : controlsChecked--
                }

                ControlBox {
                    caption: qsTr("Укрепление безопасности")
                    checked: check
                    onClicked: !checked ? controlsChecked++ : controlsChecked--
                }
            }

            Column {
                width: parent.width/4 - spacing
                height: 40
                spacing: 20

                ControlBox {
                    caption: qsTr("Удаление мусора")
                    checked: check
                    onClicked: !checked ? controlsChecked++ : controlsChecked--
                }

                ControlBox {
                    caption: qsTr("Интернет ускорение")
                    checked: check
                    onClicked: !checked ? controlsChecked++ : controlsChecked--
                }

                ControlBox {
                    caption: qsTr("Ремонт уязвимости")
                    checked: check
                    onClicked: !checked ? controlsChecked++ : controlsChecked--
                }
            }

            Column {
                width: parent.width/4 - spacing
                height: 40
                spacing: 20

                ControlBox {
                    caption: qsTr("Ремонт ярлыков")
                    checked: check
                    onClicked: !checked ? controlsChecked++ : controlsChecked--
                }

                ControlBox {
                    caption: qsTr("Оптимизация системы")
                    checked: check
                    onClicked: !checked ? controlsChecked++ : controlsChecked--
                }

                ControlBox {
                    caption: qsTr("Оптимизация диска")
                    checked: check
                    onClicked: !checked ? controlsChecked++ : controlsChecked--
                }
            }
        }
    }
}

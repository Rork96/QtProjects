import QtQuick 2.10
import QtQuick.Controls 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

Item {  // ClientArea
    anchors.fill: parent

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
                width: 250
                height: width
                radius: width/2
                color: "transparent"
                border.color: "#2513af"
                border.width: 0.1
                gradient: Gradient {
                    GradientStop {
                        position: 0.00
                        color: "transparent"
                    }
                    GradientStop {
                        position: 0.50;
                        color: Qt.lighter("#0b2880", 0.5);
                    }
                    GradientStop {
                        position: 1.00;
                        color: "transparent";
                    }
                }

                RectangularGlow {
                    id: glow
                    anchors.fill: rectangle
                    glowRadius: 10
                    spread: 0.2
                    color: "#5555ff"
                    cornerRadius: rectangle.radius + glowRadius
                }

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

                states: [   // Change the scale dependent on the mouse behavior (entered or exited rectangle)
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
                        console.log("ПУСК")
                    }
                }

                Behavior on scale { // When the scale is changed, play animation
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
                checkedState: Qt.Checked
                onCheckedStateChanged: console.log(caption + " - checked: " + checked)
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
                    checkedState: Qt.Checked
                    onCheckedStateChanged: console.log(caption + " - checked: " + checked)
                }

                ControlBox {
                    caption: qsTr("Очистка реестра")
                    checkedState: Qt.Checked
                    onCheckedStateChanged: console.log(caption + " - checked: " + checked)
                }

                ControlBox {
                    caption: qsTr("Дефрагм. реестра")
                    checkedState: Qt.Checked
                    onCheckedStateChanged: console.log(caption + " - checked: " + checked)
                }
            }

            Column {
                width: parent.width/4 - spacing
                height: 40
                spacing: 20

                ControlBox {
                    caption: qsTr("Очистка конфиденц.")
                    checkedState: Qt.Checked
                    onCheckedStateChanged: console.log(caption + " - checked: " + checked)
                }

                ControlBox {
                    caption: qsTr("Удал. шпионского ПО")
                    checkedState: Qt.Checked
                    onCheckedStateChanged: console.log(caption + " - checked: " + checked)
                }

                ControlBox {
                    caption: qsTr("Укрепление безопасности")
                    checkedState: Qt.Checked
                    onCheckedStateChanged: console.log(caption + " - checked: " + checked)
                }
            }

            Column {
                width: parent.width/4 - spacing
                height: 40
                spacing: 20

                ControlBox {
                    caption: qsTr("Удаление мусора")
                    checkedState: Qt.Checked
                    onCheckedStateChanged: console.log(caption + " - checked: " + checked)
                }

                ControlBox {
                    caption: qsTr("Интернет ускорение")
                    checkedState: Qt.Checked
                    onCheckedStateChanged: console.log(caption + " - checked: " + checked)
                }

                ControlBox {
                    caption: qsTr("Ремонт уязвимости")
                    checkedState: Qt.Checked
                    onCheckedStateChanged: console.log(caption + " - checked: " + checked)
                }
            }

            Column {
                width: parent.width/4 - spacing
                height: 40
                spacing: 20

                ControlBox {
                    caption: qsTr("Ремонт ярлыков")
                    checkedState: Qt.Checked
                    onCheckedStateChanged: console.log(caption + " - checked: " + checked)
                }

                ControlBox {
                    caption: qsTr("Оптимизация системы")
                    checkedState: Qt.Checked
                    onCheckedStateChanged: console.log(caption + " - checked: " + checked)
                }

                ControlBox {
                    caption: qsTr("Оптимизация диска")
                    checkedState: Qt.Checked
                    onCheckedStateChanged: console.log(caption + " - checked: " + checked)
                }
            }
        }
    }
}

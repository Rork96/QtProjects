import QtQuick 2.0

Item {  // ControlElement
    id: itemControl
    x: posX
    y: posY
    width: elemWidth
    height: elemHeight

    property int posX: 0
    property int posY: 0
    property int elemWidth: 300
    property int elemHeight: 450

    property string headerText: qsTr("Турбо ускорение: ")
    property string stateText: qsTr("ВЫКЛ")
    property string bodyText:qsTr("Сервисы/Приложения остановлены: 0 \nВысвобождено RAM: 0 MB Автозапуск: Выключено")
    property string buttonText: qsTr("Включить")
    property string imageSource: "qrc:/pict/speedtest.png"
    property bool bodyVisible: true
    property bool mouseHover: false

    Rectangle {
        id: baseRect
        anchors.fill: itemControl
        color: "transparent"

        Rectangle { // Body rectangle
            id: infoRect
            width: baseRect.width
            height: baseRect.height - imgRect.height/2
            anchors.left: baseRect.left
            anchors.right: baseRect.right
            anchors.bottom: baseRect.bottom
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

            MouseArea {
                anchors.fill: infoRect
                hoverEnabled: true
                onEntered: mouseHover = true
                onExited: mouseHover = false
            }

            Rectangle { // Body
                id: bodyRect
                height: infoRect.height - imgRect.height - bottomRect.height
                anchors.left: infoRect.left
                anchors.right: infoRect.right
                anchors.bottom: bottomRect.top
                color: "transparent"

                Row {
                    x: bodyRect.width/2 - width/2

                    Text {
                        text: headerText
                        font.pixelSize: 20
                        font.bold: true
                        color: "white"
                        elide: Text.ElideMiddle
                    }

                    Text {
                        id: optionState
                        text: stateText
                        font.pixelSize: 20
                        color: "blue"
                    }
                }

                Row {
                    x: bodyRect.width/2 - width/2
                    y: bodyVisible ? 100 : 0
                    visible: bodyVisible

                    Text {
                        width: bodyRect.width - 10
                        text: bodyText
                        font.pixelSize: 18
                        horizontalAlignment: Text.AlignHCenter
                        wrapMode: Text.Wrap
                        color: "white"
                        elide: Text.ElideMiddle
                    }
                }
            }

            Rectangle { // Bottom
                id: bottomRect
                anchors.left: infoRect.left
                anchors.right: infoRect.right
                anchors.bottom: infoRect.bottom
                height: 80
                color: "transparent"

                SimpleButton {
                    anchors.centerIn: bottomRect
                    itemText: buttonText
                    itemWidth: 150
                    onMouseClick: console.log(itemText)
                }
            }
        }

        Rectangle { // Image rectangle
            id: imgRect
            x: infoRect.width/2 - width/2
            anchors.top: parent.top
            width: 70
            height: width
            radius: width/2
            color: "transparent"

            Image {
                anchors.fill: imgRect
                anchors.centerIn: imgRect
                source: imageSource
                smooth: true
            }
        }
    }
}

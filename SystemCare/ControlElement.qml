import QtQuick 2.0

Item {  // ControlElement
    id: itemControl
    x: 0
    y: 0
    width: 300
    height: 450

    property alias headerText: headText.text
    property alias stateText: optionState.text
    property alias bodyText: body_Text.text
    property alias buttonText: button.text
    property alias source: imageSource.source
    property alias bodyVisible: bodyRow.visible
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
                        id: headText
                        text: qsTr("Турбо ускорение: ")
                        font.pixelSize: 20
                        font.bold: true
                        color: "white"
                        elide: Text.ElideMiddle
                    }

                    Text {
                        id: optionState
                        text: qsTr("ВЫКЛ") //stateText
                        font.pixelSize: 20
                        color: "blue"
                    }
                }

                Row {
                    id: bodyRow
                    x: bodyRect.width/2 - width/2
                    y: bodyRow.visible ? 100 : 0
                    visible: true //bodyVisible

                    Text {
                        id: body_Text
                        width: bodyRect.width - 10
                        text: qsTr("Сервисы/Приложения остановлены: 0 \nВысвобождено RAM: 0 MB Автозапуск: Выключено") //bodyText
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
                    id: button
                    anchors.centerIn: bottomRect
                    text: qsTr("Включить")
                    width: 150
                    onMouseClick: console.log(text)
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
                id: imageSource
                anchors.fill: imgRect
                anchors.centerIn: imgRect
                source: "qrc:/pict/speedtest.png"
                smooth: true
            }
        }
    }
}

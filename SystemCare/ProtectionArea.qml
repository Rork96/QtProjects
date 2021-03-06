import QtQuick 2.0
import QtQuick.Controls 2.2

Item {  // ProtectionArea
    anchors.fill: parent

    property alias areaHeight: face.height
    property alias areaWidht: face.width

    Rectangle {
        anchors.fill: parent
        color: "transparent"

        Grid {
            anchors.centerIn: parent
            rows: 2
            columns: 3
            spacing: 40

            ControlElement {
                id: face
                headerText: qsTr("Идентификация лица")
                stateText: qsTr("")
                bodyText: qsTr("")
                buttonText: qsTr("Включить")
                bodyVisible: false
                height: 200
                width: 420
                source: "qrc:/pict/face.png"

                ToolTip {
                    text: qsTr("Защитите свой ПК от несанкционированного доступа")
                    delay: 1000
                    visible: face.mouseHover
                    font.pixelSize: 14
                }
            }

            ControlElement {
                id: watch
                headerText: qsTr("Анти-слежка в браузере")
                stateText: qsTr("")
                bodyText: qsTr("")
                buttonText: qsTr("Включить")
                bodyVisible: false
                height: face.height
                width: face.width
                source: "qrc:/pict/shield.png"

                ToolTip {
                    text: qsTr("Автоматическое стирание истории в браузере после его закрытия")
                    delay: 1000
                    visible: watch.mouseHover
                    font.pixelSize: 14
                }
            }

            ControlElement {
                id: protector
                headerText: qsTr("Защитник в реальном времени")
                stateText: qsTr("")
                bodyText: qsTr("")
                buttonText: qsTr("Включить")
                bodyVisible: false
                height: face.height
                width: face.width
                source: "qrc:/pict/clock.png"

                ToolTip {
                    text: qsTr("Активная и легкая защита от шпинских программ")
                    delay: 1000
                    visible: protector.mouseHover
                    font.pixelSize: 14
                }
            }

            ControlElement {
                id: advt
                headerText: qsTr("Защита серфинга и удаление рекламы")
                stateText: qsTr("")
                bodyText: qsTr("")
                buttonText: qsTr("Включить")
                bodyVisible: false
                height: face.height
                width: face.width
                source: "qrc:/pict/browser.png"

                ToolTip {
                    text: qsTr("Защита браузера от сетевых атак")
                    delay: 1000
                    visible: advt.mouseHover
                    font.pixelSize: 14
                }
            }

            ControlElement {
                id: advisor
                headerText: qsTr("Советник дом. страницы")
                stateText: qsTr("")
                bodyText: qsTr("")
                buttonText: qsTr("Включить")
                bodyVisible: false
                height: face.height
                width: face.width
                source: "qrc:/pict/home.png"

                ToolTip {
                    text: qsTr("Мониторинг изменения домашней страницы и поиска в браузере")
                    delay: 1000
                    visible: advisor.mouseHover
                    font.pixelSize: 14
                }
            }

            ControlElement {
                id: dns
                headerText: qsTr("Защита DNS")
                stateText: qsTr("")
                bodyText: qsTr("")
                buttonText: qsTr("Включить")
                bodyVisible: false
                height: face.height
                width: face.width
                source: "qrc:/pict/laptop.png"

                ToolTip {
                    text: qsTr("Предотвращение от изменения DNS вредоносными программами")
                    delay: 1000
                    visible: dns.mouseHover
                    font.pixelSize: 14
                }
            }
        }
    }
}

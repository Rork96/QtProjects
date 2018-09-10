import QtQuick 2.10
import QtQuick.Window 2.10

Window { // MenuWindow
    id: wnd
    width: 200
    height: 100
    flags: Qt.SubWindow | Qt.FramelessWindowHint
    color: Qt.darker("darkblue", 3)

    onActiveFocusItemChanged: if (!activeFocusItem) wnd.close() //wnd.visible = false

    Rectangle {
        x: 0
        y: 60
        width: wnd.width
        height: wnd.height - y
        color: "transparent"

        Column {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            spacing: 24

            SimpleItem {
                id: parameters
                x: 10
                width: parent.width - x
                text: qsTr("Быстрые параметры")
                source: "qrc:/pict/quick_settings.png"
            }

            SimpleItem {
                id: settings
                x: parameters.x
                width: parent.width - x
                text: qsTr("Настройки...")
                source: "qrc:/pict/settings.png"
            }

            SimpleItem {
                id: news
                x: parameters.x
                width: parent.width - x
                text: qsTr("Что нового?")
                source: "qrc:/pict/question.png"
            }

            Rectangle {
                x: parameters.x
                width: parent.width - x*2
                height: 2
                color: Qt.darker("blue", 2)
            }

            SimpleItem {
                id: help
                x: parameters.x
                width: parent.width - x
                text: qsTr("Техподдержка")
                source: "qrc:/pict/center_help.png"
            }

            SimpleItem {
                id: centerHelp
                x: parameters.x
                width: parent.width - x
                text: qsTr("Центр спасения")
                source: "qrc:/pict/help.png"
            }

            SimpleItem {
                id: review
                x: parameters.x
                width: parent.width - x
                text: qsTr("Отправить отзыв")
                source: "qrc:/pict/email.png"

            }

            SimpleItem {
                id: update
                x: parameters.x
                width: parent.width - x
                text: qsTr("Проверка обновлений")
                source: "qrc:/pict/update.png"
            }

            SimpleItem {
                id: guide
                x: parameters.x
                width: parent.width - x
                text: qsTr("Руководство пользователя")
                source: "qrc:/pict/systemhelp.png"
            }
        }

        Column {
            id: footer
            anchors.left: parent.left
            anchors.right: parent.right
            y: parent.height - height - 20
            spacing: 24

            SimpleItem {
                id: qtInfo
                x: parameters.x
                width: parent.width - x
                text: qsTr("О Qt")
                source: "qrc:/pict/qt.png"
            }

            SimpleItem {
                id: info
                x: parameters.x
                width: parent.width - x
                text: qsTr("О программе")
                source: "qrc:/pict/info.png"
            }
        }
    }
}

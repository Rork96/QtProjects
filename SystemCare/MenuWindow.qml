import QtQuick 2.10
import QtQuick.Window 2.10

Window { // MenuWindow
    id: wnd
    width: wndWidth
    height: wndHeight
    flags: Qt.SubWindow | Qt.FramelessWindowHint
    color: Qt.darker("darkblue", 3)

    property int wndWidth: 200
    property int wndHeight: 100

    onActiveFocusItemChanged: if (!activeFocusItem) wnd.visible = false

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
                itemText: "Быстрые параметры"
                itemImage: "qrc:/pict/quick_settings.png"
            }

            SimpleItem {
                id: settings
                x: parameters.x
                width: parent.width - x
                itemText: "Настройки..."
                itemImage: "qrc:/pict/settings.png"
            }

            SimpleItem {
                id: news
                x: parameters.x
                width: parent.width - x
                itemText: "Что нового?"
                itemImage: "qrc:/pict/question.png"
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
                itemText: "Техподдержка"
                itemImage: "qrc:/pict/center_help.png"
            }

            SimpleItem {
                id: centerHelp
                x: parameters.x
                width: parent.width - x
                itemText: "Центр спасения"
                itemImage: "qrc:/pict/help.png"
            }

            SimpleItem {
                id: review
                x: parameters.x
                width: parent.width - x
                itemText: "Отправить отзыв"
                itemImage: "qrc:/pict/email.png"

            }

            SimpleItem {
                id: update
                x: parameters.x
                width: parent.width - x
                itemText: "Проверка обновлений"
                itemImage: "qrc:/pict/update.png"
            }

            SimpleItem {
                id: guide
                x: parameters.x
                width: parent.width - x
                itemText: "Руководство пользователя"
                itemImage: "qrc:/pict/systemhelp.png"
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
                itemText: "О Qt"
                itemImage: "qrc:/pict/qt.png"
            }

            SimpleItem {
                id: info
                x: parameters.x
                width: parent.width - x
                itemText: "О программе"
                itemImage: "qrc:/pict/info.png"
            }
        }
    }
}

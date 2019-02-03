import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Dialogs 1.2

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
                onMouseClicked: console.log(text)
            }

            SimpleItem {
                id: settings
                x: parameters.x
                width: parent.width - x
                text: qsTr("Настройки...")
                source: "qrc:/pict/settings.png"
                onMouseClicked: console.log(text)
            }

            SimpleItem {
                id: news
                x: parameters.x
                width: parent.width - x
                text: qsTr("Что нового?")
                source: "qrc:/pict/question.png"
                onMouseClicked: console.log(text)
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
                onMouseClicked: console.log(text)
            }

            SimpleItem {
                id: centerHelp
                x: parameters.x
                width: parent.width - x
                text: qsTr("Центр спасения")
                source: "qrc:/pict/help.png"
                onMouseClicked: console.log(text)
            }

            SimpleItem {
                id: review
                x: parameters.x
                width: parent.width - x
                text: qsTr("Отправить отзыв")
                source: "qrc:/pict/email.png"
                onMouseClicked: console.log(text)
            }

            SimpleItem {
                id: update
                x: parameters.x
                width: parent.width - x
                text: qsTr("Проверка обновлений")
                source: "qrc:/pict/update.png"
                onMouseClicked: console.log(text)
            }

            SimpleItem {
                id: guide
                x: parameters.x
                width: parent.width - x
                text: qsTr("Руководство пользователя")
                source: "qrc:/pict/systemhelp.png"
                onMouseClicked: console.log(text)
            }
        }

        Column {
            id: footer
            anchors.left: parent.left
            anchors.right: parent.right
            y: parent.height - height - 20
            spacing: 24

            SimpleItem {
                id: info
                x: parameters.x
                width: parent.width - x
                text: qsTr("О программе")
                source: "qrc:/pict/info.png"
                onMouseClicked: aboutDlg.open()
            }

            MessageDialog {
                id: aboutDlg
                modality: Qt.ApplicationModal
                title: qsTr("О программе")
                text: "System Care v 1.0.0"
                informativeText: "Автор: masterarrow\nmasterarrows@gmail.com\n\n    Copyright © 2018\n"
                icon: StandardIcon.Information
                standardButtons: StandardButton.Ok
            }
        }
    }
}

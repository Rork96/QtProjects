import QtQuick 2.10
import QtQuick.Window 2.10

Window {
    id: root
    visible: true
    width: Screen.width-500
    height: Screen.height-300
    title: qsTr("Test")

    Image {
        source: "qrc:/pict/background.jpg"
        anchors.fill: parent
    }

    Row {
        x: 0
        y: 50
        width: root.width
        spacing: 2

        MenuButton {
            id: optimizeBtn
            itemText: qsTr("Меню 1")
            itemWidth: parent.width/5 - parent.spacing
        }

        MenuButton {
            id: quickBtn
            itemText: qsTr("Меню 2")
            itemWidth: parent.width/5 - parent.spacing
        }

        MenuButton {
            id: protectionBtn
            itemText: qsTr("Меню 3")
            itemWidth: parent.width/5 - parent.spacing
        }

        MenuButton {
            id: toollBtn
            itemText: qsTr("Меню 4")
            itemWidth: parent.width/5 - parent.spacing
        }

        MenuButton {
            id: actionsBtn
            itemText: qsTr("Меню 5")
            itemWidth: parent.width/5 - parent.spacing
        }
    }
}

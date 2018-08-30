import QtQuick 2.10
import QtQuick.Window 2.10

Window {
    id: root
    visible: true
    width: Screen.width-500
    height: Screen.height-300
    minimumWidth: 1250
    minimumHeight: 750
    title: qsTr("System Care")

    Image {
        // Background image
        source: "qrc:/pict/background.jpg"
        anchors.fill: parent
    }

    Row {
        // MenuButtons
        id: header
        x: 0
        y: 50
        width: root.width
        spacing: 2

        MenuButton {
            id: optimizeBtn
            itemText: qsTr("Очистка и оптимизация")
            itemWidth: parent.width/5 - parent.spacing
            onMouseClick: clientLoader.setSource(Qt.resolvedUrl("qrc:/MainArea.qml")) // Show MainArea
        }

        MenuButton {
            id: quickBtn
            itemText: qsTr("Ускорение")
            itemWidth: parent.width/5 - parent.spacing
        }

        MenuButton {
            id: protectionBtn
            itemText: qsTr("Защита")
            itemWidth: parent.width/5 - parent.spacing
        }

        MenuButton {
            id: toollBtn
            itemText: qsTr("Инструменты")
            itemWidth: parent.width/5 - parent.spacing
        }

        MenuButton {
            id: actionsBtn
            itemText: qsTr("Центр действия")
            itemWidth: parent.width/5 - parent.spacing
        }
    }

    Loader {    // Clien area
        id: clientLoader
        anchors.left: header.left
        anchors.top: header.bottom
        width: root.width
        height: footer.y - y
        source: Qt.resolvedUrl("qrc:/MainArea.qml")
    }

    Rectangle { // Footer
        id: footer
        anchors.left: header.left
        y: root.height - height
        width: root.width
        height: 100
        color: "transparent"
        border.color: "black"
        border.width: 1.5

        MenuButton {
            id: activateBtn
            x: root.width - itemWidth - 20
            y: parent.height/2 - itemHeight/2
            itemText: qsTr("Выход")
            itemWidth: 150
            onMouseClick: Qt.quit() // Exit on click
        }
    }
}

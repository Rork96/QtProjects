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
    flags: Qt.FramelessWindowHint

    // Mouse position
    property int previousX
    property int previousY

    Image { // Background image
        source: "qrc:/pict/background.jpg"
        anchors.fill: parent
    }

    MouseArea { // TopArea
        id: topArea

        height: 3

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        // Change cursor
        cursorShape: Qt.SizeVerCursor

        onPressed: {
            // Save Y
            previousY = mouseY
        }

        // Calck window position and size
        onMouseYChanged: {
            var dy = mouseY - previousY
            root.setY(root.y + dy)
            root.setHeight(root.height - dy)
        }
    }

    MouseArea { // BottomArea
        id: bottomArea
        height: 3

        anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        cursorShape: Qt.SizeVerCursor

        onPressed: {
            previousY = mouseY
        }

        onMouseYChanged: {
            var dy = mouseY - previousY
            root.setHeight(root.height + dy)
        }
    }

    MouseArea { // LeftArea
        width: 3

        anchors {
            top: topArea.bottom
            bottom: bottomArea.top
            left: parent.left
        }

        cursorShape: Qt.SizeHorCursor

        onPressed: {
            previousX = mouseX
        }

        onMouseXChanged: {
            var dx = mouseX - previousX
            root.setX(root.x + dx)
            root.setWidth(root.width - dx)
        }
    }

    MouseArea { // RightArea
        width: 3

        anchors {
            top: topArea.bottom
            bottom: bottomArea.top
            right: parent.right
        }

        cursorShape:  Qt.SizeHorCursor

        onPressed: {
            previousX = mouseX
        }

        onMouseXChanged: {
            var dx = mouseX - previousX
            root.setWidth(root.width + dx)
        }
    }

    Rectangle { // Header
        id: header
        x: 3
        y: 3
        width: root.width-6
        height: 36
        color: "transparent"

        MouseArea {
            anchors.fill: parent

            onPressed: {
                previousX = mouseX
                previousY = mouseY
            }

            onMouseXChanged: {
                var dx = mouseX - previousX
                root.setX(root.x + dx)
            }

            onMouseYChanged: {
                var dy = mouseY - previousY
                root.setY(root.y + dy)
            }
        }

        MainMenu {
            itemX: 1
            itemY: 1
            imageSource: "qrc:/pict/menu.png"
            onMouseClick: console.log("Menu")
        }

        Rectangle { // Header buttons
            x: parent.width - width
            y: 1
            width: 100
            height: parent.height
            color: "transparent"

            MainMenu { // Close
                itemX: parent.width - itemWidth - 10
                itemY: parent.height/2 - itemHeight/2
                itemHeight: 16
                itemWidth: 16
                imageSource: "qrc:/pict/close.png"
                onMouseClick: Qt.quit()
            }

            MainMenu {  // Maximaze
                itemX: minimizeBtn.width + 20
                itemY: parent.height/2 - itemHeight/2
                itemHeight: 16
                itemWidth: 16
                imageSource: "qrc:/pict/maximize.png"
                onMouseClick: {
                    if (root.visibility === root.Maximized) root.showNormal()
                    else root.showMaximized()
                    clientLoader.update()
                }
            }

            MainMenu { // Minimize
                id: minimizeBtn
                itemX: 0
                itemY: parent.height/2 - itemHeight/2
                itemHeight: 16
                itemWidth: 16
                imageSource: "qrc:/pict/minimize.png"
                onMouseClick: root.showMinimized()
            }
        }
    }

    Row { // Menu
        id: menu
        x: 3
        y: 50
        spacing: 2
        anchors.left: header.left
        anchors.top: header.bottom
        width: header.width
        height: 40

        MenuButton {
            id: optimizeBtn
            itemText: qsTr("Очистка и оптимизация")
            itemWidth: parent.width/5 - parent.spacing/2
            onMouseClick: {
                checked = true
                quickBtn.checked = !checked
                protectionBtn.checked = !checked
                toollBtn.checked = !checked
                actionsBtn.checked = !checked
                clientLoader.setSource(Qt.resolvedUrl("qrc:/MainArea.qml")) // Show MainArea
            }
            checked: true
        }

        MenuButton {
            id: quickBtn
            itemText: qsTr("Ускорение")
            itemWidth: parent.width/5 - parent.spacing/2
            onMouseClick: {
                checked = true
                optimizeBtn.checked = !checked
                protectionBtn.checked = !checked
                toollBtn.checked = !checked
                actionsBtn.checked = !checked
//                clientLoader.setSource(Qt.resolvedUrl("qrc:/QuickArea.qml"))
            }
        }

        MenuButton {
            id: protectionBtn
            itemText: qsTr("Защита")
            itemWidth: parent.width/5 - parent.spacing/2
            onMouseClick:{
                checked = true
                quickBtn.checked = !checked
                optimizeBtn.checked = !checked
                toollBtn.checked = !checked
                actionsBtn.checked = !checked
//                clientLoader.setSource(Qt.resolvedUrl("qrc:/ProtectionArea.qml"))
            }
        }

        MenuButton {
            id: toollBtn
            itemText: qsTr("Инструменты")
            itemWidth: parent.width/5 - parent.spacing/2
            onMouseClick: {
                checked = true
                quickBtn.checked = !checked
                protectionBtn.checked = !checked
                optimizeBtn.checked = !checked
                actionsBtn.checked = !checked
//                clientLoader.setSource(Qt.resolvedUrl("qrc:/ToolsArea.qml"))
            }
        }

        MenuButton {
            id: actionsBtn
            itemText: qsTr("Центр действия")
            itemWidth: parent.width/5 - parent.spacing/2
            onMouseClick: {
                checked = true
                quickBtn.checked = !checked
                protectionBtn.checked = !checked
                toollBtn.checked = !checked
                optimizeBtn.checked = !checked
//                clientLoader.setSource(Qt.resolvedUrl("qrc:/ActionsArea.qml"))
            }
        }
    }

    /* Clien Area */
    Loader {    // Clien area
        id: clientLoader
        anchors.left: header.left
        anchors.top: menu.bottom
        width: header.width
        height: footer.y - y
        source: Qt.resolvedUrl("qrc:/MainArea.qml")
    }

    Rectangle { // Footer
        id: footer
        anchors.left: header.left
        y: root.height - height -3
        width: header.width
        height: 100
        color: "transparent"
        border.color: "black"
        border.width: 1.5

        MenuButton {
            id: activateBtn
            x: root.width - itemWidth - 20
            y: parent.height/2 - itemHeight/2
            itemText: qsTr("Активировать")
            itemWidth: 150
            onMouseClick: console.log(itemText)
        }
    }
}

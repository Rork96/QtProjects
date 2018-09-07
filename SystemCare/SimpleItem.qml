import QtQuick 2.0

Item { // SimpleItem
    id: itm
    width: itemWidth
    height: 28
    opacity: 0.7

    property string itemText: qsTr("Item")
    property string itemImage: "qrc:/pict/home.png"
    signal mouseClicked

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor // Change cursor
        onEntered: itm.state = "Entered"
        onExited: itm.state = "Exited"
        onClicked: {
            // Start animation
            anim.running = true
            // Send signal
            mouseClicked()
        }
    }

    Image {
        id: imgRect
        x: parent.x + 2
        y: parent.height/2 - height/2
        width: 26
        height: width
        anchors.fill: imgRect
        source: itemImage
    }

    Text {
        x: imgRect.x + imgRect.width + 20
        y: imgRect.height/2 - height/2
        text: itemText
        font.pixelSize: 18
        color: "white"
    }

    SequentialAnimation {   // Animation at onClick
        id: anim
        NumberAnimation {
            target: itm
            properties: "opacity"
            from: 0.7
            to: 0.5
            duration: 80
        }

        NumberAnimation {
            target: itm
            properties: "opacity"
            from: 0.5
            to: 0.7
            duration: 80
        }
    }

    states: [   // Change opacity dependent on the mouse behavior (entered or exited rect)
        State {
            name: "Entered"
            PropertyChanges {
                target: itm
                opacity: 1.0
            }
        },
        State {
            name: "Exited"
            PropertyChanges {
                target: itm
                opacity: 0.7
            }
        }
    ]
}

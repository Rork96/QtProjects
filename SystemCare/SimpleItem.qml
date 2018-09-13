import QtQuick 2.0

Item { // SimpleItem
    id: itm
    width: 100
    height: 28
    opacity: 0.7

    property alias text: itemText.text
    property alias source: imgRect.source
    property alias imageWidth: imgRect.width
    property alias fontSize: itemText.font.pixelSize
    property real itemOpacity: 0.7
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
        x: itm.x + 2
        y: itm.height/2 - height/2
        width: 26
        height: width
        anchors.fill: imgRect
        source: "qrc:/pict/home.png"
    }

    Text {
        id: itemText
        x: imgRect.x + imgRect.width + 20
        y: imgRect.height/2 - height/2
        text: qsTr("Item")
        font.pixelSize: 18
        color: "white"
    }

    SequentialAnimation {   // Animation at onClick
        id: anim
        NumberAnimation {
            target: itm
            properties: "opacity"
            from: itemOpacity
            to: 0.5
            duration: 80
        }

        NumberAnimation {
            target: itm
            properties: "opacity"
            from: 0.5
            to: itemOpacity
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
                opacity: itemOpacity
            }
        }
    ]
}

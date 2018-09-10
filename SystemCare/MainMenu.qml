import QtQuick 2.0

Item {  // MainMenu
    id: mMenu
    x: 0
    y: 0
    height: 30
    width: height

    property alias source: img.source
    signal mouseClick   // Signal for MouseArea onClicked

    Rectangle {
        id: rect
        anchors.fill: parent
        color: "transparent"

        Image {
            id: img
            anchors.fill: parent
            source: ""
            sourceSize.width: mMenu.height
            sourceSize.height: mMenu.height
        }

        states: [   // Change opacity dependent on the mouse behavior (entered or exited rect)
            State {
                name: "Entered"
                PropertyChanges {
                    target: rect
                    opacity: 0.8
                }
            },
            State {
                name: "Exited"
                PropertyChanges {
                    target: rect
                    opacity: 1.0
                }
            }
        ]

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: rect.state = "Entered"
            onExited: rect.state = "Exited"
            onClicked: mouseClick()
        }
    }
}

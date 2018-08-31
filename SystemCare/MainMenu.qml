import QtQuick 2.0

Item {  // Menu
    property string imageSource: ""
    property int itemX: 0
    property int itemY: 0
    property int itemHeight: 30
    property int itemWidth: 30

    signal mouseClick   // Signal for MouseArea onClicked

    x: itemX
    y: itemY
    height: itemHeight
    width: itemWidth

    Rectangle {
        id: rect
        anchors.fill: parent
        color: "transparent"

        Image {
            anchors.fill: parent
            source: imageSource
            sourceSize.width: itemHeight
            sourceSize.height: itemHeight
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

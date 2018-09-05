import QtQuick 2.10

Item {  // SimpleButton
    property string itemText: "Text"
    property int fontSize: 18
    property int itemHeight: 40
    property int itemWidth: 100
    property string itemColor: "#0b1160"
    property string borderColor: "#1313af"

    signal mouseClick   // Signal for MouseArea onClicked

    height: itemHeight
    width: itemWidth

    Rectangle {
        id: rect
        anchors.fill: parent
        color: itemColor
        gradient: Gradient {
            GradientStop {
                position: 0.47
                color: itemColor
            }
            GradientStop {
                position: 1.00
                color: "#ffffff"
            }
        }
        border.color: borderColor
        border.width: 1
        opacity: 0.7

        Text {
            anchors.centerIn: rect
            text: itemText
            font.pixelSize: fontSize
            color: "white"
        }

        SequentialAnimation {   // Animation at onClick
            id: anim
            NumberAnimation {
                target: rect
                properties: "opacity"
                from: 0.7
                to: 0.5
                duration: 80
            }

            NumberAnimation {
                target: rect
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
                    target: rect
                    opacity: 1.0
                }
            },
            State {
                name: "Exited"
                PropertyChanges {
                    target: rect
                    opacity: 0.7
                }
            }
        ]

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor // Change cursor
            onEntered: rect.state = "Entered"
            onExited: rect.state = "Exited"
            onClicked: {
                // Start animation
                anim.running = true
                // Send signal
                mouseClick()
            }
        }
    }
}

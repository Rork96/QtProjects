import QtQuick 2.10

Item {  // MenuButton
    height: 40
    width: 100

    property alias text: itemText.text
    property alias fontSize: itemText.font.pixelSize
    property real startOpacity: 0.6
    property real defaultOpacity: 1.0
    property bool checked: false
    signal mouseClick   // Signal for MouseArea onClicked

    Rectangle {
        id: rect
        anchors.fill: parent
        color: "#0b1160"
        gradient: Gradient {
            GradientStop {
                position: 0.47
                color: "#0b1160"
            }
            GradientStop {
                position: 1.00
                color: "#ffffff"
            }
        }
        border.color: "#1313af"
        border.width: 1
        opacity: checked ? defaultOpacity : startOpacity

        Text {
            id: itemText
            anchors.centerIn: rect
            text: qsTr("Text")
            font.pixelSize: 18
            color: "white"
        }

        SequentialAnimation {   // Animation at onClick
            id: anim
            NumberAnimation {
                target: rect
                properties: "opacity"
                from: startOpacity
                to: 0.4
                duration: 80
            }

            NumberAnimation {
                target: rect
                properties: "opacity"
                from: 0.4
                to: 0.8
                duration: 80
            }
        }

        states: [   // Change opacity dependent on the mouse behavior (entered or exited rect)
            State {
                name: "Entered"
                PropertyChanges {
                    target: rect
                    opacity: checked ? defaultOpacity : 0.8
                }
            },
            State {
                name: "Exited"
                PropertyChanges {
                    target: rect
                    opacity: checked ? defaultOpacity : startOpacity
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
                // Change state
                checked = true
                // Change opacity
                if (checked) opacity = defaultOpacity
                else opacity = startOpacity
            }
        }
    }
}

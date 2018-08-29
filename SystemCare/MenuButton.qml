import QtQuick 2.10

Item {
    property string itemText: "Text"
    property int fontSize: 18
    property int itemHeight: 40
    property int itemWidth: 100

    height: itemHeight
    width: itemWidth

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

        Text {
            anchors.centerIn: rect
            text: itemText
            font.pixelSize: fontSize
            color: "white"
        }

        SequentialAnimation {
            id: anim
            NumberAnimation {
                target: rect
                properties: "opacity"
                from: 1.0
                to: 0.5
                duration: 80
            }

            NumberAnimation {
                target: rect
                properties: "opacity"
                from: 0.5
                to: 1.0
                duration: 80
            }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                anim.running = true
                console.log(itemText)
            }
        }
    }
}

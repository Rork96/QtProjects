import QtQuick 2.10
import QtQuick.Controls 2.4

Button {    // CustomButton
    id: btn
    width: 142
    height: 40
    highlighted: false
    background: Rectangle {
        gradient: Gradient {
            GradientStop { position: 0; color: "lightGray" }
            GradientStop { position: 0.4; color: "darkGray" }
            GradientStop { position: 0.6; color: "darkGray" }
            GradientStop { position: 1; color: "lightGray" }
        }
    }
    // For desktop
    contentItem: Label {
        anchors.fill: parent
        text: btn.text
        font.family: "Verdana"
        font.pixelSize: 12
        renderType: Text.NativeRendering
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
    // -------
    text: "Button"
    onHoveredChanged: hovered ? opacity = 0.9 : opacity = 1.0
    onClicked: anim.start()

    SequentialAnimation {
        id: anim
        NumberAnimation {
            target: btn
            property: "opacity"
            duration: 50
            from: 1.0
            to: 0.7
        }
        NumberAnimation {
            target: btn
            property: "opacity"
            duration: 50
            from: 0.7
            to: 1.0
        }
    }
}

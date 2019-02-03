import QtQuick 2.0

Text {
    id: mainText
    text: "Детали"
    font.underline: true
    font.pixelSize: 14
    color: "white"
    opacity: 0.5

    signal mouseClick

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor // Change cursor
        onEntered: mainText.opacity = 1.0
        onExited: mainText.opacity = 0.5
        onClicked: mouseClick()
    }
}

import QtQuick 2.0
import QtQuick.Controls 2.3

Item {
    id: item
    width: parent.width
    height: 80

    property alias fontSize: slider.value
    property alias text: headerText.text

    Rectangle {
        anchors.fill: parent
        color: "transparent"

        Column {
            Text { id: headerText; color: "lightGray"; text: ""; font.pointSize: 16 }

            Text {
                color: "lightGray"; text: "Current font size: " + slider.value
                font.italic: true; font.pointSize: 12 }

            Slider {
                id: slider
                width: item.width - 20
                height: 24
                orientation: Qt.Horizontal
                stepSize: 2
                to: 24
                from: 6
                value: 6
            }
        }
    }
}

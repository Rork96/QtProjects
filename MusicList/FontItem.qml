import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {  // FontItem
    id: it
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
                width: it.width - 10
                height: 24
                orientation: Qt.Horizontal
                stepSize: 2
                minimumValue: 6
                maximumValue: 24
                value: minimumValue

                style: SliderStyle {
                    groove: Rectangle { // The background of the slider
                        height: 4
                        antialiasing: true
                        radius: height/2
                        color: "gray"

                        Rectangle { // Filled slider part
                            width: styleData.handlePosition
                            height: parent.height
                            color: "lightGray"
                            radius: parent.radius
                        }
                    }

                    handle: Rectangle { // Handle
                        implicitHeight: 12
                        implicitWidth: implicitHeight
                        radius: implicitHeight/2
                        color: "lightGray"
                    }

                }
            }
        }
    }
}

import QtQuick 2.0
import QtQuick.Controls 1.4

Item { // ActionsArea
    anchors.fill: parent

    Flickable {
        anchors.fill: parent
        contentWidth: 600
        contentHeight: 600

        Rectangle {
            id: mainRect
            x: 0
            y: 50
            height: parent.height - y
            width: parent.width
            color: "blue"
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "transparent"
                }
                GradientStop {
                    position: 0.2
                    color: Qt.darker("blue", 4.0)
                }
                GradientStop {
                    position: 0.8
                    color: Qt.darker("blue", 4.0)
                }
                GradientStop {
                    position: 1.00
                    color: "transparent"
                }
            }
        }

        Rectangle {
            id: rect
            x: 0
            y: mainRect.x + mainRect.height + 50
            height: 300
            width: parent.width
            color: "blue"
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "transparent"
                }
                GradientStop {
                    position: 0.2
                    color: Qt.darker("blue", 4.0)
                }
                GradientStop {
                    position: 0.8
                    color: Qt.darker("blue", 4.0)
                }
                GradientStop {
                    position: 1.00
                    color: "transparent"
                }
            }
        }
    }
}

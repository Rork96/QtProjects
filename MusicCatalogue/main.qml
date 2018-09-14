import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.XmlListModel 2.0

ApplicationWindow {
    visible: true
    width: 200
    height: 360
    title: qsTr("Music Catalogue")

    Rectangle {
         id: mainRect
         color: "grey"
         width: parent.width
         height: parent.height

         Component {
             id: delegate

             Item {
                 width: mainRect.width
                 height: 70

                 Row {
                     anchors.verticalCenter: parent.verticalCenter

                     Image {
                         width: 64
                         height: 64
                         source: cover
                         smooth: true
                     }

                     Column {
                         Text { color: "white"; text: " " + artist; font.pointSize: 14 }
                         Text { color: "lightblue"; text: " " + album; font.pointSize: 12 }
                         Text { color: "yellow"; text: " " + year; font.pointSize: 10 }
                     }
                 }
             }
         }

        ListView {
            anchors.fill: parent
            focus: true
            header: Rectangle {
                width: parent.width
                height: 30
                gradient: Gradient {
                    GradientStop { position: 0; color: "grey" }
                    GradientStop { position: 0.7; color: "black" }
                }

                Text {
                    anchors.centerIn: parent
                    color: "grey"
                    text: "Muisc"
                    font.bold: true
                    font.pointSize: 20
                }
            }
            footer: Rectangle {
                width: parent.width
                height: 30
                gradient: Gradient {
                    GradientStop { position: 0; color: "grey" }
                    GradientStop { position: 0.7; color: "black" }
                }
            }
            highlight: Rectangle {
                width: parent.width
                color: "blue"
            }
            model: Music { }
            delegate: delegate
        }
    }
}

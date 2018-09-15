import QtQuick 2.9
import QtQuick.Window 2.0
import QtQuick.Controls 2.2

ApplicationWindow {
    id: root
    visible: true
    width: 300 // Screen.width
    height: 450 //Screen.height
    title: qsTr("Music Catalogue")

    Rectangle {
         id: mainRect
         color: "grey"
         width: parent.width
         height: parent.height

         Component {
             id: delegate

             Item {
                 id: it
                 width: mainRect.width
                 height: 70

                 Row {
                     anchors.verticalCenter: parent.verticalCenter

                     Image {
                         id: imgCover
                         width: 64
                         height: 64
                         source: "file://" + cover
                         smooth: true
                     }

                     Column {
                         Text { color: "white"; text: " " + artist; font.pointSize: 14 }
                         Text { color: "lightblue"; text: " " + album; font.pointSize: 12 }
                         Text { color: "yellow"; text: " " + year; font.pointSize: 10 }
                     }
                 }

                 MouseArea {
                     anchors.fill: parent
                     onDoubleClicked: {
                         imgViewer.title = artist + " - " + album
                         imgViewer.source = imgCover.source
                         imgViewer.show()
                     }
                 }
             }
         }

         Viewer {
             id: imgViewer
         }

        ListView {
            anchors.fill: parent
            focus: true
            ScrollBar.vertical: ScrollBar {}
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
                    text: "Music"
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

import QtQuick 2.9
import QtQuick.Window 2.0
import QtQuick.Controls 2.2

ApplicationWindow {
    id: root
    visible: true
    width: Screen.width
    height: Screen.height
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
                height: 100

                Row {
                    anchors.verticalCenter: parent.verticalCenter

                    Image {
                        id: imgCover
                        width: 96
                        height: 96
                        // source: "file://" + cover  // Linux
                        source: cover  // Android
                        smooth: true
                    }

                    Column {
                        Text { color: "white"; text: " " + artist; font.pointSize: 20 }
                        Text { color: "lightblue"; text: " " + album; font.pointSize: 18 }
                        Text { color: "yellow"; text: " " + year; font.pointSize: 16 }
                    }
                }
            }
        }

        ListView {
            anchors.fill: parent
            focus: true
            ScrollBar.vertical: ScrollBar {}
            header: Rectangle {
                width: parent.width
                height: 40
                gradient: Gradient {
                    GradientStop { position: 0; color: "grey" }
                    GradientStop { position: 0.7; color: "black" }
                }

                Text {
                    anchors.centerIn: parent
                    color: "grey"
                    text: "Music"
                    font.bold: true
                    font.pointSize: 24
                }
            }
            footer: Rectangle {
                width: parent.width
                height: 40
                gradient: Gradient {
                    GradientStop { position: 0; color: "grey" }
                    GradientStop { position: 0.7; color: "black" }
                }

                Text {
                    anchors.centerIn: parent
                    color: "grey"
                    text: "mastrarrows@gmail.com"
                    font.bold: true
                    font.pointSize: 14
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

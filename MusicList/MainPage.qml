import QtQuick 2.10
import QtQuick.Window 2.0
import QtQuick.Controls 2.3

Page {
    id: mainPage

    property int artistFont: 20
    property int albumFont: 18
    property int yearFont: 16
    property bool imageVisible: true

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

                Rectangle {
                    anchors.fill: parent
                    border.color: "grey"
                    border.width: 1
                    gradient: Gradient {
                        GradientStop { position: 0; color: "grey" }
                        GradientStop { position: 0.3; color: Qt.darker("grey") }
                        GradientStop { position: 0.7; color: Qt.darker("grey") }
                        GradientStop { position: 1; color: "grey" }
                    }

                    Row {
                        anchors.verticalCenter: parent.verticalCenter

                        Image {
                            id: imgCover
                            width: 96
                            height: 96
                            source: cover
                            smooth: true
                            visible: imageVisible
                        }

                        Column {
                            Text { color: "white"; text: " " + artist; font.pointSize: artistFont }
                            Text { color: "lightblue"; text: " " + album; font.pointSize: albumFont }
                            Text { color: "yellow"; text: " " + year; font.pointSize: yearFont }
                        }
                    }
                }
            }
        }

        ListView {
            id: view
            anchors.fill: parent
            focus: true
            ScrollBar.vertical: ScrollBar { }
            model: Music { }
            delegate: delegate
            clip: true
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
}

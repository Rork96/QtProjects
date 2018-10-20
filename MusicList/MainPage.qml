import QtQuick 2.9
import QtQuick.Window 2.0
import QtQuick.Controls 2.2

Page {  // MainPage
    id: mainPage

    property int artistFont: 20
    property int albumFont: 18
    property int yearFont: 16
    property bool imageVisible: true
    signal changePage

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

        Image { // Go to the MenuPage
            anchors.verticalCenter: parent.verticalCenter
            x: parent.width - width - 5
            width: 28
            height: width
            source: "qrc:/pict/settings.png"

            MouseArea {
                anchors.fill: parent
                onClicked: changePage()
            }
        }
    }

    Rectangle {
        id: mainRect
        color: "grey"
        width: parent.width
        height: parent.height

        Component { // Delegate for ListView
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

                    Image {
                        id: imgCover
                        anchors.left: parent.left
                        anchors.top: parent.top
                        anchors.leftMargin: 0
                        anchors.topMargin: 0
                        width: 96
                        height: 96
                        source: cover
                        smooth: true
                        visible: imageVisible

                        MouseArea {
                            anchors.fill: parent
                            onClicked: if (imgCover.parent.state === "") {
                                           imgCover.parent.state = "expanded"    // Switch to expanded ListView
                                       }
                                       else {
                                           imgCover.parent.state = ""            // Switch back to not expanded ListView
                                       }
                        }
                    }

                    Rectangle {
                        id: infoRect
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                        width: txt.width
                        opacity: 0

                        Column {
                            anchors.fill: parent
                            Text { id: txt; color: "white"; text: "Artist: "; font.pointSize: artistFont }
                            Text { color: "lightblue"; text: "Album: "; font.pointSize: albumFont }
                            Text { color: "yellow"; text: "Year: "; font.pointSize: yearFont }
                        }
                    }

                    Rectangle {
                        id: rect
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        anchors.left: imgCover.right
                        anchors.leftMargin: 5
                        anchors.right: parent.right

                        Column {
                            anchors.fill: parent
                            Text { color: "white"; text: " " + artist; font.pointSize: artistFont }
                            Text { color: "lightblue"; text: " " + album; font.pointSize: albumFont }
                            Text { color: "yellow"; text: " " + year; font.pointSize: yearFont }
                        }
                    }

                    states: [
                        State {
                            name: "expanded"
                            PropertyChanges { target: it; height: view.height }
                            PropertyChanges { target: infoRect; opacity: 1 }
                            PropertyChanges { target: imgCover; width: view.width; height: view.width; anchors.topMargin: 120 }
                            PropertyChanges { target: rect; anchors.left: infoRect.right }
                            PropertyChanges { target: it.ListView.view; contentY: it.y; interactive: false }  // Listing between an elements is restricted
                        }
                    ]

                    transitions: [
                        Transition {
                            NumberAnimation {
                                duration: 200;
                                properties: "height,opacity,width,anchors.topMargin,anchors.left"
                            }
                        }
                    ]
                }
            }
        }

        ListView {
            id: view
            anchors.fill: parent
            focus: true
            //ScrollBar.vertical: ScrollBar { }
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

import QtQuick 2.9
import QtQuick.Controls 2.2

Item {  // MenuItems
    width: parent.width
    height: parent.height

    property alias artistFont: art.fontSize
    property alias albumFont: alb.fontSize
    property alias yearFont: yea.fontSize
    property alias imgVisible: box.checked

    Rectangle {
        id: mainRect
        anchors.fill: parent
        color: "grey"
        border.width: 1
        gradient: Gradient {
            GradientStop { position: 0; color: "grey" }
            GradientStop { position: 0.3; color: Qt.darker("grey") }
            GradientStop { position: 0.7; color: Qt.darker("grey") }
            GradientStop { position: 1; color: "grey" }
        }

        Column {
            x: 5
            width: mainRect.width - x*2
            spacing: 0

            /* Font settings */

            Text { color: "lightGray"; text: "Font size"; font.bold: true; font.pointSize: 16 }

            ToolSeparator { width: parent.width; height: 14; orientation: Qt.Horizontal } // Separator

            FontItem { id: art; fontSize: 6; text: "Artist" }

            ToolSeparator { width: parent.width; height: 13; orientation: Qt.Horizontal }

            FontItem { id: alb; fontSize: 6; text: "Album" }

            ToolSeparator { width: parent.width; height: 13; orientation: Qt.Horizontal }

            FontItem { id: yea; fontSize: 6; text: "Year" }

            ToolSeparator { width: parent.width; height: 14; orientation: Qt.Horizontal }

            Rectangle { // Show or hide image
                width: mainRect.width - 10
                height: 60
                color: "transparent"

                Row {
                    anchors.verticalCenter: parent.verticalCenter

                    Column {
                        width: mainRect.width - 40

                        Text {
                            color: "lightGray"; text: "Show pictures";
                            font.bold: true; font.pointSize: 16 }

                        Text {
                            color: "lightGray"; text: "Do you want to see a picture of album?";
                            font.italic: true; font.pointSize: 12 }
                    }

                    ControlBox {
                        id: box
                        checked: true
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: box.checked = !box.checked
                }
            }

            ToolSeparator { width: parent.width; height: 14; orientation: Qt.Horizontal }

            Rectangle { // About the app
                width: mainRect.width - 10
                height: 120
                color: "transparent"

                Row {
                    id: r
                    spacing: 10
                    width: 30

                    Image {
                        anchors.verticalCenter: parent.verticalCenter
                        width: 26
                        height: width
                        source: "qrc:/pict/info.png"
                    }

                    Text {
                        anchors.verticalCenter: parent.verticalCenter;
                        color: "lightGray";
                        text: "About the app";
                        font.bold: true
                        font.pointSize: 16
                    }
                }

                Column {    // Information
                    x: 10
                    anchors.top: r.bottom

                    Text { color: "lightGray"; text: "Music List v1.0.0";
                        font.italic: true; font.pointSize: 12 }

                    Text { color: "lightGray"; text: "author: masterarrow";
                        font.italic: true; font.pointSize: 12 }

                    Text { color: "lightGray"; text: "email: masterarrows@gmail.com";
                        font.italic: true; font.pointSize: 12 }

                    Text { color: "lightGray"; text: "Copyright © 2018";
                        font.italic: true; font.pointSize: 12 }
                }
            }
        }
    }
}

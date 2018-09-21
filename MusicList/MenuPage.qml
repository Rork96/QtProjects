import QtQuick 2.9
import QtQuick.Window 2.0
import QtQuick.Controls 2.2

Page {
    id: menuPage

    property alias artistFont: fontItem.artistFont
    property alias albumFont: fontItem.albumFont
    property alias yearFont: fontItem.yearFont
    property alias imageVisible: fontItem.imgVisible
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
            text: "Preferences"
            font.bold: true
            font.pointSize: 24
        }

        Image {
            anchors.verticalCenter: parent.verticalCenter
            x: 5
            width: 24
            height: width
            source: "qrc:/pict/back.png"

            MouseArea {
                anchors.fill: parent
                onClicked: changePage()
            }
        }
    }

    MenuItems {
        id: fontItem
        artistFont: 6
        albumFont: 6
        yearFont: 6
        imgVisible: true
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

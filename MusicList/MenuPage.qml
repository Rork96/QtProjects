import QtQuick 2.10
import QtQuick.Window 2.0
import QtQuick.Controls 2.3

Page {
    id: menuPage

    property alias artistFont: fontItem.artistFont
    property alias albumFont: fontItem.albumFont
    property alias yearFont: fontItem.yearFont
    property alias imageVisible: fontItem.imgVisible

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

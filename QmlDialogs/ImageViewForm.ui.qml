import QtQuick 2.10
import QtQuick.Controls 2.4

Page {
    property alias imgPathText: imgPath.text
    property alias imageSource: image.source
    property alias backBtn: backBtn
    header: Rectangle {
        width: parent.width
        height: 40
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "grey"
            }
            GradientStop {
                position: 0.3
                color: "black"
            }
            GradientStop {
                position: 0.6
                color: "black"
            }
            GradientStop {
                position: 1
                color: "grey"
            }
        }

        Button {
            id: backBtn
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            width: 28
            height: width
            icon.source: "qrc:/pict/up.png"
            icon.color: "lightGray"
            icon.width: backBtn.width - 2
            rotation: 270
            background: Rectangle {
                color: "transparent"
            }
        }

        Text {
            id: imgPath
            anchors.centerIn: parent
            text: qsTr("Image")
            color: "lightGray"
            font.bold: true
            font.pointSize: 10
        }
    }

    footer: Rectangle {
        anchors.bottom: parent.bottom
        width: parent.width
        height: 30
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "grey"
            }
            GradientStop {
                position: 0.4
                color: "black"
            }
        }

        Text {
            id: pathText
            anchors.centerIn: parent
            text: qsTr("")
            font.italic: false
            font.bold: false
            color: "lightGray"
            font.pointSize: 14
        }
    }

    Flickable {
        id: flickable
        anchors.fill: parent
        clip: true
        contentWidth: parent.width
        contentHeight: image.height
        ScrollBar.vertical: ScrollBar {
        }
        ScrollBar.horizontal: ScrollBar {
        }

        Image {
            id: image
            anchors.centerIn: parent
            fillMode: Image.PreserveAspectFit
            source: "qrc:/qtquickplugin/images/template_image.png"
        }
    }
}


/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:18;anchors_height:100;anchors_width:100;anchors_x:214;anchors_y:135}
}
 ##^##*/

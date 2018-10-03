import QtQuick 2.10
import QtQuick.Controls 2.4

Page {
    property alias testText: testText
    property alias messageBtn: messageBtn
    property alias dialogBtn: dialogBtn
    property alias imageBtn: imageBtn
    property alias folderBtn: folderBtn
    property alias fontBtn: fontBtn
    property alias colorBtn: colorBtn
    property alias pathTextText: pathText.text
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

        Text {
            anchors.centerIn: parent
            text: qsTr("Choose a dialog")
            color: "lightGray"
            font.bold: true
            font.pointSize: 18
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

    Column {
        id: column
        spacing: 20
        anchors.fill: parent

        Label {
            id: testText
            text: qsTr("Text for a test")
            font.pointSize: 24
            anchors.top: parent.top
            anchors.topMargin: 80
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Row {
            id: row
            width: parent.width
            height: messageBtn.height
            anchors.top: testText.bottom
            anchors.topMargin: 60
            spacing: 0

            CustomButton {
                id: messageBtn
                text: "Show message"
                anchors.horizontalCenterOffset: -width + 50
                anchors.horizontalCenter: parent.horizontalCenter
            }

            CustomButton {
                id: dialogBtn
                text: "Show dialog"
                anchors.horizontalCenterOffset: width - 50
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
        Row {
            id: row1
            width: parent.width
            height: imageBtn.height
            anchors.topMargin: 30
            anchors.top: row.bottom
            spacing: 10

            CustomButton {
                id: imageBtn
                text: "Open image"
                anchors.horizontalCenterOffset: -width + 50
                anchors.horizontalCenter: parent.horizontalCenter
            }

            CustomButton {
                id: folderBtn
                text: "Open folder"
                anchors.horizontalCenterOffset: width - 50
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        Row {
            id: row2
            width: parent.width
            height: folderBtn.height
            anchors.top: row1.bottom
            anchors.topMargin: 30
            spacing: 10

            CustomButton {
                id: fontBtn
                text: "Select font"
                anchors.horizontalCenterOffset: -width + 50
                anchors.horizontalCenter: parent.horizontalCenter
            }

            CustomButton {
                id: colorBtn
                text: "Select color"
                anchors.horizontalCenterOffset: width - 50
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}


/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:19;anchors_height:400}D{i:20;anchors_height:400}
D{i:18;anchors_height:400}D{i:13;anchors_height:400;anchors_width:200;anchors_x:220;anchors_y:29}
}
 ##^##*/

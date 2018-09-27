import QtQuick 2.10
import QtQuick.Window 2.3
import QtQuick.Controls 2.4
import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2

Page {
    property alias path: pathText.text
    signal openFileDialog
    signal openFolderDialog

    header: Rectangle {
        width: parent.width
        height: 40
        gradient: Gradient {
            GradientStop { position: 0; color: "grey" }
            GradientStop { position: 0.3; color: "black" }
            GradientStop { position: 0.6; color: "black" }
            GradientStop { position: 1; color: "grey" }
        }

        Text {
            anchors.centerIn: parent
            text: qsTr("Choose a dialog")
            color: "lightGray"
            font.bold: true
            font.pointSize: 18
        }
    }

    MessageDialog {
        id: msgDlg
        title: "Information"
        modality: Qt.WindowModal
        standardButtons: StandardButton.Ok
    }

    Dialog {
        id: dlg
        title: "Simple dialog"

        contentItem: Rectangle {
            //color: "lightskyblue"
            implicitWidth: 400
            implicitHeight: 150
            gradient: Gradient {
                GradientStop { position: 0; color: "white" }
                GradientStop { position: 0.3; color: "lightskyblue" }
                GradientStop { position: 0.7; color: "lightskyblue" }
                GradientStop { position: 1; color: "white" }
            }

            Text {
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.topMargin: 30
                anchors.leftMargin: 5
                text: "Text in the simple dialog!"
                color: "navy"
            }

            Button {
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 10
                anchors.rightMargin: 10
                text: "Ok"
                onClicked: dlg.close()
            }
        }
    }

//    FileDialog {
//        id: fileDlg
//        title: "Choose a file"
//        selectMultiple: false
//        folder: shortcuts.home
//        nameFilters: [ "Image files (*.jpg *.png *jpeg)", "All files (*)" ]
//        modality: Qt.WindowModal
//        onAccepted: pathText.text = fileUrl
//    }

//    FolderDialog {
//       id: folderDialog
//       title: "Choose a folder or a couple of folders"
//       folder: shortcuts.home
//       modality: Qt.WindowModal
//       options: FolderDialog.ShowDirsOnly
//       currentFolder: shortcuts.home
//       onAccepted: pathText.text = folder
//    }

    ColorDialog {
        id: colorDlg
        title: "Choose a color"
        modality: Qt.WindowModal
        currentColor: testText.color
        showAlphaChannel: true
    }

    FontDialog {
        id: fontDlg
        title: "Choose a font"
        modality: Qt.WindowModal
        font: Qt.font({ family: "Verdana", pointSize: 24, weight: Font.Normal })
    }

    Label {
        id: testText
        text: qsTr("Text for a test")
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: fontDlg.font.pointSize //20
        font.family: fontDlg.font
        font.weight: fontDlg.font.weight
        font.bold: fontDlg.font.bold
        font.italic: fontDlg.font.italic
        font.underline: fontDlg.font.underline
        color: colorDlg.color
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 65
    }

    CustomButton {
        text: qsTr("Message dialog")
        anchors.left: parent.left
        anchors.leftMargin: 140
        anchors.top: parent.top
        anchors.topMargin: 155
        onClicked: {
            msgDlg.text = "Text in the message dialog"
            msgDlg.detailedText = "Some detailed text"
            msgDlg.informativeText = "Informative text"
            msgDlg.icon = StandardIcon.Information
            msgDlg.open()
        }
    }

    CustomButton {
        text: qsTr("Dialog")
        anchors.right: parent.right
        anchors.rightMargin: 140
        anchors.top: parent.top
        anchors.topMargin: 155
        onClicked: dlg.open()
    }

    CustomButton {
        text: qsTr("File dialog")
        anchors.top: parent.top
        anchors.topMargin: 235
        anchors.left: parent.left
        anchors.leftMargin: 140
        onClicked: openFileDialog() //fileDlg.open()
    }

    CustomButton {
        text: qsTr("Folder dialog")
        anchors.top: parent.top
        anchors.topMargin: 235
        anchors.right: parent.right
        anchors.rightMargin: 140
        onClicked: openFolderDialog() //folderDialog.open()
    }

    CustomButton {
        text: qsTr("Font dialog")
        anchors.left: parent.left
        anchors.leftMargin: 140
        anchors.top: parent.top
        anchors.topMargin: 315
        onClicked: fontDlg.open()
    }

    CustomButton {
        text: qsTr("Color dialog")
        anchors.right: parent.right
        anchors.rightMargin: 140
        anchors.top: parent.top
        anchors.topMargin: 315
        onClicked: colorDlg.open()
    }

    footer: Rectangle {
        anchors.bottom: parent.bottom
        width: parent.width
        height: 30
        gradient: Gradient {
            GradientStop { position: 0; color: "grey" }
            GradientStop { position: 0.4; color: "black" }
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
}

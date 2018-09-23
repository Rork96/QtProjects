import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("QmlDialogs")

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
    }

    Dialog {
        id: dlg
        title: "Simple dialog"

        contentItem: Rectangle {
            color: "lightskyblue"
            implicitWidth: 400
            implicitHeight: 150

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

    FileDialog {
        id: fileDlg
        title: "Choose a file"
        selectMultiple: false
        folder: shortcuts.home
        nameFilters: [ "Image files (*.jpg *.png *jpeg)", "All files (*)" ]
        modality: Qt.WindowModal
        onAccepted: pathText.text = fileUrl
    }

    FolderDialog {
       id: folderDialog
       title: "Choose a folder or a couple of folders"
       folder: shortcuts.home
       modality: Qt.WindowModal
       options: FolderDialog.ShowDirsOnly
       currentFolder: shortcuts.home
       onAccepted: pathText.text = folder
    }

    ColorDialog {
        id: colorDlg
        title: "Choose a color"
    }

    FontDialog {
        id: fontDlg
        title: "Choose a font"
    }

    Label {
        id: label
        text: qsTr("Text for a test")
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 20
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 75
    }

    Button {
        width: 142
        height: 40
        text: qsTr("Message dialog")
        anchors.left: parent.left
        anchors.leftMargin: 140
        anchors.top: parent.top
        anchors.topMargin: 155
        onClicked: {
            msgDlg.text = "Text in the message dialog"
            msgDlg.detailedText = "Some detailed text"
            //msgDlg.icon = MessageDialog.Information
            msgDlg.open()
        }
    }

    Button {
        x: 358
        width: 142
        height: 40
        text: qsTr("Dialog")
        anchors.right: parent.right
        anchors.rightMargin: 140
        anchors.top: parent.top
        anchors.topMargin: 155
        onClicked: {
            dlg.open()
        }
    }

    Button {
        width: 142
        height: 40
        text: qsTr("File dialog")
        anchors.top: parent.top
        anchors.topMargin: 235
        anchors.left: parent.left
        anchors.leftMargin: 140
        onClicked: {
            fileDlg.open()
        }
    }

    Button {
        x: 358
        width: 142
        height: 40
        text: qsTr("Folder dialog")
        anchors.top: parent.top
        anchors.topMargin: 235
        anchors.right: parent.right
        anchors.rightMargin: 140
        onClicked:  {
            folderDialog.open()
        }
    }

    Button {
        width: 142
        height: 40
        text: qsTr("Font dialog")
        anchors.left: parent.left
        anchors.leftMargin: 140
        anchors.top: parent.top
        anchors.topMargin: 315
    }

    Button {
        x: 358
        width: 142
        height: 40
        text: qsTr("Color dialog")
        anchors.right: parent.right
        anchors.rightMargin: 140
        anchors.top: parent.top
        anchors.topMargin: 315
    }

    footer: Rectangle {
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

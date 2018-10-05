import QtQuick 2.10
import QtQuick.Controls 2.4
import QtQuick.Dialogs 1.2

MainViewForm {
    signal openFileDialog
    signal openFolderDialog

    colorBtn.onClicked: {
        colorDlg.open()
    }

    fontBtn.onClicked: {
        fontDlg.open()
    }

    folderBtn.onClicked: {
        openFolderDialog() //folderDialog.open()
    }

    imageBtn.onClicked: {
        openFileDialog() //fileDlg.open()
    }

    dialogBtn.onClicked: {
        dlg.open()
    }

    messageBtn.onClicked: {
        msgDlg.text = "Text in the message dialog"
        msgDlg.detailedText = "Some detailed text"
        msgDlg.informativeText = "Informative text"
        msgDlg.icon = StandardIcon.Information
        msgDlg.open()
    }

    testText.font.pointSize: fontDlg.font.pointSize
    testText.font.family: fontDlg.font
    testText.font.weight: fontDlg.font.weight
    testText.font.italic: fontDlg.font.italic
    testText.font.underline: fontDlg.font.underline
    testText.font.overline: fontDlg.font.overline
    testText.font.strikeout: fontDlg.font.strikeout
    testText.color: colorDlg.color

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
                font.family: "Verdana"
                color: "navy"
                font.pointSize: 12
            }

            CustomButton {
                id: btnOk
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 10
                anchors.rightMargin: 10
                height: 30
                width: 80
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
}

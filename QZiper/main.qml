import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
import QtQuick.Dialogs 1.2

Window {
    id: root
    visible: true
    width: 600
    height: 500
    title: qsTr("QZiper")

    property string fileName
    //property QList<QUrl> fileNames

    FileDialog {
         /* File dialog */
         id: fileDialog
         title: qsTr("Choose file")
         modality: Qt.WindowModal // Show dialog as modal
         nameFilters: [ "Archives (*.zip *.rar *tar)" ]
         folder: shortcuts.home         // Home directory
         selectMultiple: fileDialogSelectMultiple.checked   // Multiple file selection
         selectFolder: fileDialogSelectFolder.checked       // Folders selection

         onAccepted: {
             /*selectMultiple ? console.log("You chose: " + fileDialog.fileUrls) :
                console.log("You chose: " + fileDialog.fileUrl)*/
             /*if (fileDialogSelectMultiple.checked)
             {
                 //for (var i = 0; i < fileUrls.length; ++i)
                     //Qt.openUrlExternally(fileUrls[i])
                     // fileNames = fileUrls
             }*/
             fileName = fileUrl
         }
    }

    MenuBar {
        /* Main menu */
        id: menuBar
        height: 40
        width: parent.width

        Menu {
            /* Menu file */
            id: menuFile
            title: qsTr("File")

            MenuItem {
                id: openItem
                text: qsTr("Open archive")

                onClicked: {
                    // Single selection
                    fileDialog.selectMultiple = false
                    fileDialog.selectFolder = false
                    fileDialog.open() // Open file
                    console.log(fileName)
                }
            }

            MenuItem {
                id: saveAsItem
                text: qsTr("Save as")

                onClicked: { /* Save file as */
                    fileDialog.selectMultiple = false
                    fileDialog.selectFolder = false
                    fileDialog.open()
                }
            }

            MenuItem {
                id: quitItem
                text: qsTr("Quit")
                onClicked: {
                    Qt.quit() // Quit
                }
            }
        }

        Menu {
            /* Menu Edit*/
            id: menuEdit
            title: qsTr("Edit")

            MenuItem {
                id: extractItem
                text: qsTr("Extract")

                onClicked: { /* Unpack file from archive */
                    // Multiple selection
                    fileDialog.selectMultiple = false
                    fileDialog.selectFolder = false
                    fileDialog.open()
                }
            }

            MenuItem {
                id: packFilesItem
                text: qsTr("Pack files")

                onClicked: { /* Pack files into archive */
                    fileDialog.selectMultiple = true
                    fileDialog.selectFolder = false
                    fileDialog.open()
                }
            }

            MenuItem {
                id: packFoldersItem
                text: qsTr("Pack folder")

                onClicked: { /* Pack folder into archive */
                    // Select folders
                    fileDialog.selectFolder = true
                    fileDialog.open()
                }
            }
        }

        Menu {
            /* Menu Help*/
            id: menuHelp
            title: qsTr("Help")

            MenuItem {
                id: aboutItem
                text: qsTr("About program")

                onClicked: { /* About program */ }
            }

            MenuItem {
                id: aboutQtItem
                text: qsTr("About Qt")

                onClicked: { /* About Qt */ }
            }
        }
    }
}

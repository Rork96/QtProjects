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

    // Select one or more files in FileDialog
    property bool selectMulty: false
    // Select folders in FileDialog
    property bool selectFolder: false

    FileDialog {
         /* File dialog */
         id: openFile
         title: qsTr("Choose file")
         modality: Qt.WindowModal // Show dialog as modal
         nameFilters: [ "Archives (*.zip *.rar *tar)" ]
         folder: shortcuts.home         // Home directory
         selectMultiple: selectMulty    // Multiple file selection
         selectFolder: selectFolder     // Folders selection

         onAccepted: {
            selectMultiple ? console.log("You chose: " + openFile.fileUrls) :
                console.log("You chose: " + openFile.fileUrl)
         }
    }

    MenuBar {
        /* Main menu */
        id: menuBar

        Menu {
            /* Menu file */
            id: menuFile
            title: qsTr("File")
            width: 95

            MenuItem {
                id: openItem
                text: qsTr("Open archive")

                onClicked: {
                    selectMulty = false
                    openFile.open() // Open file
                }
            }

            MenuItem {
                id: saveAsItem
                text: qsTr("Save as")

                onClicked: { /* Save file as */
                    selectMulty = false
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
            width: 95

            MenuItem {
                id: extractItem
                text: qsTr("Extract")

                onClicked: { /* Unpack file from archive */
                    selectMulty = false
                }
            }

            MenuItem {
                id: packFilesItem
                text: qsTr("Pack files")

                onClicked: { /* Pack files into archive */
                    selectMulty = true
                    openFile.open()
                }
            }

            MenuItem {
                id: packFolderItem
                text: qsTr("Pack folders")

                onClicked: { /* Pack folder into archive */
                    selectMulty = true
                }
            }
        }

        Menu {
            /* Menu Help*/
            id: menuHelp
            title: qsTr("Help")
            width: 95

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

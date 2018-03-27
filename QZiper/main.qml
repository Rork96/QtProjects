import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
import QtQuick.Dialogs 1.4

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
         selectFolders: selectFolder    // Folders selection

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
            id: mainMenu
            title: qsTr("File")
            width: 95

            MenuItem {
                id: openItem
                text: qsTr("Open archive")

                onClicked: {
                    openFile.open() // Open file
                }
            }

            MenuItem {
                id: saveAsItem
                text: qsTr("Save as")

                onClicked: { /* Save file as */ }
            }

            MenuItem {
                id: minItem
                text: qsTr("Minimize")

                onClicked: {
                    root.showMinimized() // Minimized
                }
            }

            MenuItem {
                id: normalItem
                text: qsTr("Normal")

                onClicked: {
                    root.showNormal() // Normal size
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
            id: mainMenu
            title: qsTr("Edit")
            width: 95

            MenuItem {
                id: unpackItem
                text: qsTr("Extract")

                onClicked: { /* Unpack file from archive */ }
            }

            MenuItem {
                id: packItem
                text: qsTr("Pack files")

                onClicked: { /* Pack files into archive */ }
            }

            MenuItem {
                id: maxItem
                text: qsTr("Pack folders")

                onClicked: { /* Pack folders into archive */ }
            }
        }
    }
}

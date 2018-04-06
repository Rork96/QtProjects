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

    FileDialog {
         /* File dialog */
         id: openArchive
         title: qsTr("Choose archive")
         modality: Qt.WindowModal           // Show dialog as modal
         nameFilters: [ "Archives (*.zip *.rar *tar)" ]
         folder: shortcuts.home             // Home directory

         onAccepted: {
             /* Open archive */
             appCore.openArchive(fileUrl)
         }
    }

    FileDialog {
        /* Pack folder */
        id: packFolder
        title: qsTr("Choose folder")
        modality: Qt.WindowModal       // Show dialog as modal
        nameFilters: [ "" ]
        folder: shortcuts.home         // Home directory
        selectFolder: true             // For folders

        onAccepted: {
            /* Compress dir */
            appCore.compressDir("", fileUrl)
            }
    }

    FileDialog {
        /* Pack files */
        id: packFiles
        title: qsTr("Choose files")
        modality: Qt.WindowModal       // Show dialog as modal
        nameFilters: [ "" ]
        folder: shortcuts.home         // Home directory

        onAccepted: {
            /* Compress files */
            appCore.compressFiles(fileUrl, "")
        }
    }

    MenuBar {
        /* Main menu */
        id: menuBar
        height: 40
        width: parent.width
        font.pointSize: 10

        Menu {
            /* Menu file */
            id: menuFile
            title: qsTr("File")
            font.pointSize: 10

            MenuItem {
                id: openItem
                text: qsTr("Open archive")

                onClicked: {
                    // Single selection
                    openArchive.open() // Open file
                }
            }

            MenuItem {
                id: saveAsItem
                text: qsTr("Save as")

                onClicked: {
                    /* Save file as */
                }
            }

            MenuSeparator { }

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
            font.pointSize: 10

            MenuItem {
                id: extractItem
                text: qsTr("Extract")

                onClicked: {
                    /* Unpack file from archive */
                    // Multiple selection
                }
            }

            MenuItem {
                id: packFilesItem
                text: qsTr("Pack files")

                onClicked: {
                    /* Pack files into archive */
                    // Select files
                    packFiles.open()
                }
            }

            MenuItem {
                id: packFoldersItem
                text: qsTr("Pack folder")

                onClicked: {
                    /* Pack folder into archive */
                    // Select folders
                    packFolder.open()
                }
            }
        }

        Menu {
            /* Menu Help*/
            id: menuHelp
            title: qsTr("Help")
            font.pointSize: 10

            MenuItem {
                id: aboutItem
                text: qsTr("About program")

                onClicked: {
                    /* About program */
                    appCore.aboutProgram()
                }
            }

            MenuItem {
                id: aboutQtItem
                text: qsTr("About Qt")

                onClicked: {
                    /* About Qt */
                    appCore.aboutQt()
                }
            }
        }
    }
}

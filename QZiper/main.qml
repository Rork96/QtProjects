import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 1.4
import QtQuick.Controls 2.3
import QtQuick.Dialogs 1.2
import QtQml.Models 2.3

Window {
    id: root
    visible: true
    width: 600
    height: 500
    title: qsTr("QZiper")
    //ico: "./pict/QZiper.ico"

    MenuBar {
        /* Main menu */
        id: menuBar
        height: 35
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
                    appCore.openArchive() // Open file
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
                    appCore.extractArchive()
                }
            }

            MenuItem {
                id: packFilesItem
                text: qsTr("Pack files")

                onClicked: {
                    /* Pack files into archive */
                    // Select files
                    //packFiles.open()
                    appCore.compressFiles()
                }
            }

            MenuItem {
                id: packFoldersItem
                text: qsTr("Pack folder")

                onClicked: {
                    /* Pack folder into archive */
                    // Select folders
                    //packFolder.open()
                    appCore.compressDir()
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

    ItemSelectionModel {
        id: sel
        model: fileSystemModel
    }

    TreeView {
        id: treeView
        y: menuBar.height
        height: root.height - menuBar.height
        width: root.width
        //model: fileSystemModel
        model: DelegateModel {
            model: appCore.fileSystemModel
        }
        rootIndex: rootPathIndex
        selection: sel

        TableViewColumn {
            id: nameColumn
            title: "Name"
            role: "fileName"
            resizable: true
            horizontalAlignment : Text.Center
            width: treeView.width - sizeColumn.width - dateColumn.width - 5
        }

        TableViewColumn {
            id: sizeColumn
            title: "Size"
            role: "size"
            resizable: true
            horizontalAlignment : Text.Center
            width: 120
        }

        TableViewColumn {
            id: dateColumn
            title: "Date Modified"
            role: "lastModified"
            resizable: true
            horizontalAlignment : Text.Center
            width: 150
        }

        onActivated: {
            var url = fileSystemModel.data(index, FileSystemModel.UrlStringRole)
            Qt.openUrlExternally(url)
        }
    }
}

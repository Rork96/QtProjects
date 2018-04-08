import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 1.4
import QtQuick.Controls 2.3
import QtQuick.Dialogs 1.2
import QtQml.Models 2.3
import Qt.labs.folderlistmodel 2.1

ApplicationWindow {
    id: root
    visible: true
    width: 600
    height: 500
    title: qsTr("QZiper")

    MenuBar {
        /* * * Main menu * * */
        id: menuBar
        height: 35
        width: parent.width
        font.pointSize: 10

        Menu {
            /* * * Menu file * * */
            id: menuFile
            title: qsTr("File")
            font.pointSize: 10

            MenuItem {
                id: openItem
                text: qsTr("Open archive")

                onClicked: {
                    // Single selection
                    appCore.openArchive(treeView) // Open file
                }
            }

            MenuItem {
                id: saveAsItem
                text: qsTr("Save as")

                onClicked: {
                    // Save file as
                    appCore.saveAs()
                }
            }

            MenuSeparator { }

            MenuItem {
                id: quitItem
                text: qsTr("Quit")

                onClicked: {
                    appCore.close()
                    Qt.quit() // Quit
                }
            }
        }

        Menu {
            /* * * Menu Edit * * */
            id: menuEdit
            title: qsTr("Edit")
            font.pointSize: 10

            MenuItem {
                id: extractItem
                text: qsTr("Extract")

                onClicked: {
                    // Extract archive
                    appCore.extractArchive()
                }
            }

            MenuItem {
                id: packFilesItem
                text: qsTr("Pack files")

                onClicked: {
                    // Compress files into archive
                    appCore.compressFiles()
                }
            }

            MenuItem {
                id: packFoldersItem
                text: qsTr("Pack folder")

                onClicked: {
                    // Compress folder into archive
                    appCore.compressDir()
                }
            }
        }

        Menu {
            /* * * Menu Help * * */
            id: menuHelp
            title: qsTr("Help")
            font.pointSize: 10

            MenuItem {
                id: aboutItem
                text: qsTr("About program")

                onClicked: {
                    // About program
                    appCore.aboutProgram()
                }
            }

            MenuItem {
                id: aboutQtItem
                text: qsTr("About Qt")

                onClicked: {
                    // About Qt
                    appCore.aboutQt()
                }
            }
        }
    }

    FolderListModel {
        /* * * File system model * * */
        id: fileSystemModel
        //showDirs: true
        showDirsFirst: true
        sortField: FolderListModel.Name
        folder: treeView.path // Current path
    }

    Rectangle {
        /* * * Go to parent dir * * */
        y: parent.height - height
        height: 32
        width: parent.width
        visible: treeView.elemntVisible

        Row {
            anchors.fill: parent

            Button {
                id: button
                width: 32
                height: 32
                text: "<<<"

                onClicked: {
                    // Step out of the start directory is forbidden
                    if (treeView.path != treeView.startPath) {
                        // Parent dir
                        treeView.path = fileSystemModel.parentFolder
                        curPath.text = " " + treeView.path
                    }
                }
            }

            Text {
                id: curPath
                text: " " + treeView.path // Current path
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    TreeView {
        /* * * View file system * * */
        property string path: ""        // Current path
        property string startPath: ""   // For saving start path
        // Visibility of treeView and "Go to parent dir" Rectangle
        property bool elemntVisible: false

        id: treeView
        y: menuBar.height
        height: root.height - menuBar.height - button.height
        width: root.width
        model: fileSystemModel
        clip: true
        visible: elemntVisible
        selection: ItemSelectionModel {
            /* * * To be able to get the index of the selected item * * */
            id: itemSelectionModel
            model: fileSystemModel
        }
        selectionMode: SelectionMode.SingleSelection

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
            role: "fileSize"
            resizable: true
            horizontalAlignment : Text.Center
            width: 120
        }

        TableViewColumn {
            id: dateColumn
            title: "Modified"
            role: "fileModified"
            resizable: true
            horizontalAlignment : Text.Center
            width: 180
        }

        itemDelegate: Item {
            /* * * Delegate for file system model * * */
            id: item
            Text {
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                renderType: Text.NativeRendering
                text: styleData.value
            }
        }

        onDoubleClicked: {
            /* * * User double clicked on item * * */

            // Get the index of the selected element
            var ind = treeView.selection.currentIndex.row
            if (fileSystemModel.isFolder(ind)) {
                // Go to directory
                treeView.path = fileSystemModel.get(ind, "fileURL")
                // Change current path in the "curPath"
                curPath.text = " " + treeView.path
            }
            else {
                // Open file
                Qt.openUrlExternally(fileSystemModel.get(ind, "fileURL"))
            }
        }
    }

    onClosing: {
        /* * * Delete start folder before closing * * */

        appCore.close()
    }
}

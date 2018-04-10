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

    property url fileName: ""
    property string infString: " Ready ..."

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

            FileDialog {
                id: openArch
                title: qsTr("Choose archive")
                modality: Qt.WindowModal       // Show dialog as modal
                nameFilters: [ "*.zip" ]
                folder: shortcuts.home         // Home directory

                onAccepted: {
                    // Select archive file
                    root.fileName = fileUrl
                    if (appCore.openArchive(treeView, fileUrl)) {
                        root.infString = " << Back"
                    }
                    else {
                        root.infString = " Opening rejected ..."
                    }
                    progress.visible = false
                }
            }

            MenuItem {
                id: openItem
                text: qsTr("Open archive")

                onClicked: {
                    // Open file
                    root.infString = " Progress ... "
                    progress.visible = true
                    openArch.open()
                }
            }

            MessageDialog {
                id: msgDialog
                title: qsTr("QZiper")
                text: qsTr("Open archive before saving!")
                icon: StandardIcon.Information
                standardButtons: standardButtons.Ok

                onAccepted: {
                    root.infString = " Archive not opened ..."
                }
            }

            MenuItem {
                id: saveAsItem
                text: qsTr("Save as")

                onClicked: {
                    // Save file as
                    if (treeView.elemntVisible) {
                        // Save archive
                        root.infString = " Progress ... "
                        progress.visible = true
                        if (appCore.saveAs(root)) {
                            root.infString = " Archive saved ..."
                        }
                        else {
                            root.infString = " Saving rejected ..."
                        }
                        progress.visible = false
                    }
                    else {
                        // Show Message
                        msgDialog.open()
                    }
                }
            }

            MenuSeparator { }

            MenuItem {
                id: closeArchItem
                text: qsTr("Close archive")

                onClicked: {
                    if (treeView.elemntVisible) {
                        treeView.elemntVisible = false
                        root.fileName = ""
                        root.infString = " Archive closed ..."
                    }
                    else {
                        root.infString = " Archive not opened ..."
                    }
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
                    if (treeView.elemntVisible) {
                        // Extract opened archive
                        root.infString = " Progress ... "
                        progress.visible = true
                        if (appCore.extractArchive(root)) {
                            root.infString = " Archive extracted ..."
                        }
                        else {
                            root.infString = " Extraction rejected ..."
                        }
                        progress.visible = false
                    }
                    else {
                        // Open archive
                        extractArchive.show()
                    }
                }
            }

            MenuItem {
                id: packFilesItem
                text: qsTr("Compress files")

                onClicked: {
                    // Compress files into archive
                    compressFiles.show()
                }
            }

            MenuItem {
                id: packFoldersItem
                text: qsTr("Compress folder")

                onClicked: {
                    // Compress folder into archive
                    compressFolder.show()
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
                    root.infString = " Ready ..."
                }
            }

            MenuItem {
                id: aboutQtItem
                text: qsTr("About Qt")

                onClicked: {
                    // About Qt
                    appCore.aboutQt()
                    root.infString = " Ready ..."
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
        visible: true

        Row {
            anchors.fill: parent

            Button {
                id: button
                visible: treeView.elemntVisible
                width: 32
                height: 32
                text: "<<<"

                onClicked: {
                    // Step out of the start directory is forbidden
                    if (treeView.path != treeView.startPath) {
                        // Parent dir
                        treeView.path = fileSystemModel.parentFolder
                    }
                }
            }

            Text {
                id: curPath
                text: infString
                anchors.verticalCenter: parent.verticalCenter
            }

            ProgressBar {
                id: progress
                indeterminate: true // Progress is unknown
                visible: false
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
            id: itemDeleg
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

    Compress {
        /* Compress files */
        id: compressFiles

        onSignalCompress: {
            /* * * Compress * * */
            root.infString = " Progress ... "
            progress.visible = true
            if (appCore.compressFiles(compressFiles)) {
                root.infString = " Files compressed ..."
            }
            else {
                root.infString = " Compression rejected ..."
            }
            progress.visible = false
            // Close window
            compressFiles.close()
        }

        FileDialog {
            id: files
            title: qsTr("Choose files for compression")
            modality: Qt.WindowModal       // Show dialog as modal
            nameFilters: [ "*" ]
            folder: shortcuts.home         // Home directory
            selectMultiple: true

            onAccepted: {
                // Files name
                // Format fileUrls into string with ";" as separator
                for (var i = 0; i < fileUrls.length; ++i)
                    compressFiles.fileName += fileUrls[i] + ";"
            }
        }

        onSignalCoose: {
            /* * * Choosing files for compression * * * */
            files.open()
        }

        onSignalCansel: {
            // Close window
            root.infString = " Rejected ..."
            compressFiles.close()
        }
    }

    Compress {
        /* Compress folder */
        id: compressFolder

        onSignalCompress: {
            /* * * Compress * * */
            root.infString = " Progress ... "
            progress.visible = true
            if (appCore.compressDir(compressFolder)) {
                root.infString = " Folder compressed ..."
            }
            else {
                root.infString = " Compression rejected ..."
            }
            progress.visible = false
            // Close window
            compressFolder.close()
        }

        FileDialog {
            id: folder
            title: qsTr("Choose folder for compression")
            modality: Qt.WindowModal       // Show dialog as modal
            nameFilters: [ "*" ]
            folder: shortcuts.home         // Home directory
            selectFolder: true             // For folders

            onAccepted: {
                // Folder name
                compressFolder.fileName = fileUrl
            }
        }

        onSignalCoose: {
            /* * * Choosing folder for compression * * * */
            folder.open()
        }

        onSignalCansel: {
            // Close window
            root.infString = " Rejected ..."
            compressFolder.close()
        }
    }

    ExtractArc {
        /* Compress folder */
        id: extractArchive

        onSignalExtract: {
            /* * * Compress * * */
            root.infString = " Progress ... "
            progress.visible = true
            if (appCore.extractArchive(extractArchive)) {
                root.infString = " Archive extracted ..."
            }
            else {
                root.infString = " Extraction rejected ..."
            }
            progress.visible = false
            // Close window
            extractArchive.close()
        }

        FileDialog {
            id: pathDlg
            title: qsTr("Choose folder for compression")
            modality: Qt.WindowModal       // Show dialog as modal
            nameFilters: [ "*.zip" ]
            folder: shortcuts.home         // Home directory

            onAccepted: {
                // Folder name
                extractArchive.fileName = fileUrl
            }
        }

        onSignalCoose: {
            /* * * Choosing folder for compression * * * */
            pathDlg.open()
        }

        onSignalCansel: {
            // Close window
            root.infString = " Rejected ..."
            extractArchive.close()
        }
    }
}

import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.4
import QtQml.Models 2.3
import Qt.labs.folderlistmodel 2.2
import Qt.labs.platform 1.0

Page {  // DialogPage
    id: dlgPage

    property string path: initPath.toString()
    property alias initPath: fileSystemModel.folder
    property alias filter: fileSystemModel.nameFilters
    property alias showFiles: fileSystemModel.showFiles
    signal selected
    signal rejected

    header: Rectangle {
        width: parent.width
        height: 28

        Button {
            id: backBtn
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            width: 28
            height: width
            icon.source: "qrc:/pict/up.png"
            background: Rectangle { color: "white" }
            onClicked: {
                path = path.replace(path.substring(path.lastIndexOf("/"), path.length), "")
                if (path.lastIndexOf(":") === path.length-1) path += "/"
                fileSystemModel.folder = path
            }
        }

        Label {
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            text: dlgPage.path
            font.pointSize: 10
            width: parent.width - backBtn.width - 25
        }
    }

    footer: Rectangle {
        width: parent.width
        height: 32

        Row {
            width: parent.width
            anchors.bottomMargin: 5
            spacing: 5

            Button {
                anchors.right: openBtn.left
                anchors.rightMargin: 5
                width: 52
                height: 26
                text: "Cansel"
                background: Rectangle { color: "white" }
                onClicked: rejected()
            }

            Button {
                id: openBtn
                anchors.right: parent.right
                anchors.rightMargin: 5
                width: 52
                height: 26
                text: "Select"
                background: Rectangle { color: "white" }
                onClicked: {
                    path = fileSystemModel.get(treeView.selection.currentIndex.row, "fileURL")
                    selected()
                }
            }
        }
    }

    TreeView {
        id: treeView
        anchors.fill: parent
        clip: true
        headerVisible: false
        model: FolderListModel {
            /* * * File system model * * */
            id: fileSystemModel
            showDirsFirst: true
            sortField: FolderListModel.Name
            nameFilters: [ "*.*" ]
            folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation) // Documents directory
        }
        selection: ItemSelectionModel {
            /* * * To be able to get the index of the selected item * * */
            id: itemSelectionModel
            model: fileSystemModel
        }
        selectionMode: SelectionMode.SingleSelection

        TableViewColumn {
            width: 38
            delegate: Image {
                id: img
                fillMode: Image.PreserveAspectFit
                source: if (fileSystemModel.isFolder(styleData.row)) {
                            return "qrc:/pict/folder.png"
                        }
                        else {
                            return "qrc:/pict/file.png"
                        }
            }
        }

        TableViewColumn {
            id: nameColumn
            role: "fileName"
        }

        //itemDelegate: Item {
            /* * * Delegate for file system model * * */
            /*id: itemDeleg
            Text {
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                renderType: Text.NativeRendering
                text: styleData.value
            }
        }*/

        onDoubleClicked: {
            /* * * User double clicked on item * * */

            // Get the index of the selected element
            var ind = treeView.selection.currentIndex.row
            if (fileSystemModel.isFolder(ind)) {
                dlgPage.path = fileSystemModel.get(ind, "fileURL")
                // Go to directory
                fileSystemModel.folder = fileSystemModel.get(ind, "fileURL")
            }
        }
    }
}

import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.4
import QtQml.Models 2.3
import Qt.labs.folderlistmodel 2.2

Page {  // DialogPage
    id: dlgPage

    property string path: initPath.toString()
    property alias initPath: fileSystemModel.folder
    signal selected
    signal rejected

    header: Rectangle {
        width: parent.width
        height: 40

        Button {
            id: backBtn
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            width: 26
            height: width
            icon.source: "qrc:/pict/up.png"
            onClicked: {
                path = path.replace(path.substring(path.lastIndexOf("/"), path.length), "/")
                fileSystemModel.folder = path
            }
        }

        Label {
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            text: dlgPage.path
            font.pointSize: 12
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

            ComboBox {
                anchors.left: parent.left
                anchors.leftMargin: 15
                width: 250
                height: 26
            }

            Button {
                anchors.right: openBtn.left
                anchors.rightMargin: 5
                width: 52
                height: 26
                text: "Cansel"
                onClicked: rejected()
            }

            Button {
                id: openBtn
                anchors.right: parent.right
                anchors.rightMargin: 5
                width: 52
                height: 26
                text: "Select"
                onClicked: {
                    path = fileSystemModel.get(treeView.selection.currentIndex.row, "fileURL")
                    console.log(path);
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
//            showDotAndDotDot: true
            sortField: FolderListModel.Name
            folder: "file:///D:" // Current path
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
                fillMode: Image.PreserveAspectFit
                source: if (fileSystemModel.isFolder(treeView.currentIndex)) {
                            return "qrc:/pict/folder.png"
                        }
                        else {
                            return "qrc:/pict/up.png"
                        }
            }
        }

        TableViewColumn {
            id: nameColumn
            role: "fileName"
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
                dlgPage.path = fileSystemModel.get(ind, "fileURL")
                // Go to directory
                fileSystemModel.folder = fileSystemModel.get(ind, "fileURL")
            }
            else {
                // Open file
                openBtn.clicked()
            }
        }
    }
}

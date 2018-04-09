import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0

Window {
    id: compress
    visible: false
    width: 400
    height: 190
    title: qsTr("Compress to zip")
    minimumWidth: 400
    minimumHeight: 190
    maximumWidth: 400
    maximumHeight: 190

    property var    fileName:       "" // Wrong type ?
    property url folderPath:        ""
    property string archiveName:    nameField.text

    signal signalCompress   // Start compression
    signal signalCoose      // Files or folder for compression
    signal signalCansel     // Close window

    function clearPath() {
        var path = compress.folderPath.toString()
        console.log(path)
        // Remove prefixed "file:///"
        path = path.replace(/^(file:\/{3})/,"")
        // Unescape html codes like '%23' for '#'
        var cleanPath = decodeURIComponent(path)
        pathField.text = cleanPath
    }

    FileDialog {
        id: folderDialog
        title: qsTr("Choose folder")
        modality: Qt.WindowModal       // Show dialog as modal
        nameFilters: [ "*" ]
        folder: shortcuts.home         // Home directory
        selectFolder: true             // For folders

        onAccepted: {
            compress.folderPath = fileUrl
            clearPath()
        }
    }

    Button {
        id: nameBtn
        x: 300
        y: 21
        width: 81
        height: 20
        text: qsTr("Choose ...")
        spacing: 0
        padding: 0
        font.pointSize: 10
        Layout.preferredHeight: 20
        Layout.preferredWidth: 42
        Layout.alignment: Qt.AlignLeft | Qt.AlignTop

        onClicked: {
            /* * * Choosing files or folder for compression * * */
            compress.signalCoose()
        }
    }

    Label {
        id: label
        y: 20
        height: 21
        text: qsTr("File name:")
        font.pointSize: 10
        anchors.right: parent.right
        anchors.rightMargin: 119
        anchors.left: parent.left
        anchors.leftMargin: 20
    }

    Label {
        id: label1
        y: 80
        height: 20
        text: qsTr("Folder:")
        font.pointSize: 10
        anchors.right: parent.right
        anchors.rightMargin: 19
        anchors.left: parent.left
        anchors.leftMargin: 20
    }

    RowLayout {
        y: 47
        height: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20

        TextField {
            id: nameField
            width: 258
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            padding: 0
            font.pointSize: 10
            Layout.preferredHeight: 20
            Layout.preferredWidth: 258
            placeholderText: qsTr("")
            text: "Archive"
        }
    }

    RowLayout {
        y: 106
        height: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20

        TextField {
            id: pathField
            padding: 0
            font.pointSize: 10
            Layout.preferredHeight: 20
            Layout.preferredWidth: 258
            placeholderText: qsTr("")
            text: "" // compress.folderPath
        }

        Button {
            id: pathBtn
            text: qsTr(" ... ")
            padding: 0
            spacing: 0
            font.pointSize: 10
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            Layout.preferredHeight: 20
            Layout.preferredWidth: 42

            onClicked: {
                /* * * Open file dialog to choose path * * */
                folderDialog.open()
            }
        }
    }

    RowLayout {
        y: 149
        height: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20

        Button {
            id: compressBtn
            text: qsTr("Compress")
            padding: 0
            spacing: 0
            font.pointSize: 10
            Layout.preferredHeight: 20
            Layout.preferredWidth: 90

            onClicked: {
                /* * * Compress * * */
                compress.signalCompress() // Call signal
            }
        }

        Button {
            id: canselBtn
            text: qsTr("Cansel")
            padding: 0
            spacing: 0
            font.pointSize: 10
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            Layout.preferredHeight: 20
            Layout.preferredWidth: 90

            onClicked: {
                /* * * Close window * * */
                compress.signalCansel()
            }
        }
    }

}

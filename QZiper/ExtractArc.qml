import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0

Window {
    id: extract
    visible: false
    width: 400
    height: 170
    title: qsTr("Extract from zip")
    minimumWidth: width
    minimumHeight: height
    maximumWidth: width
    maximumHeight: height

    property url fileName:      ""
    property url folderPath:    ""

    signal signalExtract   // Start extraction
    signal signalCoose      // Files or folder for extraction
    signal signalCansel     // Close window

    function clearPath() {
        var path = extract.folderPath.toString()
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
            extract.folderPath = fileUrl
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
            /* * * Choosing files or folder for extraction * * */
            extract.signalCoose()
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
        y: 52
        height: 20
        text: qsTr("Folder:")
        font.pointSize: 10
        anchors.right: parent.right
        anchors.rightMargin: 19
        anchors.left: parent.left
        anchors.leftMargin: 21
    }

    RowLayout {
        y: 78
        height: 20
        anchors.right: parent.right
        anchors.rightMargin: 19
        anchors.left: parent.left
        anchors.leftMargin: 21

        TextField {
            id: pathField
            padding: 0
            font.pointSize: 10
            Layout.preferredHeight: 20
            Layout.preferredWidth: 258
            placeholderText: qsTr("")
            text: "" // extract.folderPath
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
        y: 132
        height: 20
        anchors.right: parent.right
        anchors.rightMargin: 19
        anchors.left: parent.left
        anchors.leftMargin: 21

        Button {
            id: extractBtn
            text: qsTr("Extract")
            padding: 0
            spacing: 0
            font.pointSize: 10
            Layout.preferredHeight: 20
            Layout.preferredWidth: 90

            onClicked: {
                /* * * extract * * */
                extract.signalExtract() // Call signal
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
                extract.signalCansel()
            }
        }
    }

}

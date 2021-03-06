import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    title: qsTr("QMLDrag")
    width: 640
    height: 480

    header: Rectangle {
        height: 30
        width: parent.width
        gradient: Gradient {
            GradientStop { position: 0.7; color: "white" }
            GradientStop { position: 0.9; color: "lightGray" }
            GradientStop { position: 1.0; color: "gray" }
        }

        Text {
            anchors.centerIn: parent
            text: qsTr("Drag any item you want")
            font.pixelSize: 18
            font.bold: true
            color: "gray"
        }
    }

    MainPageForm {
        anchors.fill: parent
        button.onClicked: dlg.open()

        // Drag and drop for the QML components
        mouseArea.drag.target: button
        mouseArea.drag.axis: Drag.XAndYAxis
        mouseArea.onClicked: button.clicked()

        mouseArea1.drag.target: label
        mouseArea1.drag.axis: Drag.XAndYAxis

        mouseArea2.drag.target: busyIndicator
        mouseArea2.drag.axis: Drag.XAndYAxis

        MessageDialog {
            id: dlg
            text: "Drag and Drop Test in the QML"
            title: "QMLDrag"
        }
    }

    footer: Rectangle {
        height: 30
        width: parent.width
        gradient: Gradient {
            GradientStop { position: 0; color: "gray" }
            GradientStop { position: 0.1; color: "lightGray" }
            GradientStop { position: 0.3; color: "white" }
        }
    }
}

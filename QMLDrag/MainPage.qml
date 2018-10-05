import QtQuick 2.4
import QtQuick.Dialogs 1.2

MainPageForm {
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

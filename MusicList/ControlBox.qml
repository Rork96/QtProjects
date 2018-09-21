import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

CheckBox {  // ControlBox
    anchors.verticalCenter: parent.verticalCenter

    style: CheckBoxStyle {
        indicator: Rectangle {
            implicitWidth: 18
            implicitHeight: implicitWidth
            radius: implicitWidth/2
            border.color: control.activeFocus ? "darkblue" : "gray"
            border.width: 1

            Rectangle {
                implicitWidth: 16
                implicitHeight: implicitWidth
                visible: control.checked
                color: "grey"
                border.color: "#f5f2f2"
                radius: implicitWidth/2
                anchors.margins: 2
                anchors.fill: parent
            }
        }
    }
}

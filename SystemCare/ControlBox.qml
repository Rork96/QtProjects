import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

CheckBox {
    property string caption: "CheckBox"
    property string textColor: "white"
    property int fontSize: 16

    style: CheckBoxStyle {
        indicator: Rectangle {
            implicitWidth: 24
            implicitHeight: implicitWidth
            radius: implicitWidth/2
            border.color: control.activeFocus ? "darkblue" : "gray"
            border.width: 1
            Rectangle {
                implicitWidth: 22
                implicitHeight: implicitWidth
                visible: !control.checked
                color: "#003c9e"
                border.color: "#f5f2f2"
                radius: implicitWidth/2
                anchors.margins: 2
                anchors.fill: parent
            }
        }
        label: Text {
            text: " " + caption
            font.pixelSize: fontSize
            color: !control.checked ? textColor : "grey"    // Reverse state (checked by default)
        }
    }
}

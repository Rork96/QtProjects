import QtQuick 2.4
import QtQuick.Controls 2.4

Page {
    id: page
    property alias mouseArea: mouseArea
    property alias button: button
    property alias label: label
    property alias mouseArea1: mouseArea1
    property alias busyIndicator: busyIndicator
    property alias mouseArea2: mouseArea2
    Button {
        id: button
        x: 160
        y: 220
        text: qsTr("Drag me")

        MouseArea {
            id: mouseArea
            anchors.fill: parent
        }
    }

    Label {
        id: label
        x: 135
        y: 140
        height: 33
        text: qsTr("Drag and Drop Test in the QML")
        font.pointSize: 20

        MouseArea {
            id: mouseArea1
            anchors.fill: parent
        }
    }

    BusyIndicator {
        id: busyIndicator
        x: 380
        y: 200
        width: 80
        height: 80
        wheelEnabled: false

        MouseArea {
            id: mouseArea2
            anchors.fill: parent
        }
    }

}


/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:7;anchors_height:100;anchors_width:100}
D{i:8;anchors_height:100;anchors_width:100}D{i:9;anchors_height:100;anchors_width:100}
D{i:6;anchors_height:80;anchors_width:80;anchors_x:280;anchors_y:301}
}
 ##^##*/

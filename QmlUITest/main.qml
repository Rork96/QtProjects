import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 400
    height: 400
    title: qsTr("Hello World")

    SwipeView {

        HomePage {
            anchors.fill: parent
        }
    }
}

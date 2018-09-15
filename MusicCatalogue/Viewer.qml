import QtQuick 2.9
//import QtQuick.Controls 2.2
import QtQuick.Window 2.10

Window {
    width: 400
    height: width

    property alias source: img.source

    Image {
        id: img
        anchors.fill: parent
        smooth: true
    }
}

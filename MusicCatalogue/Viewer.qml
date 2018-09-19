import QtQuick 2.9
//import QtQuick.Controls 2.2
import QtQuick.Window 2.10

Window {
    id: wnd
    width: Screen.width
    height: Screen.height

    property alias source: img.source

    Image {
        id: img
        anchors.centerIn: parent
        width: wnd.width
        height: wnd.width
        smooth: true
    }
}

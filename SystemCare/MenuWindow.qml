import QtQuick 2.10
import QtQuick.Window 2.10

Window { // MenuWindow
    id: wnd
    width: wndWidth
    height: wndHeight
    //visible: false
    flags: Qt.SubWindow | Qt.FramelessWindowHint
    color: Qt.darker("darkblue")

    property int wndWidth: 200
    property int wndHeight: 100

    onActiveFocusItemChanged: if (!activeFocusItem) wnd.visible = false
}

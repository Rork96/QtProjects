import QtQuick 2.10
import QtQuick.Window 2.0
import QtQuick.Controls 2.3

ApplicationWindow {
    visible: true
    width: if (Qt.platform.os === "android" || Qt.platform.os === "ios")
               return Screen.width;
           else return 400
    height: if (Qt.platform.os === "android" || Qt.platform.os === "ios")
                return Screen.height;
            else return 600
    title: qsTr("Music Catalogue")

    SwipeView {
        anchors.fill: parent
        currentIndex: 1

        MenuPage {
            id: menu
            width: parent.width
            height: parent.height
            artistFont: 20
            albumFont: 18
            yearFont: 16
            imageVisible: true
        }

        MainPage {
            id: page
            width: parent.width;
            height: parent.height
            artistFont: menu.artistFont
            albumFont: menu.albumFont
            yearFont: menu.yearFont
            imageVisible: menu.imageVisible
        }
    }
}

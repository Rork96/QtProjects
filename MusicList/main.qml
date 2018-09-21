import QtQuick 2.9
import QtQuick.Window 2.0
import QtQuick.Controls 2.2

ApplicationWindow {
    visible: true
    width: if (Qt.platform.os === "android" || Qt.platform.os === "ios")
               return Screen.width;
           else return 400
    height: if (Qt.platform.os === "android" || Qt.platform.os === "ios")
                return Screen.height;
            else return 600
    title: qsTr("Music List")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: 0
        interactive: false

        MainPage {
            id: page
            artistFont: menu.artistFont
            albumFont: menu.albumFont
            yearFont: menu.yearFont
            imageVisible: menu.imageVisible
            onChangePage: swipeView.currentIndex = 1
        }

        MenuPage {
            id: menu
            artistFont: 20
            albumFont: 18
            yearFont: 16
            imageVisible: true
            onChangePage: swipeView.currentIndex = 0
        }
    }
}

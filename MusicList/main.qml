import QtQuick 2.9
import QtQuick.Window 2.0
import QtQuick.Controls 2.2
import Qt.labs.settings 1.0

ApplicationWindow { // MainWindow
    visible: true
    width: if (Qt.platform.os === "android" || Qt.platform.os === "ios")
               return Screen.width;
           else return 400
    height: if (Qt.platform.os === "android" || Qt.platform.os === "ios")
                return Screen.height;
            else return 600
    title: qsTr("Music List")

    Settings {  // Save and load app settings
        id: settings
        property alias artist: menu.artistFont
        property alias album: menu.albumFont
        property alias year: menu.yearFont
        property alias image: menu.imageVisible
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: 0
        interactive: false

        MainPage {
            artistFont: settings.artist
            albumFont: settings.album
            yearFont: settings.year
            imageVisible: settings.image
            onChangePage: swipeView.currentIndex = 1
        }

        MenuPage {
            id: menu
            onChangePage: swipeView.currentIndex = 0
        }
    }
}

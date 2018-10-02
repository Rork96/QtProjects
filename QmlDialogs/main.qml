import QtQuick 2.10
import QtQuick.Window 2.3
import QtQuick.Controls 2.4
import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("QmlDialogs")

    SwipeView {
           id: swipeView
           anchors.fill: parent
           currentIndex: 0
           interactive: false

           MainPage {
               id: mainPage
               onOpenFileDialog: {
                   dlgPage.showFiles = true
                   dlgPage.path = StandardPaths.writableLocation(StandardPaths.DocumentsLocation)       // Documents directory
                   dlgPage.initPath = StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
                   dlgPage.filter = [ "*.*" ]
                   swipeView.currentIndex = 1
               }
               onOpenFolderDialog: {
                   dlgPage.showFiles = false
                   dlgPage.path = StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
                   dlgPage.initPath = StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
                   swipeView.currentIndex = 1
               }
           }

           DialogPage {
               id: dlgPage
               onSelected: {
                   mainPage.path = path
                   swipeView.currentIndex = 0
               }
               onRejected: swipeView.currentIndex = 0
           }
       }
}

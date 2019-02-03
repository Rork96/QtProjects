import QtQuick 2.10
import QtQuick.Window 2.3
import QtQuick.Controls 2.4
import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: if (Qt.platform.os === "android" || Qt.platform.os === "ios")
               return Screen.width;
           else return 640
    height: if (Qt.platform.os === "android" || Qt.platform.os === "ios")
                return Screen.height;
            else return 480
    title: qsTr("QmlDialogs")

    property bool folder: false

    SwipeView {
           id: swipeView
           anchors.fill: parent
           currentIndex: 0
           interactive: false   // Flipping is forbidden

           MainView {
               id: mainPage
               onOpenFileDialog: {
                   dlgPage.showFiles = true
                   dlgPage.path = StandardPaths.writableLocation(StandardPaths.PicturesLocation)       // Pictures directory
                   dlgPage.initPath = StandardPaths.writableLocation(StandardPaths.PicturesLocation)
                   dlgPage.filter = [ "*.jpg", "*.jpeg", "*.png" ]
                   swipeView.currentIndex = 1
                   folder = false
               }
               onOpenFolderDialog: {
                   dlgPage.showFiles = false
                   dlgPage.path = StandardPaths.writableLocation(StandardPaths.HomeLocation)        // Home directory
                   dlgPage.initPath = StandardPaths.writableLocation(StandardPaths.HomeLocation)
                   swipeView.currentIndex = 1
                   folder = true
               }
           }

           DialogPage { // Open file or folder dialog
               id: dlgPage
               onSelected: if (folder) {    // Folder
                               mainPage.pathTextText = path.substring(path.indexOf("/")+3, path.length)
                               swipeView.currentIndex = 0
                           }
                           else {   // File
                               imgView.imgPathText = path.substring(path.lastIndexOf("/")+1, path.length)
                               imgView.imageSource = path
                               swipeView.currentIndex = 2
                           }

               onRejected: swipeView.currentIndex = 0
           }

           ImageView {  // Show the image (image width was fitted by parent width)
               id: imgView
               backBtn.onClicked: swipeView.currentIndex = 0
           }
       }
}


/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:19;anchors_height:400}D{i:20;anchors_height:400}
D{i:18;anchors_height:400}D{i:13;anchors_height:400;anchors_width:200;anchors_x:220;anchors_y:29}
}
 ##^##*/

//import QtQuick 2.10
//import QtQuick.Window 2.10
//import QtQuick.Controls 2.3
//import QtQuick.Dialogs 1.2

import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2

Window {
    id: root
    visible: true
    width: 600
    height: 500
    title: qsTr("QZiper")

    FileDialog {
         /* Open file dialog */
         id: openFile
         title: qsTr("Choose file")
         modality: Qt.WindowModal // Show dialog as modal
         nameFilters: [ "Archives (*.zip *.rar *tar)" ]
         folder: shortcuts.home

         onAccepted: {
            console.log("You chose: " + openFile.fileUrls)
         }
    }

    MenuBar {
        /* Main menu */
        id: menuBar

        Menu {
            id: mainMenu
            title: qsTr("File")
            //width: 95

            MenuItem {
                id: openItem
                text: qsTr("Open file")

                /*onClicked: {
                    openFile.open() // Open file
                }*/
            }

            MenuItem {
                id: saveAsItem
                text: qsTr("Save as")

                //onClicked: { /* Save file as */ }
            }

            MenuItem {
                id: unpackItem
                text: qsTr("Unpack")

                //onClicked: { /* Unpack file from archive */ }
            }

            MenuItem {
                id: packItem
                text: qsTr("Pack")

                //onClicked: { /* Pack file into archive */ }
            }

            MenuItem {
                id: maxItem
                text: qsTr("Maximize")

                /*onClicked: {
                    root.showMaximized() // Show window maximazed
                }*/
            }

            MenuItem {
                id: minItem
                text: qsTr("Minimize")

                /*onClicked: {
                    root.showMinimized() // Minimized
                }*/
            }

            MenuItem {
                id: normalItem
                text: qsTr("Normal")

                /*onClicked: {
                    root.showNormal() // Normal size
                }*/
            }

            MenuItem {
                id: quitItem
                text: qsTr("Quit")
                /*onClicked: {
                    Qt.quit() // Quit
                }*/
            }
        }
    }
}

import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import "ServiceFunctions.js" as Logic

ApplicationWindow {
    visible: true
    width: 1024
    height: 768
    title: qsTr("QML WebBrowser")

    Component.onCompleted: Logic.addScreen()    // Run after loading ApplicationWindow

    SwipeView {
        id: swipe
        anchors.fill: parent
    }

    Component {
        id: screenComponent

        Rectangle {
            Page1Form { anchors.fill: parent }
        }
    }

    footer: Rectangle {
        width: parent.width
        height: 32
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "lightGray"
            }
            GradientStop {
                position: 0.05
                color: "lightGray"
            }
            GradientStop {
                position: 0.07
                color: "white"
            }
            GradientStop {
                position: 1
                color: "white"
            }
        }

        RoundButton {   // Add new page
            id: btn
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 5
            width: height
            height: 26
            icon.source: "qrc:/pict/plus.png"
            icon.width: icon.height
            icon.color: "black"
            onClicked: Logic.addScreen()
        }

        RoundButton {   // Delete current page
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: btn.right
            anchors.leftMargin: 5
            width: height
            height: 26
            icon.source: "qrc:/pict/minus.png"
            icon.width: icon.height
            icon.color: "black"
            onClicked: Logic.removeScreen()
        }

        PageIndicator {
            id: indicator
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 10
            height: 30
            count: swipe.count
            currentIndex: swipe.currentIndex
            interactive: true
            onCurrentIndexChanged: swipe.currentIndex = currentIndex
        }
    }
}

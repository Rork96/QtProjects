import QtQuick 2.11
import QtQuick.Controls 1.4
import QtQuick.Controls 2.4

ApplicationWindow {
    visible: true
    width: 1024
    height: 768
    title: qsTr("QML WebBrowser")

    header: Rectangle {
        width: parent.width
        height: 30

        RoundButton {
            width: height
            height: 26
            text: swipeView.depth //swipeView.count
            anchors.centerIn: parent
            onClicked: { //swipeView.addTab("", component); console.log(swipeView.count) }
                swipeView.push(component)
            }
        }
    }

    //    SwipeView {
    //        id: swipeView
    //        anchors.fill: parent
    //        currentIndex: 0

    //        Page1Form {
    //            webView.onLoadingChanged: {
    //                if (loadRequest.errorString)
    //                    console.error(loadRequest.errorString);
    //            }
    //        }
    //    }

//    TabView {
//        id: swipeView
//        anchors.fill: parent
//        tabsVisible: false
//        currentIndex: indicator.currentIndex
//        clip: true

//        Tab {
//            Page1Form { anchors.fill: parent }
//        }
//    }

    StackView {
        id: swipeView
        anchors.fill: parent
        clip: true
        initialItem: component
        //currentItem: get(indicator.currentIndex)
    }

    PageIndicator {
        id: indicator
        anchors.bottom: swipeView.bottom
        anchors.horizontalCenter: swipeView.horizontalCenter
        count: swipeView.depth //swipeView.count
        currentIndex: swipeView.index //swipeView.currentIndex
        interactive: true
        onCurrentIndexChanged: swipeView.get(swipeView.get(indicator.currentIndex))
    }

    Component {
        id: component

        Page1Form {
            anchors.fill: parent
        }
    }
}

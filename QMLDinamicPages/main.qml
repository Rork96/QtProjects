import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: window
    visible: true
    width: 1024
    height: 768
    title: qsTr("QML WebBrowser")

    ColumnLayout {
        anchors.fill: parent
        spacing: 2
        Rectangle {
            Layout.preferredHeight: 50
            Layout.fillWidth: true
            Row {
               Button {
                   text: "Add screen"
                   onClicked: addScreen();
               }
               Button {
                   text: "Add widget"
                   onClicked: addWidget();
               }
            }
        }

        SwipeView {
            id: swipe
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: indicator.currentIndex
        }
    }

    Component {
        id: screenComponent
        Rectangle {
            property alias view: view
            color: Qt.rgba(Math.random(),Math.random(),Math.random(),1)
            ListView {
                id: view
                spacing: 2
                anchors.fill: parent
                model: ListModel {}
                delegate: widgetComponent
            }
        }
    }
    Component {
        id: widgetComponent
        Button {
            text: name + "_" + index
        }
    }

    function addScreen()
    {
        var page = screenComponent.createObject(swipe);
        swipe.addItem(page);
        swipe.currentIndex = swipe.count - 1;
    }

    function addWidget()
    {
        var page = swipe.currentItem;
        if(page) {
            page.view.model.append({name: "widget"});
        }
    }

    footer: PageIndicator {
        id: indicator
        anchors.bottom: swipe.bottom
        anchors.horizontalCenter: swipe.horizontalCenter
        count: swipe.count
        currentIndex: swipe.currentIndex
        interactive: true
    }
}

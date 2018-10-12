import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ListView {
        id: listView
        anchors.fill: parent
        model: ListModel {
            ListElement { sender: "Bob Bobbleton"; title: "How are you going?" }
            ListElement { sender: "Rug Emporium"; title: "SALE! All rugs MUST go!" }
            ListElement { sender: "Electric Co."; title: "Electricity bill 15/07/2016 overdue" }
            ListElement { sender: "Tips"; title: "Five ways this tip will save your life" }
        }
        delegate: SwipeDelegate {
            id: swipeDelegate
            text: model.sender + " - " + model.title
            width: parent.width

            ListView.onRemove: SequentialAnimation {
                PropertyAction {
                    target: swipeDelegate
                    property: "ListView.delayRemove"
                    value: true
                }
                NumberAnimation {
                    target: swipeDelegate
                    property: "height"
                    to: 0
                    easing.type: Easing.InOutQuad
                }
                PropertyAction {
                    target: swipeDelegate
                    property: "ListView.delayRemove"
                    value: false
                }
            }

            swipe.right: Label {
                id: deleteLabel
                text: qsTr("Delete")
                color: "white"
                verticalAlignment: Label.AlignVCenter
                padding: 12
                height: parent.height
                anchors.right: parent.right

                SwipeDelegate.onClicked: listView.model.remove(index)

                background: Rectangle {
                    color: deleteLabel.SwipeDelegate.pressed ? Qt.darker("tomato", 1.1) : "tomato"
                }
            }

            swipe.left: Row {
                anchors.left: parent.left
                height: parent.height

                Label {
                    id: moveLabel
                    text: qsTr("Move")
                    color: "white"
                    verticalAlignment: Label.AlignVCenter
                    padding: 12
                    height: parent.height

                    SwipeDelegate.onClicked: console.log("Moving...")

                    background: Rectangle {
                        color: moveLabel.SwipeDelegate.pressed ? Qt.darker("#ffbf47", 1.1) : "#ffbf47"
                    }
                }
                Label {
                    id: delLabel
                    text: qsTr("Delete")
                    color: "white"
                    verticalAlignment: Label.AlignVCenter
                    padding: 12
                    height: parent.height

                    SwipeDelegate.onClicked: console.log("Deleting...")

                    background: Rectangle {
                        color: delLabel.SwipeDelegate.pressed ? Qt.darker("tomato", 1.1) : "tomato"
                    }
                }
            }
        }
    }
}

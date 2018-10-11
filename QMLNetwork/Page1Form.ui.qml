import QtQuick 2.11
import QtQuick.Controls 2.4
import QtWebView 1.1

Page {
    property alias webView: webView

    header: Rectangle {
        id: rectangle
        width: parent.width
        height: 42
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "white"
            }
            GradientStop {
                position: 0.95
                color: "white"
            }
            GradientStop {
                position: 0.97
                color: "lightGray"
            }
            GradientStop {
                position: 1
                color: "lightGray"
            }
        }

        Row {
            id: row
            anchors.fill: parent
            spacing: 15

            TextField {
                id: textUrl
                width: parent.width - (anchors.leftMargin * 2) - (backBtn.anchors.rightMargin * 3)
                       - backBtn.width - forwardBtn.width - updateBtn.width
                height: 30
                text: webView.url
                anchors.left: parent.left
                anchors.leftMargin: 10
                font.pointSize: 10
                font.family: "Verdana"
                renderType: Text.NativeRendering
                anchors.verticalCenter: parent.verticalCenter
            }

            RoundButton {
                id: backBtn
                width: height
                height: 26
                anchors.right: forwardBtn.left
                anchors.rightMargin: 15
                display: AbstractButton.IconOnly
                anchors.verticalCenter: parent.verticalCenter
                icon.source: "qrc:/pict/back.png"
                icon.width: icon.height
                icon.height: height / 2
                icon.color: "black"
            }

            RoundButton {
                id: forwardBtn
                width: height
                height: 26
                anchors.right: updateBtn.left
                anchors.rightMargin: 15
                display: AbstractButton.IconOnly
                anchors.verticalCenter: parent.verticalCenter
                icon.source: "qrc:/pict/forward.png"
                icon.width: icon.height
                icon.height: height / 2
                icon.color: "black"
            }

            RoundButton {
                id: updateBtn
                width: height
                height: 26
                anchors.right: parent.right
                anchors.rightMargin: 10
                display: AbstractButton.IconOnly
                anchors.verticalCenter: parent.verticalCenter
                icon.source: "qrc:/pict/update.png"
                icon.width: icon.height
                icon.height: height / 1.2
                icon.color: "black"
            }
        }
    }

    WebView {
        id: webView
        url: "https://www.google.com"
        anchors.fill: parent
    }

    Connections {
        target: backBtn
        onClicked: webView.goBack()
    }

    Connections {
        target: forwardBtn
        onClicked: webView.goForward()
    }

    Connections {
        target: updateBtn
        onClicked: webView.reload()
    }
}


/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/

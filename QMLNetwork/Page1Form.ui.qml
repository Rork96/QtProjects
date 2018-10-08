import QtQuick 2.11
import QtQuick.Controls 2.4
import QtWebView 1.1

Page {
    property alias webView: webView
    WebView {
        id: webView
        anchors.fill: parent
        url: "https://www.google.com"
    }
}


/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/

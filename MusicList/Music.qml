import QtQuick.XmlListModel 2.0

XmlListModel {  // Model for ListView in the MainPage
    source: "qrc:/android.xml"
    query: "/CDs/CD"
    XmlRole { name: "artist"; query: "artist/string()" }
    XmlRole { name: "album"; query: "album/string()" }
    XmlRole { name: "year"; query: "year/string()" }
    XmlRole { name: "cover"; query: "cover/string()" }
}

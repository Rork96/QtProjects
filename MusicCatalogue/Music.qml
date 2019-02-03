import QtQuick.XmlListModel 2.0

XmlListModel {
//    source: "file://" + applicationDirPath + "/music.xml"   // Linux
    source: "qrc:/android.xml"   // Android
    query: "/CDs/CD"
    XmlRole { name: "artist"; query: "artist/string()" }
    XmlRole { name: "album"; query: "album/string()" }
    XmlRole { name: "year"; query: "year/string()" }
    XmlRole { name: "cover"; query: "cover/string()" }
}

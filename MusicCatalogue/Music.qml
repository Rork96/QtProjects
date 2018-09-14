import QtQuick 2.0
//import QtQuick.XmlListModel 2.0

//XmlListModel {
//    source: "./music.xml"
//    query: "/CDs/CD"
//    XmlRole { name: "artist"; query: "artist/string()" }
//    XmlRole { name: "album"; query: "album/string()" }
//    XmlRole { name: "year"; query: "year/string()" }
//    XmlRole { name: "cover"; query: "cover/string()" }
//}

ListModel {
    ListElement {
        artist: "Amarante"
        album: "Amarante"
        year: 2011
        cover: "./covers/A.jpg"
    }
    ListElement {
        artist: "Korn"
        album: "Korn"
        year: 2010
        cover: "./covers/B.jpg"
    }
    ListElement {
        artist: "Nightwish"
        album: "Nightwish"
        year: 2012
        cover: "./covers/C.jpg"
    }
}

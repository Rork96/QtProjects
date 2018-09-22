import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.0

Page {
    id: homePage
    width: 400
    height: 400
    property alias homePage: homePage
    property alias login: login
    property alias password: password
    property alias email: email

    header: Rectangle {
        width: 400
        height: 40

        gradient: Gradient {
            GradientStop {
                position: 0
                color: "grey"
            }
            GradientStop {
                position: 0.3
                color: "black"
            }
            GradientStop {
                position: 0.7
                color: "black"
            }
            GradientStop {
                position: 1.0
                color: "grey"
            }
        }

        Text {
            anchors.centerIn: parent
            text: "LOGIN"
            color: "lightGrey"
            font.bold: true
            font.pointSize: 18
        }
    }

    TextField {
        id: email
        x: 96
        y: 94
        width: 209
        height: 45
        text: qsTr("")
        placeholderText: "email"
    }

    TextField {
        id: password
        x: 96
        y: 152
        width: 209
        height: 45
        text: qsTr("")
        placeholderText: "password"
    }

    Button {
        id: login
        x: 154
        y: 225
        width: 92
        height: 48
        text: qsTr("LOGIN")
    }
}

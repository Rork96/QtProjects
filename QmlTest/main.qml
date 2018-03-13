import QtQuick 2.7
import QtQuick.Controls 1.5

ApplicationWindow {
    visible: true
    width: 250
    height: 230
    title: qsTr("QmlTest")

    Label {
        id: label
        x: 23
        y: 9
        text: qsTr("Сумма двух чисел")
    }

    Label {
        id: label1
        x: 23
        y: 48
        text: qsTr("Число 1:")
    }

    Label {
        id: label2
        x: 23
        y: 97
        text: qsTr("Число 2:")
    }

    Label {
        id: resultLabel
        objectName: resultLabel
        x: 23
        y: 140
        width: 70
        height: 20
        text: qsTr("Результат:")
    }

    TextField {
        id: numberY
        objectName: numberY
        x: 99
        y: 92
        width: 130
        height: 30
    }

    TextField {
        id: appCore.getObjectId() //numberX
        objectName: numberY
        x: 99
        y: 40
        width: 130
        height: 30
    }

    Button {
        id: calckBtn
        x: 23
        y: 183
        width: 80
        text: qsTr("Расчет")
    }

    Connections {
        target: calckBtn
        onClicked: appCore.calck("data");   // Функция из класса AppCore
    }

    Connections {
        target: exitBtn
        onClicked: Qt.quit() // Выход
    }

    Button {
        id: exitBtn
        x: 149
        y: 183
        width: 80
        text: qsTr("Exit")
    }
}

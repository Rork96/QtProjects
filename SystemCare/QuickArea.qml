import QtQuick 2.0

Item {  // QuickArea
    anchors.fill: parent

    Rectangle {
        anchors.fill: parent
        color: "transparent"

        Row {
            id: rect
            //anchors.fill: parent
            anchors.centerIn: parent
            spacing: 50

            ControlElement {
            }

            ControlElement {
                id: quick
                x: quick.width + rect.spacing/2
                headerText: qsTr("Аппаратне ускорение")
                stateText: qsTr("")
                bodyText: qsTr("Устаревшие драйверы могут замедлять и дестабилизировать Ваш ПК. " +
                               "Пожалуйста, проверьте, есть ли кие-либо устаревшие драйверы.")
                buttonText: qsTr("Проверить")
                source: "qrc:/pict/startup.png"
            }

            ControlElement {
                id: optimize
                x: width*2 + rect.spacing
                headerText: qsTr("Глубокая оптимизация")
                stateText: qsTr("")
                bodyText: qsTr("Проверьте какие элементы могут быть оптимизированы для ускорения Вашей системы.")
                buttonText: qsTr("Оптимизировать")
                source: "qrc:/pict/diagram.png"
            }

            ControlElement {
                id: clear
                x: width*3 + rect.spacing*1.5
                headerText: qsTr("Очиститель приложений")
                stateText: qsTr("")
                bodyText: qsTr("Найдено: 0 плагинов/панелей инструментов. " +
                               "Установите Деинсталятор, чтобы удалить ненужные для более плавного просмотра.")
                buttonText: qsTr("Установить")
                source: "qrc:/pict/broom.png"
            }
        }
    }
}

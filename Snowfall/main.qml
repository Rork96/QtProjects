import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 1.4
import QtQuick.Particles 2.0

ApplicationWindow {
    visible: true
    width: Screen.width
    height: Screen.height
    visibility: ApplicationWindow.FullScreen

    Action {
            shortcut: "Esc"
            onTriggered: Qt.quit()
    }

    Rectangle {
        anchors.fill: parent

        Image {
            anchors.fill: parent
            source: "qrc:/pict/fon.jpg"
        }

        ParticleSystem {
            anchors.fill: parent

            ImageParticle {
                source: "qrc:/pict/snow.png"
            }

            Emitter {
                width: parent.width
                height: parent.height
                anchors.bottom: parent.bottom
                lifeSpan: 10000
                sizeVariation: 10
                emitRate: 100
                velocity: AngleDirection {
                    angle: 90
                    angleVariation: 30
                    magnitude: 500
                }
            }

            Gravity {
                y: parent.height/4
                width: parent.width
                height: parent.height
                angle: 0
                magnitude: 120
            }
        }
    }
}

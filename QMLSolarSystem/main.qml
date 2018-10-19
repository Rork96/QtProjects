import QtQuick 2.11
import QtQuick.Controls 2.4

ApplicationWindow {
    visible: true
    width: 300
    height: 500
    title: qsTr("Solar system")

    Item {
        width: parent.width
        height: parent.height

        Rectangle {
            anchors.fill: parent
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#4a4a4a" }
                GradientStop { position: 1.0; color: "#2b2b2b" }
            }
        }

        ListView {
            id: listView
            interactive: true   // by default

            anchors.fill: parent

            delegate: detailsDelegate
            model: planets
        }

        ListModel {
            id: planets

            ListElement { name: "Solar system"; imageSource: "images/solar_system.jpg"; facts: "The Solar System was formed approximately 4.6 billion years ago and consists of the Sun, planets, dwarf planets and other astronomical objects bound in its orbit. The formation was cause by the collapse of a giant molecular cloud, the mass at the centre collecting to form the Sun and a flat disk of dust around it which the planets and other bodies would eventually be formed from." }
            ListElement { name: "Sun"; imageSource: "images/sun.jpg"; facts: "The Sun (or Sol), is the star at the centre of our solar system and is responsible for the Earth’s climate and weather. The Sun is an almost perfect sphere. The temperature inside the Sun can reach 15 million degrees Celsius. Eventually, the Sun will consume the Earth. The Sun will one day be about the size of Earth." }
            ListElement { name: "Mercury"; imageSource: "images/mercury.jpg"; facts: "Mercury is the smallest planet in the Solar System. It is the closest planet to the sun. It makes one trip around the Sun once every 87.969 days." }
            ListElement { name: "Venus"; imageSource: "images/venus.jpg"; facts: "Venus is the second planet from the Sun. It is a terrestrial planet because it has a solid, rocky surface. The other terrestrial planets are Mercury, Earth and Mars. Astronomers have known Venus for thousands of years." }
            ListElement { name: "Earth"; imageSource: "images/earth.jpg"; facts: "The Earth is the third planet from the Sun. It is one of the four terrestrial planets in our Solar System. This means most of its mass is solid. The other three are Mercury, Venus and Mars. The Earth is also called the Blue Planet, 'Planet Earth', and 'Terra'." }
            ListElement { name: "Mars"; imageSource: "images/mars.jpg"; facts: "Mars is the fourth planet from the Sun in the Solar System. Mars is dry, rocky and cold. It is home to the largest volcano in the Solar System. Mars is named after the mythological Roman god of war because it is a red planet, which signifies the colour of blood." }
            ListElement { name: "Ceres"; imageSource: "images/ceres.jpg"; facts: "Located in the asteroid belt between the orbits of Mars and Jupiter, Ceres is the closest dwarf planet to the Sun and the only one located in the inner solar system. It's the smallest of the known dwarf planets at 950 km (590 mi) in diameter." }
            ListElement { name: "Jupiter"; imageSource: "images/jupiter.jpg"; facts: "The planet Jupiter is the fifth planet out from the Sun, and is two and a half times more massive than all the other planets in the solar system combined. It is made primarily of gases and is therefore known as a “gas giant”." }
            ListElement { name: "Saturn"; imageSource: "images/saturn.jpg"; facts: "Saturn is the sixth planet from the Sun and the most distant that can be seen with the naked eye. Saturn is the second largest planet and is best known for its fabulous ring system that was first observed in 1610 by the astronomer Galileo Galilei." }
            ListElement { name: "Uranus"; imageSource: "images/uranus.jpg"; facts: "Uranus is the seventh planet from the Sun. While being visible to the naked eye, it was not recognised as a planet due to its dimness and slow orbit. Uranus became the first planet discovered with the use of a telescope. Uranus is tipped over on its side with an axial tilt of 98 degrees." }
            ListElement { name: "Neptune"; imageSource: "images/neptune.jpg"; facts: "Neptune is the eighth planet from the Sun making it the most distant in the solar system. This gas giant planet may have formed much closer to the Sun in early solar system history before migrating to its present position. It takes Neptune 164.8 Earth years to orbit the Sun. Neptune was discovered by Jean Joseph Le Verrier. It has the second largest gravity of any planet in the solar system – second only to Jupiter." }
            ListElement { name: "Pluto"; imageSource: "images/pluto.jpg"; facts: "Discovered in 1930, Pluto is the second closest dwarf planet to the Sun and was at one point classified as the ninth planet. Pluto is the largest dwarf planet but only the second most massive, with Eris being the most massive." }
            ListElement { name: "Haumea"; imageSource: "images/haumea.jpg"; facts: "Haumea is the third closest dwarf planet to the Sun and is located beyond the orbit of Neptune. It has about 1/3 the mass of Pluto and was discovered by 2004 by a team from Caltech at the Palomar Observatory in the United States in a project headed by Mike Brown." }
            ListElement { name: "Makemake"; imageSource: "images/makemake.jpg"; facts: "Makemake is the largest of the Kuiper belt objects (KBO) and has only one satellite (moon). The extremely low temperature of the dwarf planet, about 30 K or −243.2 °C, means that the surface of Makemake is covered with methane, ethane, and possibly nitrogen ices." }
            ListElement { name: "Eris"; imageSource: "images/eris.jpg"; facts: "The dwarf planet was named for Eris, the Greek goddess of strife and discord. Eris has one satellite (moon) which is called Dysnomia and takes 16 Earth days to complete a full orbit. Eris was once considered to become the tenth planet of the solar system before the reclassification of Pluto in 2006." }
            ListElement { name: "Asteroid"; imageSource: "images/asteroid.jpg"; facts: "An asteroid is a small body orbiting the Sun that is composed primarily of rock or metal. In 1801, Giuseppe Piazzi discovered what he believed to be a new planet and named the object Ceres. It was soon realized that these new object were not, in fact, a planet. One characteristic these objects shared was their resemblance to distant stars as viewed through the telescopes of the time. As a result of their similar appearance to stars the objects were named asteroids, meaning “star shaped.”" }
            ListElement { name: "Comet"; imageSource: "images/comet.jpg"; facts: "A comet is a very smallobject made mostly of ices mixed with smaller amounts of dust and rock. Most comets are no larger than a few kilometres across. The main body of the comet is called the nucleus, and it can contain water, methane, nitrogen and other ices. When a comet is heated by the Sun, its ices begin to sublimate. The mixture of ice crystals and dust blows away from the comet nucleus in the solar wind, creating a tail. The dust tail is what we normally see from Earth." }
        }

        Component {
            id: detailsDelegate

            Item {
                id: wrapper

                width: listView.width
                height: 50

                Rectangle {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top

                    height: 49

                    color: "#333"
                    border.color: Qt.lighter(color, 1.2)
                    Text {
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.leftMargin: 4

                        font.pixelSize: parent.height-24
                        color: '#fff'

                        text: name
                    }
                }


                Rectangle {
                    id: image

                    width: 46
                    height: 46

                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.rightMargin: 2
                    anchors.topMargin: 2

                    color: "black"


                    Image {
                        anchors.fill: parent

                        fillMode: Image.PreserveAspectFit

                        source: imageSource
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: parent.state = "expanded"
                }

                Item {
                    id: factsView

                    anchors.top: image.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom

                    opacity: 0

                    Rectangle {
                        anchors.fill: parent

                        gradient: Gradient {
                            GradientStop { position: 0.0; color: "#fed958" }
                            GradientStop { position: 1.0; color: "#fecc2f" }
                        }
                        border.color: '#000000'
                        border.width: 2

                        Text {
                            anchors.fill: parent
                            anchors.margins: 5

                            clip: true
                            wrapMode: Text.WordWrap
                            color: '#1f1f21'

                            font.pixelSize: 12

                            text: facts
                        }
                    }
                }

                Rectangle {
                    id: closeButton

                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.rightMargin: 2
                    anchors.topMargin: 2

                    width: 36
                    height: 36

                    color: "transparent"

                    Image {
                        anchors.fill: parent
                        source: "images/right.png"
                    }

                    opacity: 0

                    MouseArea {
                        anchors.fill: parent
                        onClicked: wrapper.state = ""
                    }
                }

                states: [
                    State {
                        name: "expanded"

                        PropertyChanges { target: wrapper; height: listView.height }
                        PropertyChanges { target: image; width: listView.width; height: listView.width; anchors.rightMargin: 0; anchors.topMargin: 46 }
                        PropertyChanges { target: factsView; opacity: 1 }
                        PropertyChanges { target: closeButton; opacity: 1 }
                        PropertyChanges { target: wrapper.ListView.view; contentY: wrapper.y; interactive: false }  // Listing between an elements is restricted
                    }
                ]

                transitions: [
                    Transition {
                        NumberAnimation {
                            duration: 200;
                            properties: "height,width,anchors.rightMargin,anchors.topMargin,opacity,contentY"
                        }
                    }
                ]
            }
        }
    }
}

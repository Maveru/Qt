import QtQuick 2.15
import QtQuick.Window 2.15
import Football.lib 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Football team Demo")

    FootballTeam{
        id:team1
        title: "Real Madrid"
        coach: "Ancelotti"
        captain: cr7

        players: [

            Player{
                name: "Luka Modric"
                position: "MedioCentro"
                playing:true
            },
            Player{
                name: "Courtois"
                position: "Portero"
                playing:true
            },
            Player{
                id:cr7
                name: "Cristiano Ronaldo"
                position: "Delantero"
                playing:true
            },
            Player{
                name: "Marcos"
                position: "Banquillo"
                playing:false
            },
            Player{
                name: "Sergio Ramos"
                position: "Defensa"
                playing:true
            }
        ]
    }

    ListView{
        anchors.fill: parent
        model:team1.players
        delegate: Rectangle{
            width: parent.width
            height:50
            border.width: 1
            border.color: "black"

            color:team1.captain.name === name ? "pink" : "beige"

            Text{
                text: name
                anchors.centerIn: parent
                font.pointSize: 20
            }
        }
    }

    Component.onCompleted: {
        console.log("We have: " + team1.players.length + " players in " + team1.title)
        console.log("EL capitan es: "+ team1.captain.name)
    }
}

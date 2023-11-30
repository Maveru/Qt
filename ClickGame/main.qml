import QtQuick 2.15
import QtQuick.Window 2.15
import Randomlib 1.0
import Counterlib 1.0
import QtQuick.Controls.Windows
import QtQuick.Layouts
import QtQuick.LocalStorage
import QtQuick.Dialogs
import "db.js" as JS
ApplicationWindow  {
    id:root
    width: 500
    height: 500
    visible: true
    title: qsTr("Quick Clicker!")



    property int points: 0
    property var db
    property string username
    property int score
    property bool flag : false
    property int intervalue : 1000
    property string difficulty : "NORMAL"

    Counter{
        id:mCounter
        onCountStopped:{
            mCounter.stop()
            stateManager.state = "Score"
            JS.readingData()
        }
    }
    ColumnLayout{
        id : layout
        spacing: 20
        visible: false
        Rectangle{
            id:timer
            color:"beige"
            Text {
                id: timerText
                text: 10 - mCounter.count
            }
        }
        Rectangle{
            id:pointcounter
            color:"beige"
            Text {
                id: pointText
                text: points
            }
        }
    }



    ListModel {
        id: myModel
    }

    ListView {
        id:listScore
        width: parent.width
        height: parent.height
        visible: false
        model: myModel

        delegate: Item {
            width: root.width
            height: 50

            Rectangle {
                width: parent.width
                height: 50
                color: if(model.dif === "HARD")
                           "red"
                       else if(model.dif === "NORMAL")
                           "orange"
                       else
                           "green"

                Text {
                    anchors.centerIn: parent
                    text:  model.username + " --- " + model.score + " puntos"

                }


            }
        }

    }

    ColumnLayout{
        anchors.centerIn: parent
        spacing:  75

        Rectangle{
            id:scoreId
            visible: true
            border.color: "black"
            border.width: 50
            Text {
                id: scoreTextId
                text: points +" points!"
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
                Layout.margins: 10
            }
        }

        Button{
            id:startButton
            text:"START"
            onClicked: {
                mCounter.start()
                stateManager.state = "Playing"
                flag = false
                points = 0
            }
        }
        Row{
            Button{
                id:easyButton
                text:"EASY"
                onClicked: {
                    difficulty = "EASY"
                    intervalue = 3000
                }
            }
            Button{
                id:midButton
                text:"NORMAL"
                onClicked: {
                    difficulty = "NORMAL"
                    intervalue = 1000
                }
            }
            Button{
                id:hardButton
                text:"HARD"
                onClicked: {
                    difficulty = "HARD"
                    intervalue = 500
                }
            }
        }

        Rectangle{
            id:scoreRect
            visible:false
            color:"royalblue"

            Row{
                TextField {
                    id: nameInput
                    placeholderText: "Introduce tu Nombre"
                    height: nameBut.height
                    maximumLength: 50
                }

                Button {
                    id:nameBut
                    text: "Save Score"
                    onClicked: {
                        console.log("Nombre ingresado:", nameInput.text);
                        JS.storeData()
                        nameInput.placeholderText = "Introduce tu Nombre"
                        nameInput.text = ""
                        scoreRect.visible = false
                        flag = true
                    }

                }

            }
        }
        Button {
            id:tableScoreBut
            text: "TableScore"
            visible : false
            onClicked: {

                if(stateManager.state === "Score"){
                    JS.readingData()
                    stateManager.state = "ScoreTable"
                }
                else{
                    stateManager.state = "Score"
                }
            }
        }

        Button{
            id:quitButton
            visible: false
            text:"EXIT"
            onClicked: {
                Qt.quit();

            }

        }
    }


    Rectangle{

        id:mRect
        width:50
        height: 50
        visible:false
        color:if(difficulty === "HARD")
                  "red"
              else if(difficulty === "NORMAL")
                  "orange"
              else
                  "green"

        RandomNumber on x {
            maxValue: 500 - mRect.width
            interval: intervalue
        }
        RandomNumber on y {
            maxValue: 500 -mRect.height
            interval: intervalue
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                points++
                console.log("+1 point!")
            }
        }

    }
    // Manager para controlar las transiciones de estado
    StateGroup {
        id: stateManager

        state: "Start"
        states: [
            State {
                name: "Start"
                PropertyChanges {
                    target: startButton
                    visible:true
                    text : "START"
                }
                PropertyChanges {
                    target: mRect
                    visible:false
                }
                PropertyChanges {
                    target: scoreId
                    visible:false
                }
                PropertyChanges {
                    target: quitButton
                    visible:false
                }
            },
            State {
                name: "Playing"
                PropertyChanges {
                    target: startButton
                    visible:false
                }
                PropertyChanges {
                    target: easyButton
                    visible:false
                }
                PropertyChanges {
                    target: midButton
                    visible:false
                }
                PropertyChanges {
                    target: hardButton
                    visible:false
                }
                PropertyChanges {
                    target: mRect
                    visible:true

                }
                PropertyChanges {
                    target: scoreId
                    visible:false
                }
                PropertyChanges {
                    target: scoreRect
                    visible:false

                }
                PropertyChanges {
                    target: tableScoreBut
                    visible : false
                    text : "ScoreTable"
                }
                PropertyChanges {
                    target: layout
                    visible : true
                }

            },
            State {
                name: "Score"

                PropertyChanges {
                    target: startButton
                    visible:true
                    text : "PLAY AGAIN"
                }
                PropertyChanges {
                    target: mRect
                    visible:false
                }
                PropertyChanges {
                    target: scoreId
                    visible:true
                }
                PropertyChanges {
                    target: quitButton
                    visible:true
                }
                PropertyChanges {
                    target: scoreRect
                    visible: (flag === false) ? true : false

                }
                PropertyChanges {
                    target: listScore
                    visible : false
                }
                PropertyChanges {
                    target: tableScoreBut
                    visible : true
                    text : "ScoreTable"
                }
            },
            State {
                name: "ScoreTable"
                PropertyChanges {
                    target: startButton
                    visible:false
                }
                PropertyChanges {
                    target: tableScoreBut
                    visible : true
                    text : "Back"
                }
                PropertyChanges {
                    target: mRect
                    visible:false
                }
                PropertyChanges {
                    target: scoreId
                    visible:false
                }
                PropertyChanges {
                    target: quitButton
                    visible:false
                }
                PropertyChanges {
                    target: scoreRect
                    visible:false
                }
                PropertyChanges {
                    target: easyButton
                    visible:false
                }
                PropertyChanges {
                    target: midButton
                    visible:false
                }
                PropertyChanges {
                    target: hardButton
                    visible:false
                }
                PropertyChanges {
                    target: listScore
                    visible : true
                }

            }
        ]
        // Transiciones
        transitions: [
            Transition {
                from: "Score"
                to: "Start"
                reversible: false

            },
            Transition {
                from: "Start"
                to: "Playing"
                reversible: false

            },
            Transition {
                from: "Playing"
                to: "Score"
                reversible: false

            },
            Transition {
                from: "Score"
                to: "ScoreTable"
                reversible: true

            }
        ]
    }
    Component.onCompleted: {
        //read data
        JS.dbInit()
        JS.readingData()

    }

}

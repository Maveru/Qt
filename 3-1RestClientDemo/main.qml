import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls.Fusion
import QtQuick.Layouts

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Rest APi Demo")

    ColumnLayout{
        anchors.fill:parent
        spacing:0

        ListView{
            id:mListView
            model:myModel
            Layout.fillHeight: true
            Layout.fillWidth: true
            delegate: Rectangle{
                width: parent.width
                height:textId.implicitHeight +30
                color:"mistyrose"
                border.color: "gray"
                radius:5

                Text{
                    id:textId
                    width:parent.width
                    height: parent.height
                    anchors.centerIn: parent
                    text:modelData
                    font.pointSize: 13
                    wrapMode:Text.WordWrap
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }
        SpinBox{
            id:spinBoxId
            Layout.fillWidth: true
            value:10
        }

        Button{
            id:mBut
            text:"fetch"

            onClicked: {
                Wrapper.fetchPosts(spinBoxId.value)
            }
        }
        Button{
            id:mBut2
            text:"RemoveLast"

            onClicked: {
                Wrapper.removeLast()

            }
        }
    }


}

import QtQuick 2.6
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MouseArea {
        anchors.leftMargin: 12
        anchors.topMargin: 19
        anchors.rightMargin: 22
        anchors.bottomMargin: 19
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }

        Grid {
            id: grid1
            x: 142
            y: 21
            width: 400
            height: 400
            clip: false
        }
    }

    Text {
        text: qsTr("Hello World")
        anchors.verticalCenterOffset: -142
        anchors.horizontalCenterOffset: -246
        anchors.centerIn: parent
    }
}

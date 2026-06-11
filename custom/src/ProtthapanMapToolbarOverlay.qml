import QtQuick
import QtQuick.Controls

Rectangle {
    id: root
    height: 56
    radius: 8
    color: "#CC050A07"
    border.color: "#00FF88"
    border.width: 1

    Row {
        anchors.fill: parent
        anchors.leftMargin: 14
        anchors.rightMargin: 14
        spacing: 18

        Image {
            source: "qrc:/custom/res/Images/protthapan-logo-toolbar.png"
            width: 110
            height: 48
            fillMode: Image.PreserveAspectFit
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            text: "MAP"
            color: "#00FF88"
            font.bold: true
            font.pixelSize: 16
            anchors.verticalCenter: parent.verticalCenter
        }
        Text { text: "CONNECT"; color: "#D8FFE6"; font.pixelSize: 14; anchors.verticalCenter: parent.verticalCenter }
        Text { text: "MODE"; color: "#D8FFE6"; font.pixelSize: 14; anchors.verticalCenter: parent.verticalCenter }
        Text { text: "GPS"; color: "#D8FFE6"; font.pixelSize: 14; anchors.verticalCenter: parent.verticalCenter }
        Text { text: "BATTERY"; color: "#D8FFE6"; font.pixelSize: 14; anchors.verticalCenter: parent.verticalCenter }
        Text { text: "RTL"; color: "#FFB000"; font.pixelSize: 14; font.bold: true; anchors.verticalCenter: parent.verticalCenter }
    }
}
